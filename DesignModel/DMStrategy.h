// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMStrategy.h
// FileTarget    : DMStrategy.h
// Description   : Strategy ģʽ
//                 
// ����:
// ����һϵ�е��㷨,������һ������װ����, ����ʹ���ǿ��໥�滻.��ģʽʹ���㷨�ɶ�����ʹ�����Ŀͻ����仯.
// 
// ����:
// �����֮һ�仰,Strategyģʽ�Ƕ��㷨�ķ�װ.����һ�������ʱ������ж����㷨,��Щ�㷨�Ľӿ�(�������,���������)����һ�µ�,��ô���Կ��ǲ���
// Strategyģʽ����Щ�㷨���з�װ,�ڻ����ж���һ�������ӿھͿ�����.
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       �½�
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
