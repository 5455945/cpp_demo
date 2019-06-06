#include "Concurrency04.h" 
#include <condition_variable>
#include <future>
#include <mutex>
#include <chrono>
namespace {
    // 4.2.4 Ϊfuture�����쳣
    double square_root(double x) {
        if (x < 0) {
            throw std::out_of_range("x < 0");
        }
        return sqrt(x);
    }
    
    // 4.2.5 �ȴ��Զ���߳�
    // 4.3 ��ʱ�����Ƶĵȴ�
    // 4.3.1 ʱ��
    // 4.3.2 ʱ���
    // 4.3.3 ʱ���
    // �ȴ�һ�����г�ʱ����������
    std::condition_variable cv;
    bool done;
    std::mutex m;
    bool wait_loop()
    {
        auto const timeout = std::chrono::steady_clock::now() +
            std::chrono::milliseconds(500);
        std::unique_lock<std::mutex> lk(m);
        while (!done)
        {
            if (cv.wait_until(lk, timeout) == std::cv_status::timeout)
                break;
        }
        return done;
    }
}
void Concurrency04_11() {
    //double y = square_root(-1);
    //std::future<double> f = std::async(square_root, -1);
    double y2 = square_root(3);
    std::future<double> f2 = std::async(square_root, 2);
    double f1 = f2.get();

    std::promise<double> some_promise;
    try {
        some_promise.set_value(3.14);
    }
    catch (...) {
        some_promise.set_exception(std::current_exception());
        //some_promise.set_exception(std::copy_exception(std::logic_error("foo ")));
    }
    wait_loop();
}