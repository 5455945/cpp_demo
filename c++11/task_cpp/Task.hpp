#pragma once
#include <functional>

template<typename T>
class Task;

template<typename R, typename ...Args>
class Task<R(Args...)>
{
private:
    std::function<R(Args...)> m_fn;
    
public:
    typedef R return_type;
    
    template<typename F>
    //auto Then(F&& f) {
	auto Then(F&& f)->Task<typename std::result_of<F(R)>::type(Args...)> {
        typedef typename std::result_of<F(R)>::type ReturnType;
        auto func = std::move(m_fn);
        return Task<ReturnType(Args...)>([func, &f](Args&&... args) {
            std::future<R> lastf = std::async(func, std::forward<Args>(args)...);
            return std::async(f, lastf.get()).get();
        });
    }
    
    Task(std::function<R(Args...)>&& f) :m_fn(std::move(f)){}
    Task(std::function<R(Args...)>& f) :m_fn(f){}
    
    ~Task(){}
    // 等待异步操作完成
    void Wait() {
        std::async(m_fn).wait();
    }
    // 获取异步操作的结果
    template<typename... Args>
    R Get(Args&&... args) {
        return std::async(m_fn, std::forward<Args>(args)...).get();
	}
    // 发起异步操作
	std::shared_future<R> Run() {
        return std::async(m_fn);
    }
};
