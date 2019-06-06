#include "Concurrency03.h"
#include <deque>
// 2.3 ���ֽӿ��й��еľ�������
namespace {
    // std::tack�����������Ľӿ�
    template<typename T, typename Container = std::deque<T> >
    class stack
    {
    public:
        explicit stack(const Container&);
        explicit stack(Container&& = Container());
        template <class Alloc> explicit stack(const Alloc&);
        template <class Alloc> stack(const Container&, const Alloc&);
        template <class Alloc> stack(Container&&, const Alloc&);
        template <class Alloc> stack(stack&&, const Alloc&);

        bool empty() const;
        size_t size() const;
        T& top();
        T const& top() const;
        void push(T const&);
        void push(T&&);
        void pop();
        void swap(stack&&);
    };
}
void Concurrency03_03() {
}
