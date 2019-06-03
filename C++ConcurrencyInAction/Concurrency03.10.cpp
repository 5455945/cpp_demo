#include "Concurrency03.h"
#include <mutex>
namespace {
    // 3.2.7 在作用域之间转移锁的所有权
    std::mutex  some_mutex;
    void prepare_data() {}
    void do_something() {}
    std::unique_lock<std::mutex> get_lock() {
        extern std::mutex some_mutex;
        std::unique_lock<std::mutex> lk(some_mutex);
        prepare_data();
        return lk;
    }
    void process_data() {
        std::unique_lock<std::mutex> lk(get_lock());
        do_something();
    }

    // 3.2.8 锁定在恰当的粒度
    //void get_and_process_data() {
    //    std::unique_lock<std::mutex> my_lock(the_mutex);
    //    some_class data_to_process = get_next_data_chunk();
    //    my_lock.unlock();// 对于process的调用不需要互斥元
    //    result_type result = process(data_to_process);
    //    my_lock.lock(); // 重新锁定互斥元已回写结果
    //    write_result(data_to_process, result);
    //}
    // 一般情况下，只应以执行要求的操作所需的最小可能时间持有锁。

    // 在比较运算中每次锁定一个互斥元
    // 如果你不能在操作的整个持续时间内持有所需要的锁，你就把自己暴露在竞争条件中。
    class Y
    {
    private:
        int some_detail;
        mutable std::mutex m;

        int get_detail() const
        {
            std::lock_guard<std::mutex> lock_a(m);
            return some_detail;
        }
    public:
        Y(int sd) :some_detail(sd) {}

        friend bool operator==(Y const& lhs, Y const& rhs)
        {
            if (&lhs == &rhs)
                return true;
            int const lhs_value = lhs.get_detail();
            // lhs.get_detail()和rhs.get_detail()之间可能发生任何修改
            int const rhs_value = rhs.get_detail();
            return lhs_value == rhs_value;
        }
    };
}
void Concurrency03_10() {

}
