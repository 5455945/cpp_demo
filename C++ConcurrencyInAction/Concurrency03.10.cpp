#include "Concurrency03.h"
#include <mutex>
namespace {
    // 3.2.7 ��������֮��ת����������Ȩ
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

    // 3.2.8 ������ǡ��������
    int get_next_data_chunk() { return 0; }
    int process(int) { return 0; }
    void write_result(int, int) {}
    void get_and_process_data() {
        std::mutex the_mutex;
        std::unique_lock<std::mutex> my_lock(the_mutex);
        int data_to_process = get_next_data_chunk();
        my_lock.unlock();// ����process�ĵ��ò���Ҫ����Ԫ
        int result = process(data_to_process);
        my_lock.lock(); // ������������Ԫ�ѻ�д���
        write_result(data_to_process, result);
    }
    // һ������£�ֻӦ��ִ��Ҫ��Ĳ����������С����ʱ���������

    // �ڱȽ�������ÿ������һ������Ԫ
    // ����㲻���ڲ�������������ʱ���ڳ�������Ҫ��������Ͱ��Լ���¶�ھ��������С�
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
            // lhs.get_detail()��rhs.get_detail()֮����ܷ����κ��޸�
            int const rhs_value = rhs.get_detail();
            return lhs_value == rhs_value;
        }
    };
}
#include <iostream>
void Concurrency03_10() {
    std::cout << __FUNCTION__ << std::endl;
    process_data();
    get_and_process_data();
    Y y2(2), y3(2);
    if (y2 == y3) {
        std::cout << "y2 == y3" << std::endl;
    }
    else {
        std::cout << "y2 != y3" << std::endl;
    }
}
