#include "Concurrency03.h"
#include <mutex>
// 3.2 Ϊ�����������ݾ�����֯����
namespace {
    // ����ش������ܱ������ݵ�����
    class some_data
    {
        int a;
        std::string b;
    public:
        void do_something()
        {}
    };

    class data_wrapper
    {
    private:
        some_data data;
        std::mutex m; // ���mҪ�������ݳ�Աdata
    public:
        template<typename Function>
        void process_data(Function func)
        {
            std::lock_guard<std::mutex> l(m);
            func(data);
        }
    };

    some_data* unprotected;

    void malicious_function(some_data& protected_data)
    {
        unprotected = &protected_data;
    }

    data_wrapper x;

    void foo()
    {
        // process_data�еĴ��뿴����ͦ�޺��ģ��ܵ�std::lock_guard������
        // �����û��ṩ�ĺ���func�ĵ�����ζ��foo���Դ���malicious_function
        // ���ƹ�����,Ȼ��������������Ԫ���ɵ���do_something()��
        x.process_data(malicious_function); // ����һ�����⺯��
        unprotected->do_something(); // ���ܱ��������ݽ���δ�ܱ����ķ���
    }
}
void Concurrency03_02() {
    foo();
}

// ԭ�򣺲�Ҫ���ܱ������ݵ�ָ������ô��ݵ����ķ�Χ֮��,������ͨ���Ӻ����з������ǡ�
// ���������ⲿ�ɼ����ڴ���,������Ϊ�������ݸ��û��ṩ�ĺ�����