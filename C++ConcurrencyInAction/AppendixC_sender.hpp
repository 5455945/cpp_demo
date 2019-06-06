#pragma once
#include "AppendixC_queue.hpp"
namespace messaging
{
    // sender��
    class sender
    {
        queue *q; // sender���Ƿ�װ�˶���ָ��
    public:
        sender() :
            q(nullptr) // Ĭ�Ϲ����senderû�ж���
        {}
        explicit sender(queue *q_) : // �����ָ����е�ָ����й���
            q(q_)
        {}
        template<typename Message>
        void send(Message const& msg)
        {
            if (q)
            {
                q->push(msg); // �ڶ�����������Ϣ
            }
        }
    };
}
