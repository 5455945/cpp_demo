#include "Concurrency03.h"
#include <map>
#include <string>
#include <mutex>
#include <shared_mutex> // C++17
// shared_mutex ���������ڱ����������ܶ���߳�ͬʱ���ʵ�ͬ��ԭ��������ٽ������Է��ʵĻ��������෴�� shared_mutex ӵ�ж�����εķ��ʣ�
// ���� - ����߳��ܹ���ͬһ���������Ȩ��
// ������ - ��һ���߳���ռ�л��⡣
// ������ͨ�����ڶ�����߳���ͬʱ����ͬһ��Դ�����������ݾ�������ֻ��һ��д�߳��ܷ��ʵ����Ρ�

// 3.3.2 �������ٸ��µ����ݽṹ
namespace {
    class dns_entry
    {};

    class dns_cache
    {
        std::map<std::string, dns_entry> entries;
        // ������ͨ�����ڶ�����߳���ͬʱ����ͬһ��Դ�����������ݾ�������ֻ��һ��д�߳��ܷ��ʵ�����
        std::shared_mutex entry_mutex;
    public:
        dns_entry find_entry(std::string const& domain)
        {
            // ����������ʱ���ǹ����(ֻ����):std::shared_lock<std::shared_mutex>
            std::shared_lock<std::shared_mutex> lk(entry_mutex);
            std::map<std::string, dns_entry>::const_iterator const it =
                entries.find(domain);
            return (it == entries.end()) ? dns_entry() : it->second;
        }
        void update_or_add_entry(std::string const& domain,
            dns_entry const& dns_details)
        {
            // ����������ʱ����������(��ռ��):std::lock_guard<std::shared_mutex>/std::unique_lock<std::shared_mutex>
            std::lock_guard<std::shared_mutex> lk(entry_mutex);
            entries[domain] = dns_details;
        }
    };
}
void Concurrency03_13() {

}

// 3.3.3 �ݹ���
// std::mutex��ͬһ���̱߳���ε��ûᵼ��δ������Ϊ(underined behavior)
// std::unique_lock<std::recursive_mutex>/std::lock_guard<std::recursive_mutex>֧��ͬһ���̶߳�λ�ȡ��
// ������ʹ�õݹ���
