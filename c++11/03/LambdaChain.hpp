#pragma once
#include <iostream>
#include <functional>
#include <type_traits>

template<typename T>
class LambdaChain;

template<typename R, typename...Args>
class LambdaChain<R(Args...)> {
public:
    LambdaChain(std::function<R(Args...)>&& f) : m_fn(std::move(f)) {}

    LambdaChain(std::function<R(Args...)>& f) : m_fn(f) {}

    template<typename... Args>
    R Run(Args&&... args) {
        return m_fn(std::forward<Args>(args)...);
    }

    template<typename F>
    auto Then(F& f)->LambdaChain<typename std::result_of<F(R)>::type(Args...)> {
        using return_type = typename std::result_of<F(R)>::type;

        auto func = std::move(m_fn);

        return LambdaChain<return_type(Args...)>([func, f](Args&&... args) {
            return f(func(std::forward<Args>(args)...)); 
        });
    }
    
private:
    std::function<R(Args...)> m_fn;
};