#include "Concurrency07.h" 
#include <atomic>
namespace {
    template<typename T>
    class lock_free_stack
    {
    private:
        struct node
        {
            T data;
            node* next;
            node(T const& data_) :
                data(data_)
            {}
        };
        std::atomic<node*> head;
    public:
        void push(T const& data)
        {
            node* const new_node = new node(data);
            new_node->next = head.load();
            while (!head.compare_exchange_weak(new_node->next, new_node));
        }
    };
}

void Concurrency07_02() {

}