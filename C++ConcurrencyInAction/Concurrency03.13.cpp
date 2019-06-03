#include "Concurrency03.h"
#include <map>
#include <string>
#include <mutex>
#include <shared_mutex> // C++17
// shared_mutex 类是能用于保护数据免受多个线程同时访问的同步原语。与其他促进排他性访问的互斥类型相反， shared_mutex 拥有二个层次的访问：
// 共享 - 多个线程能共享同一互斥的所有权。
// 排他性 - 仅一个线程能占有互斥。
// 共享互斥通常用于多个读线程能同时访问同一资源而不导致数据竞争，但只有一个写线程能访问的情形。

// 3.3.2 保护很少更新的数据结构
namespace {
    class dns_entry
    {};

    class dns_cache
    {
        std::map<std::string, dns_entry> entries;
        // 共享互斥通常用于多个读线程能同时访问同一资源而不导致数据竞争，但只有一个写线程能访问的情形
        std::shared_mutex entry_mutex;
    public:
        dns_entry find_entry(std::string const& domain)
        {
            // 这样持有锁时，是共享的(只读的):std::shared_lock<std::shared_mutex>
            std::shared_lock<std::shared_mutex> lk(entry_mutex);
            std::map<std::string, dns_entry>::const_iterator const it =
                entries.find(domain);
            return (it == entries.end()) ? dns_entry() : it->second;
        }
        void update_or_add_entry(std::string const& domain,
            dns_entry const& dns_details)
        {
            // 这样持有锁时，是排他的(独占的):std::lock_guard<std::shared_mutex>/std::unique_lock<std::shared_mutex>
            std::lock_guard<std::shared_mutex> lk(entry_mutex);
            entries[domain] = dns_details;
        }
    };
}
void Concurrency03_13() {

}

// 3.3.3 递归锁
// std::mutex在同一个线程被多次调用会导致未定义行为(underined behavior)
// std::unique_lock<std::recursive_mutex>/std::lock_guard<std::recursive_mutex>支持同一个线程多次获取锁
// 不建议使用递归锁
