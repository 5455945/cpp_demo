#include "Concurrency02.h"
#include <thread>
#include <iostream>
namespace C0201{
    void do_something(int& i)
    {
        ++i;
    }

    struct func
    {
        int& i;

        func(int& i_) :i(i_) {}

        void operator()()
        {
            for (unsigned j = 0; j < 1000000; ++j)
            {
                do_something(i);
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }
    };


    void oops()
    {
        int some_local_state = 0;
        func my_func(some_local_state);
        std::thread my_thread(my_func);
        my_thread.detach();
    }
}
void Concurrency02_01() {
    //C0201::oops();
    //// oops()中的some_local_state已经失效，但my_thread对象的my_func函数应该还在运行，导致发生问题
}
