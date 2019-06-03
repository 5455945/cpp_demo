#include "Concurrency04.h" 
#include <future>
#include <iostream>
namespace {

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
