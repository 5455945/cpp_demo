// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMChainOfResponsibility.h
// FileTarget    : DMChainOfResponsibility.h
// Description   : ChainOfResponsibility 模式
// 
// 作用:
// 使多个对象都有机会处理请求,从而避免请求的发送者和接收者之间的耦合关系.将这些对象连成一条链，并沿着这条链传递该请求,直到有一个对象处理它为止.
// 抽象基类:
// 1)Handler:定义一个处理请求的接口,在图中这个接口就是HandleRequset函
// 数,这个类同时有一个指向Handler对象的指针,指向后续的处理请求的对象(如
// 果有的话).
// 解析:
// 这个模式把可以处理一个请求的对象以链的形式连在了一起,让这些对象都有处
// 理请求的机会.好比原来看古装电视中经常看到皇宫中召见某人的时候,太监们
// (可以处理一个请求的对象)就会依次的喊:传XX...这样一直下去直到找到这个
// 人为止.ChainOfResponsibility模式也是这样的处理请求的,如果有后续的对
// 象可以处理,那么传给后续的对象处理,否则就自己处理请求.这样的设计把请求
// 的发送者和请求这种的处理者解耦了,好比发号的皇帝不知道到底是哪个太监最
// 后会找到他要找到的人一般,只管发出命令就OK了.
// 
// version        date        Author        Description
// 0001-0001      2013-03-05  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __CHAINOFRESPONSIBILITY__H__
#define __CHAINOFRESPONSIBILITY__H__
#include <string>
// 抽象基类，定义一个处理请求的接口
class Handler
{
public:
	Handler(Handler* pSuccessor = NULL);
	virtual ~Handler();
	// 纯虚函数，由派生类实现
	virtual void HandleRequest() = 0;
protected:
	Handler* m_pSuccessor;
};
class ConcreteHandler1
	: public Handler
{
public:
	ConcreteHandler1(Handler* pSuccessor = NULL) : Handler(pSuccessor){};
	virtual ~ConcreteHandler1(){};
	virtual void HandleRequest();
};
class ConcreteHandler2
	: public Handler
{
public:
	ConcreteHandler2(Handler* pSuccessor = NULL) : Handler(pSuccessor){};
	virtual ~ConcreteHandler2(){};
	virtual void HandleRequest();
};
#endif //__CHAINOFRESPONSIBILITY__H__
