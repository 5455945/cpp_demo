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
    //void get_and_process_data() {
    //    std::unique_lock<std::mutex> my_lock(the_mutex);
    //    some_class data_to_process = get_next_data_chunk();
    //    my_lock.unlock();// ����process�ĵ��ò���Ҫ����Ԫ
    //    result_type result = process(data_to_process);
    //    my_lock.lock(); // ������������Ԫ�ѻ�д���
    //    write_result(data_to_process, result);
    //}
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
void Concurrency03_10() {

}
