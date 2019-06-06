#include "Concurrency08.h" 
#include <atomic>
#include <thread>
#include <vector>
namespace {
    // 通过成对更新的partial_sum的并行实现
    class join_threads {
    private:
        std::vector<std::thread>& threads;
    public:
        explicit join_threads(std::vector<std::thread>& threads_) :
            threads(threads_) {
        }
        ~join_threads() {
            for (unsigned long i = 0; i < threads.size(); ++i) {
                if (threads[i].joinable()) {
                    threads[i].join();
                }
            }
        }
    };
    struct barrier
    {
        std::atomic<unsigned> count;
        std::atomic<unsigned> spaces;
        std::atomic<unsigned> generation;
        barrier(unsigned count_) :
            count(count_), spaces(count_), generation(0)
        {}
        void wait()
        {
            unsigned const gen = generation.load();
            if (!--spaces)
            {
                spaces = count.load();
                ++generation;
            }
            else
            {
                while (generation.load() == gen)
                {
                    std::this_thread::yield();
                }
            }
        }

        void done_waiting()
        {
            --count;
            if (!--spaces)
            {
                spaces = count.load();
                ++generation;
            }
        }
    };

    template<typename Iterator>
    void parallel_partial_sum(Iterator first, Iterator last)
    {
        typedef typename Iterator::value_type value_type;

        struct process_element
        {
            void operator()(Iterator first, Iterator last,
                std::vector<value_type>& buffer,
                unsigned i, barrier& b)
            {
                value_type& ith_element = *(first + i);
                bool update_source = false;
                for (unsigned step = 0, stride = 1; stride <= i; ++step, stride *= 2)
                {
                    value_type const& source = (step % 2) ?
                        buffer[i] : ith_element;
                    value_type& dest = (step % 2) ?
                        ith_element : buffer[i];
                    value_type const& addend = (step % 2) ?
                        buffer[i - stride] : *(first + i - stride);
                    dest = source + addend;
                    update_source = !(step % 2);
                    b.wait();
                }
                if (update_source)
                {
                    ith_element = buffer[i];
                }
                b.done_waiting();
            }
        };

        unsigned long const length = std::distance(first, last);

        if (length <= 0)
            return;

        std::vector<value_type> buffer(length);
        barrier b(length);
        std::vector<std::thread> threads(length - 1);
        join_threads joiner(threads);

        Iterator block_start = first;
        for (unsigned long i = 0; i < (length - 1); ++i)
        {
            threads[i] = std::thread(process_element(), first, last,
                std::ref(buffer), i, std::ref(b));
        }
        process_element()(first, last, std::ref(buffer), length - 1, std::ref(b));
    }
}
#include <atomic>
#include <array>
#include <numeric>
#include <iostream>
void Concurrency08_13() {
    // 这个算法奇数个线程正确，偶数线程不正确
    std::cout << __FUNCTION__ << std::endl;
    std::atomic<bool> done = false;
    std::array<int, 100> a;
    std::iota(a.begin(), a.end(), 1);
    for (auto& it : a) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    int b = std::accumulate(a.begin(), a.end(), 0);
    std::cout << "b = " << b << std::endl;
    parallel_partial_sum(a.begin(), a.end());
    for (auto& it : a) {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}