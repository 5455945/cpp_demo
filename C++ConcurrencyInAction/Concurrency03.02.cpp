#include "Concurrency03.h"
#include <mutex>
// 3.2 为保护共享数据精心组织代码
namespace {
    // 意外地传出对受保护数据的引用
    class some_data
    {
        int a;
        std::string b;
    public:
        void do_something()
        {}
    };

    class data_wrapper
    {
    private:
        some_data data;
        std::mutex m; // 这个m要保护数据成员data
    public:
        template<typename Function>
        void process_data(Function func)
        {
            std::lock_guard<std::mutex> l(m);
            func(data);
        }
    };

    some_data* unprotected;

    void malicious_function(some_data& protected_data)
    {
        unprotected = &protected_data;
    }

    data_wrapper x;

    void foo()
    {
        // process_data中的代码看起来挺无害的，受到std::lock_guard保护；
        // 但对用户提供的函数func的调用意味着foo可以传入malicious_function
        // 来绕过保护,然后无需锁定互斥元即可调用do_something()。
        x.process_data(malicious_function); // 传入一个恶意函数
        unprotected->do_something(); // 对受保护的数据进行未受保护的访问
    }
}
void Concurrency03_02() {
    foo();
}

// 原则：不要将受保护数据的指针和引用传递到锁的范围之外,无论是通过从函数中返回它们、
// 将其存放在外部可见的内存中,还是作为参数传递给用户提供的函数。