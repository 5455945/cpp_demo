// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMCommand.h
// FileTarget    : DMCommand.h
// Description   : Command 模式
// 
// 作用:
// 将一个请求封装为一个对象,从而使你可用不同的请求对客户进行参数化;对请求排队或记录请求日志,以及支持可撤消的操作.
// 
// 解析:
// Comnand模式的思想是把命令封装在一个类中,就是这里的Command基类,同时把接收对象也封装在一个类中就是这里的Receiver类中,由调用这个命令
// 的类也就是这里的Invoker类来调用.其实,如果弄清楚了Command模式的原理,就会发现其实它和注册回调函数的原理是很相似的,而在面向过程的设计
// 中的回调函数其实和这里的Command类的作用是一致的.采用Command模式解耦了命令的发出者和命令的执行者.
// 
// version        date        Author        Description
// 0001-0001      2013-03-11  Zhangfj       新建
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
