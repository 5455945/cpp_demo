#include "Concurrency04.h" 
#include <future>
#include <iostream>
// 4.2 使用future等待一次性事件
// 4.2.1 从后台任务中返回值
namespace {
    // 使用std::future获取异步任务的返回值
    int find_the_answer_to_ltuae()
    {
        return 42;
    }
    void do_other_stuff()
    {}
}
void Concurrency04_06() {
    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    std::cout << "The answer is " << the_answer.get() << std::endl;
}
