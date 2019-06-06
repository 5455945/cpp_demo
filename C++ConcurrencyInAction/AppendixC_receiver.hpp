#pragma once
#include "AppendixC_sender.hpp"
#include "AppendixC_dispatcher.hpp"
namespace messaging
{
    class receiver
    {
        queue q; // 一个receiver拥有此队列
    public:
        operator sender() // 允许隐式转换到引用队列的sender
        {
            return sender(&q);
        }
        dispatcher wait() // 等待队列创建调度器
        {
            return dispatcher(&q);
        }
    };
}