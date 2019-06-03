#include "Concurrency03.h"
#include <exception>
#include <memory>
// 一个线程安全栈的概要定义
namespace {
    struct empty_stack : std::exception
    {
        const char* what() const throw();
    };

    template<typename T>
    class threadsafe_stack
    {
    public:
        threadsafe_stack();
        threadsafe_stack(const threadsafe_stack&);
        threadsafe_stack& operator=(const threadsafe_stack&) = delete;

        void push(T new_value) ;
        std::shared_ptr<T> pop();
        void pop(T& value);
        bool empty() const;
    };
}
void Concurrency03_04() {

}

