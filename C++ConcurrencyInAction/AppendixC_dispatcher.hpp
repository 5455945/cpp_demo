#pragma once
#include "AppendixC_queue.hpp"

namespace messaging
{
    class close_queue // �����رն��е���Ϣ
    {};

    class dispatcher
    {
        queue* q;
        bool chained;

        dispatcher(dispatcher const&) = delete; // ���ܸ��Ƶĵ�����ʵ��
        dispatcher& operator=(dispatcher const&) = delete;

        template<
            typename Dispatcher,
            typename Msg,
            typename Func> // ����TemplateDispatcherʵ�з����ڲ���Ա
            friend class TemplateDispatcher;

        void wait_and_dispatch()
        {
            for (;;) // ѭ�����ȴ��͵�����Ϣ
            {
                auto msg = q->wait_and_pop();
                dispatch(msg);
            }
        }

        bool dispatch( // dispatch()���close_queue��Ϣ�����׳�
            std::shared_ptr<message_base> const& msg)
        {
            if (dynamic_cast<wrapped_message<close_queue>*>(msg.get()))
            {
                throw close_queue();
            }
            return false;
        }
    public:
        dispatcher(dispatcher&& other) : // ������ʵ�����Ա��ƶ�
            q(other.q), chained(other.chained)
        {
            other.chained = true; // ��Դ���õȴ���Ϣ
        }

        explicit dispatcher(queue* q_) :
            q(q_), chained(false)
        {}

        template<typename Message, typename Func>
        TemplateDispatcher<dispatcher, Message, Func>
            handle(Func&& f) // ʹ��TemplateDispatcher�����ض����͵���Ϣ
        {
            return TemplateDispatcher<dispatcher, Message, Func>(
                q, this, std::forward<Func>(f));
        }

        ~dispatcher() noexcept(false) // �������������׳��쳣
        {
            if (!chained)
            {
                wait_and_dispatch();
            }
        }
    };
}
