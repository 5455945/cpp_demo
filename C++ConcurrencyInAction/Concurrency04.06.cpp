#include "Concurrency04.h" 
#include <future>
#include <iostream>
// 4.2 ʹ��future�ȴ�һ�����¼�
// 4.2.1 �Ӻ�̨�����з���ֵ
namespace {
    // ʹ��std::future��ȡ�첽����ķ���ֵ
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
