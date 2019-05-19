// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMChainOfResponsibility.h
// FileTarget    : DMChainOfResponsibility.h
// Description   : ChainOfResponsibility ģʽ
// 
// ����:
// ʹ��������л��ᴦ������,�Ӷ���������ķ����ߺͽ�����֮�����Ϲ�ϵ.����Щ��������һ���������������������ݸ�����,ֱ����һ����������Ϊֹ.
// �������:
// 1)Handler:����һ����������Ľӿ�,��ͼ������ӿھ���HandleRequset��
// ��,�����ͬʱ��һ��ָ��Handler�����ָ��,ָ������Ĵ�������Ķ���(��
// ���еĻ�).
// ����:
// ���ģʽ�ѿ��Դ���һ������Ķ�����������ʽ������һ��,����Щ�����д�
// ������Ļ���.�ñ�ԭ������װ�����о��������ʹ����ټ�ĳ�˵�ʱ��,̫����
// (���Դ���һ������Ķ���)�ͻ����εĺ�:��XX...����һֱ��ȥֱ���ҵ����
// ��Ϊֹ.ChainOfResponsibilityģʽҲ�������Ĵ��������,����к����Ķ�
// ����Դ���,��ô���������Ķ�����,������Լ���������.��������ư�����
// �ķ����ߺ��������ֵĴ����߽�����,�ñȷ��ŵĻʵ۲�֪���������ĸ�̫����
// ����ҵ���Ҫ�ҵ�����һ��,ֻ�ܷ��������OK��.
// 
// version        date        Author        Description
// 0001-0001      2013-03-05  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __CHAINOFRESPONSIBILITY__H__
#define __CHAINOFRESPONSIBILITY__H__
#include <string>
// ������࣬����һ����������Ľӿ�
class Handler
{
public:
	Handler(Handler* pSuccessor = NULL);
	virtual ~Handler();
	// ���麯������������ʵ��
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
