#pragma once
#include <exception>
#include <stack>
#include <mutex>
#include <memory>
// �̰߳�ȫջ���ඨ��
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
        data = other.data;
    }
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m);
        data.push(std::move(new_value)); // �� �����׳��쳣
    }
    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw empty_stack(); // �� �׳��쳣ʱ����Ϊ��û���޸ģ����̰߳�ȫ��
        std::shared_ptr<T> const res(
            std::make_shared<T>(std::move(data.top()))); // �� �����׳��쳣�����̰߳�ȫ
        data.pop(); // �� �������쳣
        return res;
    }
    void pop(T& value)
    {
        std::lock_guard<std::mutex> lock(m);
        if (data.empty()) throw empty_stack();
        value = std::move(data.top()); // ��
        data.pop(); // ��
    }
    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m);
        return data.empty();
    }
    size_t size() const {
        std::lock_guard<std::mutex> lock(m);
        return data.size();
    }
};

void Concurrency08_01();
void Concurrency08_02();
void Concurrency08_03();
void Concurrency08_04();
void Concurrency08_05();
void Concurrency08_06();
void Concurrency08_07();
void Concurrency08_08();
void Concurrency08_09();
void Concurrency08_10();
void Concurrency08_11();
void Concurrency08_12();
void Concurrency08_13();