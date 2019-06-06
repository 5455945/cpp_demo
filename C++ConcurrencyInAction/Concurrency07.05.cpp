#include "Concurrency07.h" 
#include <atomic>
#include <memory>
namespace {
    // ���ü����Ļ��ջ���
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
            if (threads_in_pop == 1) // �� 
            {
                node* nodes_to_delete = to_be_deleted.exchange(nullptr); // �� �г���Ҫ��ɾ���Ľڵ��嵥
                if (!--threads_in_pop) // �� ��pop()��Ψһ���߳���
                {
                    delete_nodes(nodes_to_delete); // ��
                }
                else if (nodes_to_delete) // ��
                {
                    chain_pending_nodes(nodes_to_delete); // ��
                }
                delete old_head; // ��
            }
            else
            {
                chain_pending_node(old_head); // ��
                --threads_in_pop;
            }
        }
        void chain_pending_nodes(node* nodes)
        {
            node* last = nodes;
            while (node* const next = last->next) // �������һ��ָ�룬����ĩβ
            {
                last = next;
            }
            chain_pending_nodes(nodes, last);
        }
        void chain_pending_nodes(node* first, node* last)
        {
            last->next = to_be_deleted; // ��
            while (!to_be_deleted.compare_exchange_weak(
                last->next, first)); // 11 ѭ���Ա�֤last->next��ȷ
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
            ++threads_in_pop; // �����κ���������ǰ���Ӽ���
            node* old_head = head.load();
            while (old_head &&
                !head.compare_exchange_weak(old_head, old_head->next));
            std::shared_ptr<T> res;
            if (old_head)
            {
                res.swap(old_head->data); // ������ܣ�����ɾ���Ľڵ�
            }
            try_reclaim(old_head); // �ӽڵ�����ȡ���ݣ������Ǹ���ָ��
            return res;
        }
    };
}
#include <atomic>
#include <iostream>
#include <thread>
void Concurrency07_05() {
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
