#pragma once
#include "Optional.hpp"
template<typename T>
struct Lazy {
    Lazy() {}
    // 保存需要延迟执行的函数
    template <typename Func, typename... Args>
    Lazy(Func& f, Args&& ... args) {
        m_func = [&f, &args...]{
            return f(args...);
        };
    }
    // 延迟执行，将结果放到Optional中缓存起来，下次不用重新计算可以直接返回结果
    T& Value() {
        if (!m_value.isInit()) {
            m_value = m_func();
        }
        return *m_value;
    }
    
    bool IsValueCreated() const {
        return m_value.isInit();
    }
    
private:
    std::function<T()> m_func;
    Optional<T> m_value;
};

template<class Func, typename... Args>
Lazy<typename std::result_of<Func(Args...)>::type>
lazy(Func&& fun, Args&& ... args) {
    return Lazy<typename std::result_of<Func(Args...)>::type>(std::forward<Func>(fun), std::forward<Args>(args)...);
}
