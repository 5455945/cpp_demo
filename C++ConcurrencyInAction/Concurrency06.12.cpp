#include "Concurrency06.h"
#include <algorithm>
#include <vector>
#include <memory>
#include <mutex>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <shared_mutex> // C++17
namespace {
    // 获取threadsafe_lookup_table的内容作为一个std::map<>
    template<typename Key, typename Value, typename Hash = std::hash<Key> >
    class threadsafe_lookup_table
    {
    private:
        class bucket_type
        {
        private:
            typedef std::pair<Key, Value> bucket_value;
            typedef std::list<bucket_value> bucket_data;
            typedef typename bucket_data::iterator bucket_iterator;

            bucket_data data;
            mutable std::shared_mutex mutex;

            bucket_iterator find_entry_for(Key const& key)
            {
                return std::find_if(data.begin(), data.end(),
                    [&](bucket_value const& item)
                    {return item.first == key; });
            }
        public:
            Value value_for(Key const& key, Value const& default_value)
            {
                std::shared_lock<std::shared_mutex> lock(mutex);
                bucket_iterator found_entry = find_entry_for(key);
                return (found_entry == data.end()) ?
                    default_value : found_entry->second;
            }

            void add_or_update_mapping(Key const& key, Value const& value)
            {
                std::unique_lock<std::shared_mutex> lock(mutex);
                bucket_iterator found_entry = find_entry_for(key);
                if (found_entry == data.end())
                {
                    data.push_back(bucket_value(key, value));
                }
                else
                {
                    found_entry->second = value;
                }
            }

            void remove_mapping(Key const& key)
            {
                std::unique_lock<std::shared_mutex> lock(mutex);
                bucket_iterator const found_entry = find_entry_for(key);
                if (found_entry != data.end())
                {
                    data.erase(found_entry);
                }
            }
        };

        std::vector<std::unique_ptr<bucket_type> > buckets;
        Hash hasher;

        bucket_type& get_bucket(Key const& key) const
        {
            std::size_t const bucket_index = hasher(key) % buckets.size();
            return *buckets[bucket_index];
        }

    public:
        typedef Key key_type;
        typedef Value mapped_type;
        typedef Hash hash_type;

        threadsafe_lookup_table(
            unsigned num_buckets = 19, Hash const& hasher_ = Hash()) :
            buckets(num_buckets), hasher(hasher_)
        {
            for (unsigned i = 0; i < num_buckets; ++i)
            {
                buckets[i].reset(new bucket_type);
            }
        }

        threadsafe_lookup_table(threadsafe_lookup_table const& other) = delete;
        threadsafe_lookup_table& operator=(
            threadsafe_lookup_table const& other) = delete;

        Value value_for(Key const& key,
            Value const& default_value = Value()) const
        {
            return get_bucket(key).value_for(key, default_value);
        }

        void add_or_update_mapping(Key const& key, Value const& value)
        {
            get_bucket(key).add_or_update_mapping(key, value);
        }

        void remove_mapping(Key const& key)
        {
            get_bucket(key).remove_mapping(key);
        }

        std::map<Key, Value> get_map() const
        {
            std::vector<std::unique_lock<std::shared_mutex> > locks;
            for (unsigned i = 0; i < buckets.size(); ++i)
            {
                //locks.push_back(
                //    std::unique_lock<std::shared_mutex>(buckets[i].mutex));
            }
            std::map<Key, Value> res;
            for (unsigned i = 0; i < buckets.size(); ++i)
            {
                //for (bucket_iterator it = buckets[i].data.begin();
                //    it != buckets[i].data.end();
                //    ++it)
                //{
                //    res.insert(*it);
                //}
            }
            return res;
        }
    };
}
#include <iostream>
#include <string>
#include <atomic>
void Concurrency06_12() {
    std::cout << "06.12 获取threadsafe_lookup_table的内容作为一个std::map<>" << std::endl;
    threadsafe_lookup_table<int, std::string, std::hash<int>> tlt;
    std::atomic_bool stop = false;
    std::thread t1([&]() {
        for (int i = 0; i < 1000; i++) {
            if (!stop) {
                tlt.add_or_update_mapping(i, std::to_string(i));
            }
        }
        });
    std::thread t2([&]() {
        std::string const value_default = "-1";
        for (int i = 0; i < 1000; i++) {
            if (!stop) {
                std::string value = tlt.value_for(i, value_default);
                std::cout << value << " ";
                if (value.compare(value_default) != 0) {
                    tlt.remove_mapping(i);
                }
            }
        }
        std::cout << std::endl;
        });
    std::thread t3([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        stop.store(true);
        });
    t1.join();
    t2.join();
    t3.join();
    std::map<int, std::string> maps;
    maps = tlt.get_map();
    for (auto& it : maps) {
        std::cout << it.first << "->" << it.second << std::endl;
    }
}