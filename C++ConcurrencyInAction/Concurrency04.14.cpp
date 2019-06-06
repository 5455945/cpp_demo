#include "Concurrency04.h" 
#include <future>
namespace {
    // 一个简单的spawn_task的实现
    template<typename F, typename A>
    std::future<typename std::result_of<F(A&&)>::type>
        spawn_task(F&& f, A&& a)
    {
        typedef typename std::result_of<F(A&&)>::type result_type;
        std::packaged_task<result_type(A&&)>
            task(std::move(f));
        std::future<result_type> res(task.get_future());
        std::thread t(std::move(task), std::move(a));
        t.detach();
        return res;
    }
}
#include <iostream>
void Concurrency04_14() {
    std::cout << __FUNCTION__ << std::endl;
    auto f = spawn_task<std::function<int(int)>, int>([](int a) {
        std::cout << a << std::endl;
        return a;
        }, int(2));
    auto r1 = f.get();

    auto f2 = spawn_task<std::function<void(int&&)>, int>([](int &&a) {
        std::cout << a << std::endl;
        }, int(3));
    f2.wait();
}