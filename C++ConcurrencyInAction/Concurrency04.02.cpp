#include "Concurrency04.h" 
#include <queue>
// 使用条件变量建立一个线程安全队列
namespace {
    // std::quque接口
    template <class T, class Container = std::deque<T> >
    class queue {
    public:
        explicit queue(const Container&);
        explicit queue(Container&& = Container());
        queue(queue&& q);

        template <class Alloc> explicit queue(const Alloc&);
        template <class Alloc> queue(const Container&, const Alloc&);
        template <class Alloc> queue(Container&&, const Alloc&);
        template <class Alloc> queue(queue&&, const Alloc&);

        queue& operator=(queue&& q);
        void swap(queue&& q);

        bool empty() const;
        size_t size() const;

        T& front();
        const T& front() const;
        T& back();
        const T& back() const;

        void push(const T& x);
        void push(T&& x);
        void pop();
    };
}
void Concurrency04_02() {
}