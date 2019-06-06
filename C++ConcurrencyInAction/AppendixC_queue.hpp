#pragma once
#include <condition_variable>
#include <queue>
#include <memory>
#include <mutex>
namespace messaging
{
    // 简单的消息队列
    struct message_base // 基类
    {
        virtual ~message_base()
        {}
    };

    template<typename Msg>
    struct wrapped_message : // 每个消息类型有特殊定义
        message_base
    {
        Msg contents;
        explicit wrapped_message(Msg const& contents_) :
            contents(contents_)
        {}
    };

    class queue // 消息队列
    {
        std::mutex m;
        std::condition_variable c;
        std::queue<std::shared_ptr<message_base>> q; // 实际的队列存储message_base的指针
    public:
        template<typename T>
        void push(T const& msg)
        {
            std::lock_guard<std::mutex> lk(m);
            q.push(std::make_shared<wrapped_message<T> >(msg)); // 将发出的消息封装并且存储指针
            c.notify_all();
        }
        std::shared_ptr<message_base> wait_and_pop()
        {
            std::unique_lock<std::mutex> lk(m);
            c.wait(lk, [&] {return !q.empty(); }); // 阻塞直到队列非空
            auto res = q.front();
            q.pop();
            return res;
        }
    };
}
