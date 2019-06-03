#include "Concurrency03.h"
#include <exception>
#include <stack>
#include <mutex>
#include <memory>
namespace {
    // 一个线程安全栈的详细定义
    struct empty_stack : std::exception
    {
        const char* what() const throw()
        {
            return "empty stack";
        }

    };

    template<typename T>
    class threadsafe_stack
    {
    private:
        std::stack<T> data;
        mutable std::mutex m;
    public:
        threadsafe_stack() {}
        threadsafe_stack(const threadsafe_stack& other)
        {
            std::lock_guard<std::mutex> lock(other.m);
            data = other.data; // 在构造函数体中执行复制
        }
        threadsafe_stack& operator=(const threadsafe_stack&) = delete;

        void push(T new_value)
        {
            std::lock_guard<std::mutex> lock(m);
            data.push(new_value);
        }
        std::shared_ptr<T> pop()
        {
            std::lock_guard<std::mutex> lock(m);
            if (data.empty()) throw empty_stack(); // 检查是否为空
            std::shared_ptr<T> const res(std::make_shared<T>(data.top())); // 在修改栈之前分配返回值
            data.pop();
            return res;
        }
        void pop(T& value)
        {
            std::lock_guard<std::mutex> lock(m);
            if (data.empty()) throw empty_stack();
            value = data.top();
            data.pop();
        }
        bool empty() const
        {
            std::lock_guard<std::mutex> lock(m);
            return data.empty();
        }
    };
}
void Concurrency03_05() {
    threadsafe_stack<int> si;
    si.push(5);
    si.pop();
    if (!si.empty())
    {
        int x;
        si.pop(x);
    }
}
