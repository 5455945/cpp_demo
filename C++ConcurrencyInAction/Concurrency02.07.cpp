#include "Concurrency02.h"
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>
namespace {
    // ����һ���̲߳��ȴ��������
    void do_work(unsigned id)
    {}

    void f()
    {
        std::vector<std::thread> threads;
        for (unsigned i = 0; i < 20; ++i)
        {
            threads.push_back(std::thread(do_work, i)); // �����߳�
        }
        std::for_each(threads.begin(), threads.end(),
            std::mem_fn(&std::thread::join)); // ������ÿ���߳��ϵ���join(),std::mem_fn��std::bind
    }
}
void Concurrency02_07() {
    f();
}