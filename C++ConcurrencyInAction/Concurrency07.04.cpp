#include "Concurrency07.h" 
#include <atomic>
#include <memory>
// 7.2.2 ֹͣ���˵�й¶�����������ݽṹ�й����ڴ�
namespace {
    // ��pop()��û���߳�ʱ���սڵ�
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
        std::atomic<unsigned> threads_in_pop; // �� ԭ�ӱ���
        void try_reclaim(node* old_head);
    public:
        std::shared_ptr<T> pop()
        {
            ++threads_in_pop; // �� �����κ���������ǰ���Ӽ���
            node* old_head = head.load();
            while (old_head &&
                !head.compare_exchange_weak(old_head, old_head->next));
            std::shared_ptr<T> res;
            if (old_head)
            {
                res.swap(old_head->data); // �� ������ܣ�����ɾ���Ľڵ�
            }
            try_reclaim(old_head); // �� �ӽڵ�����ȡ���ݣ������Ǹ���ָ��
            return res;
        }
    };
}

void Concurrency07_04() {

}
