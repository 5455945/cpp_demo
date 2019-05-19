// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMCommand.h
// FileTarget    : DMCommand.h
// Description   : Command ģʽ
// 
// ����:
// ��һ�������װΪһ������,�Ӷ�ʹ����ò�ͬ������Կͻ����в�����;�������Ŷӻ��¼������־,�Լ�֧�ֿɳ����Ĳ���.
// 
// ����:
// Comnandģʽ��˼���ǰ������װ��һ������,���������Command����,ͬʱ�ѽ��ն���Ҳ��װ��һ�����о��������Receiver����,�ɵ����������
// ����Ҳ���������Invoker��������.��ʵ,���Ū�����Commandģʽ��ԭ��,�ͻᷢ����ʵ����ע��ص�������ԭ���Ǻ����Ƶ�,����������̵����
// �еĻص�������ʵ�������Command���������һ�µ�.����Commandģʽ����������ķ����ߺ������ִ����.
// 
// version        date        Author        Description
// 0001-0001      2013-03-11  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __COMMAND__H__
#define __COMMAND__H__
class Command
{
public:
	virtual ~Command(){};
	virtual void Execute() = 0;
};
class Receiver
{
public:
	void Action();
};
class Invoker
{
public:
	Invoker(Command* pCommand);
	~Invoker();
	void Invoke();
private:
	Command* m_pCommand;
};
class ConcreteCommand : public Command
{
public:
	ConcreteCommand(Receiver* pReceiver);
	virtual ~ConcreteCommand();
	virtual void Execute();
private:
	Receiver* m_pReceiver;
};
#endif //__COMMAND__H__
