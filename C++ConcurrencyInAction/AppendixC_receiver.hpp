#pragma once
#include "AppendixC_sender.hpp"
#include "AppendixC_dispatcher.hpp"
namespace messaging
{
    class receiver
    {
        queue q; // һ��receiverӵ�д˶���
    public:
        operator sender() // ������ʽת�������ö��е�sender
        {
            return sender(&q);
        }
        dispatcher wait() // �ȴ����д���������
        {
            return dispatcher(&q);
        }
    };
}