// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMStrategy.h
// FileTarget    : DMStrategy.h
// Description   : Strategy 模式
//                 
// 作用:
// 定义一系列的算法,把它们一个个封装起来, 并且使它们可相互替换.本模式使得算法可独立于使用它的客户而变化.
// 
// 解析:
// 简而言之一句话,Strategy模式是对算法的封装.处理一个问题的时候可能有多种算法,这些算法的接口(输入参数,输出参数等)都是一致的,那么可以考虑采用
// Strategy模式对这些算法进行封装,在基类中定义一个函数接口就可以了.
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __STRATEGY__H__
#define __STRATEGY__H__
class Strategy;
class Context
{
public:
	Context(Strategy* pStrategy);
	~Context();
	void ContextInterface();
private:
	Strategy* m_pStrategy;
};
class Strategy
{
public:
	virtual ~Strategy(){};
	virtual void AlgorithmInterface() = 0;
};
class ConcreteStrategyA
	: public Strategy
{
public:
	virtual ~ConcreteStrategyA(){};
	virtual void AlgorithmInterface();
};
#endif //__STRAGEGY__H__
