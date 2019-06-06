#pragma once
#include "AppendixC_queue.hpp"

namespace messaging
{
    class close_queue // 用来关闭队列的消息
    {};

    class dispatcher
    {
        queue* q;
        bool chained;

        dispatcher(dispatcher const&) = delete; // 不能复制的调度器实例
        dispatcher& operator=(dispatcher const&) = delete;

        template<
            typename Dispatcher,
            typename Msg,
            typename Func> // 允许TemplateDispatcher实列访问内部成员
            friend class TemplateDispatcher;

        void wait_and_dispatch()
        {
            for (;;) // 循环，等待和调度消息
            {
                auto msg = q->wait_and_pop();
                dispatch(msg);
            }
        }

        bool dispatch( // dispatch()检查close_queue消息，并抛出
            std::shared_ptr<message_base> const& msg)
        {
            if (dynamic_cast<wrapped_message<close_queue>*>(msg.get()))
            {
                throw close_queue();
            }
            return false;
        }
    public:
        dispatcher(dispatcher&& other) : // 调度器实例可以被移动
            q(other.q), chained(other.chained)
        {
            other.chained = true; // 来源不得等待消息
        }

        explicit dispatcher(queue* q_) :
            q(q_), chained(false)
        {}

        template<typename Message, typename Func>
        TemplateDispatcher<dispatcher, Message, Func>
            handle(Func&& f) // 使用TemplateDispatcher处理特定类型的消息
        {
            return TemplateDispatcher<dispatcher, Message, Func>(
                q, this, std::forward<Func>(f));
        }

        ~dispatcher() noexcept(false) // 析构函数可能抛出异常
        {
            if (!chained)
            {
                wait_and_dispatch();
            }
        }
    };
}
