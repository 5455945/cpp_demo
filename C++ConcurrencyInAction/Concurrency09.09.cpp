#include "Concurrency09.h" 
#include <thread>
namespace {
    //class interrupt_flag
    //{
    //public:
    //    void set();
    //    bool is_set() const;
    //};
    //thread_local interrupt_flag this_thread_interrupt_flag;

    //class interruptible_thread
    //{
    //    std::thread internal_thread;
    //    interrupt_flag* flag;
    //public:
    //    template<typename FunctionType>
    //    interruptible_thread(FunctionType f)
    //    {
    //        std::promise<interrupt_flag*> p;
    //        internal_thread = std::thread([f, &p] {
    //            p.set_value(&this_thread_interrupt_flag);
    //            f();
    //            });
    //        flag = p.get_future().get();
    //    }
    //    void interrupt()
    //    {
    //        if (flag)
    //        {
    //            flag->set();
    //        }
    //    }
    //};
}

void Concurrency09_09() {

}