#pragma once
#include <condition_variable>
#include <queue>
#include <memory>
#include <mutex>
namespace messaging
{
    // �򵥵���Ϣ����
    struct message_base // ����
    {
        virtual ~message_base()
        {}
    };

    template<typename Msg>
    struct wrapped_message : // ÿ����Ϣ���������ⶨ��
        message_base
    {
        Msg contents;
        explicit wrapped_message(Msg const& contents_) :
            contents(contents_)
        {}
    };

    class queue // ��Ϣ����
    {
        std::mutex m;
        std::condition_variable c;
        std::queue<std::shared_ptr<message_base>> q; // ʵ�ʵĶ��д洢message_base��ָ��
    public:
        template<typename T>
        void push(T const& msg)
        {
            std::lock_guard<std::mutex> lk(m);
            q.push(std::make_shared<wrapped_message<T> >(msg)); // ����������Ϣ��װ���Ҵ洢ָ��
            c.notify_all();
        }
        std::shared_ptr<message_base> wait_and_pop()
        {
            std::unique_lock<std::mutex> lk(m);
            c.wait(lk, [&] {return !q.empty(); }); // ����ֱ�����зǿ�
            auto res = q.front();
            q.pop();
            return res;
        }
    };
}
