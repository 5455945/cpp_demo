#include "test_jthread.h"
#include <thread>
int main(int argc, char** argv) {

    test_jthread_cppreference01();

    test_jthread_jianshu01();

    test_cv();

    test_cvcb();

    test_cvprodcons();

    test_cvrace_hh();

    test_cvrace_pred();

    test_cvrace_stop();

    test_jthread1();

    test_jthread2();

    test_stoken();

    test_stokencb();
    
    test_stokenrace();
    
    test_stopcb();

    return 0;
}