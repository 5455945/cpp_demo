#pragma once
#include "AppendixC_queue.hpp"
namespace messaging
{
    // TemplateDispatcher��ģ��
    template<typename PreviousDispatcher, typename Msg, typename Func>
    class TemplateDispatcher
    {
        queue* q;
        PreviousDispatcher* prev;
        Func f;
        bool chained;

        TemplateDispatcher(TemplateDispatcher const&) = delete;
        TemplateDispatcher& operator=(TemplateDispatcher const&) = delete;

        template<typename Dispatcher, typename OtherMsg, typename OtherFunc>
        friend class TemplateDispatcher; // TemplateDispatcherʵ��֮�以Ϊ��Ԫ

        void wait_and_dispatch()
        {
            for (;;)
            {
                auto msg = q->wait_and_pop();
                if (dispatch(msg)) // �����������Ϣ������ѭ��
                    break;
            }
        }

        bool dispatch(std::shared_ptr<message_base> const& msg)
        {
            if (wrapped_message<Msg>* wrapper =
                dynamic_cast<wrapped_message<Msg>*>(msg.get())) // �����Ϣ���Ͳ����ú���
            {
                f(wrapper->contents);
                return true;
            }
            else
            {
                return prev->dispatch(msg); // ����ǰһ��������
            }
        }
    public:
        TemplateDispatcher(TemplateDispatcher&& other) :
            q(other.q), prev(other.prev), f(std::move(other.f)),
            chained(other.chained)
        {
            other.chained = true;
        }

        TemplateDispatcher(queue* q_, PreviousDispatcher* prev_, Func&& f_) :
            q(q_), prev(prev_), f(std::forward<Func>(f_)), chained(false)
        {
            prev_->chained = true;
        }

        template<typename OtherMsg, typename OtherFunc>
        TemplateDispatcher<TemplateDispatcher, OtherMsg, OtherFunc>
            handle(OtherFunc&& of) // �������Ӹ����Ĵ�����
        {
            return TemplateDispatcher<
                TemplateDispatcher, OtherMsg, OtherFunc>(
                    q, this, std::forward<OtherFunc>(of));
        }

        ~TemplateDispatcher() noexcept(false) // ������������noexcept(false)��
        {
            if (!chained)
            {
                wait_and_dispatch();
            }
        }
    };
}
