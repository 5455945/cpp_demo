#include "Concurrency07.h" 
#include <atomic>
#include <memory>
// 7.2.2 停止恼人的泄露：在无锁数据结构中管理内存
namespace {
    // 当pop()中没有线程时回收节点
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
        std::atomic<unsigned> threads_in_pop; // ① 原子变量
        void try_reclaim(node* old_head);
    public:
        std::shared_ptr<T> pop()
        {
            ++threads_in_pop; // ② 在做任何其它事情前增加计数
            node* old_head = head.load();
            while (old_head &&
                !head.compare_exchange_weak(old_head, old_head->next));
            std::shared_ptr<T> res;
            if (old_head)
            {
                res.swap(old_head->data); // ③ 如果可能，回收删除的节点
            }
            try_reclaim(old_head); // ④ 从节点中提取数据，而不是复制指针
            return res;
        }
    };
}

void Concurrency07_04() {

}
