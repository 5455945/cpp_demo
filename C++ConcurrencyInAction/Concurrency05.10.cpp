#include "Concurrency05.h" 
#include <string>
#include <thread>
#include <atomic>
#include <cassert>
// 7 使用获取-释放顺序和memory_order_consume的数据依赖
namespace {
    // 使用std::memory_order_consume同步数据
    struct X
    {
        int i;
        std::string s;
    };
    std::atomic<X*> p;
    std::atomic<int> a;
    void create_x()
    {
        X* x = new X;
        x->i = 42;
        x->s = "hello";
        a.store(99, std::memory_order_relaxed); // ①
        p.store(x, std::memory_order_release);  // ②
    }
    void use_x()
    {
        X* x;
        while (!(x = p.load(std::memory_order_consume))) // ③
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        assert(x->i == 42);  // ④
        assert(x->s == "hello"); // ⑤
        assert(a.load(std::memory_order_relaxed) == 99); // ⑥
    }
}
void Concurrency05_10() {
    std::thread t1(create_x);
    std::thread t2(use_x);
    t1.join();
    t2.join();
}