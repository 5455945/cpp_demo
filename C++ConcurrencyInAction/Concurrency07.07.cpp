#include "Concurrency07.h" 
#include <atomic>
#include <thread>
#include <stdexcept>
namespace {
    unsigned const max_hazard_pointers = 100;
    struct hazard_pointer
    {
        std::atomic<std::thread::id> id;
        std::atomic<void*> pointer;
    };
    hazard_pointer hazard_pointers[max_hazard_pointers];
    class hp_owner
    {
        hazard_pointer* hp;
    public:
        hp_owner(hp_owner const&) = delete;
        hp_owner operator=(hp_owner const&) = delete;
        hp_owner() :
            hp(nullptr)
        {
            for (unsigned i = 0; i < max_hazard_pointers; ++i)
            {
                std::thread::id old_id;
                if (hazard_pointers[i].id.compare_exchange_strong(
                    old_id, std::this_thread::get_id()))
                {
                    hp = &hazard_pointers[i];
                    break;
                }
            }
            if (!hp)
            {
                throw std::runtime_error("No hazard pointers available");
            }
        }
        std::atomic<void*>& get_pointer()
        {
            return hp->pointer;
        }
        ~hp_owner()
        {
            hp->pointer.store(nullptr);
            hp->id.store(std::thread::id());
        }

    };
    std::atomic<void*>& get_hazard_pointer_for_current_thread()
    {
        thread_local static hp_owner hazard;
        return hazard.get_pointer();
    }

    template<typename T>
    void do_delete(void* p)
    {
        delete static_cast<T*>(p);
    }
    struct data_to_reclaim
    {
        void* data;
        std::function<void(void*)> deleter;
        data_to_reclaim* next;
        template<typename T>
        data_to_reclaim(T* p) :
            data(p),
            deleter(&do_delete<T>),
            next(0)
        {}
        ~data_to_reclaim()
        {
            deleter(data);
        }
    };
    std::atomic<data_to_reclaim*> nodes_to_reclaim;
    void add_to_reclaim_list(data_to_reclaim* node)
    {
        node->next = nodes_to_reclaim.load();
        while (!nodes_to_reclaim.compare_exchange_weak(node->next, node));
    }
    template<typename T>
    void reclaim_later(T* data)
    {
        add_to_reclaim_list(new data_to_reclaim(data));
    }

    bool outstanding_hazard_pointers_for(void* p)
    {
        for (unsigned i = 0; i < max_hazard_pointers; ++i) {
            if (hazard_pointers[i].pointer.load() == p) {
                return true;
            }
        }
        return false;
    }
    void delete_nodes_with_no_hazards()
    {
        data_to_reclaim* current = nodes_to_reclaim.exchange(nullptr);
        while (current)
        {
            data_to_reclaim* const next = current->next;
            if (!outstanding_hazard_pointers_for(current->data))
            {
                delete current;
            }
            else
            {
                add_to_reclaim_list(current);
            }
            current = next;
        }
    }

    template<typename T>
    class lock_free_stack
    {
    private:
        struct node
        {
            std::shared_ptr<T> data;
            node* next;
            node(T const& data_) :
                data(std::make_shared<T>(data_))
            {}
        };
        std::atomic<node*> head;
        std::atomic<unsigned> threads_in_pop;

        std::atomic<node*> to_be_deleted;
        static void delete_nodes(node* nodes)
        {
            while (nodes)
            {
                node* next = nodes->next;
                delete nodes;
                nodes = next;
            }
        }
        void try_reclaim(node* old_head)
        {
            if (threads_in_pop == 1) // ① 
            {
                node* nodes_to_delete = to_be_deleted.exchange(nullptr); // ② 列出将要被删除的节点清单
                if (!--threads_in_pop) // ③ 是pop()中唯一的线程吗？
                {
                    delete_nodes(nodes_to_delete); // ④
                }
                else if (nodes_to_delete) // ⑤
                {
                    chain_pending_nodes(nodes_to_delete); // ⑥
                }
                delete old_head; // ⑦
            }
            else
            {
                chain_pending_node(old_head); // ⑧
                --threads_in_pop;
            }
        }
        void chain_pending_nodes(node* nodes)
        {
            node* last = nodes;
            while (node* const next = last->next) // ⑨跟随下一个指针，链至末尾
            {
                last = next;
            }
            chain_pending_nodes(nodes, last);
        }
        void chain_pending_nodes(node* first, node* last)
        {
            last->next = to_be_deleted; // ⑩
            while (!to_be_deleted.compare_exchange_weak(
                last->next, first)); // 11 循环以保证last->next正确
        }
        void chain_pending_node(node* n)
        {
            chain_pending_nodes(n, n); // 12
        }
    public:
        void push(T const& data)
        {
            node* const new_node = new node(data);
            new_node->next = head.load();
            while (!head.compare_exchange_weak(new_node->next, new_node));
        }
        std::shared_ptr<T> pop()
        {
            std::atomic<void*>& hp = get_hazard_pointer_for_current_thread();
            node* old_head = head.load();
            do
            {
                node* temp;
                do
                {
                    temp = old_head;
                    hp.store(old_head);
                    old_head = head.load();
                } while (old_head != temp);
            } while (old_head &&
                !head.compare_exchange_strong(old_head, old_head->next));
            hp.store(nullptr);
            std::shared_ptr<T> res;
            if (old_head)
            {
                res.swap(old_head->data);
                if (outstanding_hazard_pointers_for(old_head))
                {
                    reclaim_later(old_head);
                }
                else
                {
                    delete old_head;
                }
                delete_nodes_with_no_hazards();
            }
            return res;
        }
    };
}
#include <atomic>
#include <iostream>
#include <thread>
void Concurrency07_07() {
    std::cout << __FUNCTION__ << std::endl;
    lock_free_stack<int> lfs;
    std::atomic_bool running = false;
    std::thread t1([&]() {
        if (!running) {
            std::this_thread::yield();
        }
        for (int i = 0; i < 1000; i++) {
            lfs.push(i);
        }
        });
    std::thread t2([&]() {
        if (!running) {
            std::this_thread::yield();
        }
        std::shared_ptr<int> result;
        for (int i = 0; i < 1000; i++) {
            result = lfs.pop();
        }
        });
    running.store(true);
    t1.join();
    t2.join();
}
