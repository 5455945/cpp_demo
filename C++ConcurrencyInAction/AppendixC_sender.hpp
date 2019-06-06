#pragma once
#include "AppendixC_queue.hpp"
namespace messaging
{
    // sender类
    class sender
    {
        queue *q; // sender就是封装了队列指针
    public:
        sender() :
            q(nullptr) // 默认构造的sender没有队列
        {}
        explicit sender(queue *q_) : // 允许从指向队列的指针进行构造
            q(q_)
        {}
        template<typename Message>
        void send(Message const& msg)
        {
            if (q)
            {
                q->push(msg); // 在队列上推送消息
            }
        }
    };
}
