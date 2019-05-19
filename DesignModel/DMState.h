// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMState.h
// FileTarget    : DMState.h
// Description   : State 模式
//                 
// 作用:
// 允许一个对象在其内部状态改变时改变它的行为.
// 
// 解析:
// State模式主要解决的是在开发中时常遇到的根据不同的状态需要进行不同的
// 处理操作的问题,而这样的问题,大部分人是采用switch-case语句进行处理的,
// 这样会造成一个问题:分支过多,而且如果加入一个新的状态就需要对原来的代
// 码进行编译.State模式采用了对这些不同的状态进行封装的方式处理这类问题,
// 当状态改变的时候进行处理然后再切换到另一种状态,也就是说把状态的切换责
// 任交给了具体的状态类去负责.同时,State模式和Strategy模式在图示上有很
// 多相似的地方,需要说明的是两者的思想都是一致的,只不过封装的东西不同:St
// ate模式封装的是不同的状态,而Stategy模式封装的是不同的算法.
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __STATE__H__
#define __STATE__H__
namespace CSTATE
{
	class State;
	class Context
	{
	public:
		Context(State* pState);
		~Context();
		void Request();
		void ChangeState(State* pState);
	private:
		State* m_pState;
	};
	class State
	{
	public:
		virtual ~State(){};
		virtual void Handle(Context* pContext) = 0;
	};
	class ConcreteStateA : public State
	{
	public:
		void Handle(Context* pContext);
	};
	class ConcreteStateB : public State
	{
	public:
		void Handle(Context* pContext);
	};
};
#endif //__STATE__H__
