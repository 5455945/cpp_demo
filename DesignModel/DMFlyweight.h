// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMFlyweight.h
// FileTarget    : DMFlyweight.h
// Description   : Flyweight ģʽ
//                 
// ����:
// ���ù�������Ч��֧�ִ���ϸ���ȵĶ���
// 
// ����:
// Flyweightģʽ�ڴ���ʹ��һЩ���Ա�����Ķ����ʱ�򾭳�ʹ��.����,��QQ
// �����ʱ��ܶ�ʱ�������ûظ��ֲ��ò��ظ���ʱ��,һ�����һЩ���׵Ļ���
// ���ܱ���,��"�Ǻ�","�õ�"�ȵ�֮���,��Щ�򵥵Ĵ���ʵÿ���˶�����ǰ��
// ��õ�,��ʹ�õ�ʱ��ŵ��ó���.Flyweight���ǻ��ڽ�����������˼·��
// ������,����Ҫһ�������������ط�����ʹ�õĶ����ʱ��,��ȥ��ѯ�Ƿ��Ѿ�
// ������ͬ���Ķ���,���û�о�����֮�еĻ���ֱ��ʹ��.���,Flyweightģʽ
// ��FactoryģʽҲ��������.
// 
// ʵ��:
// ��Ҫ˵�����������ʵ�ֽ���ʵ���˶Կɹ�������ʹ��,�ǿɹ�������ʹ��
// û���г�,��Ϊ�������Flyweightģʽ���ص�.�����ʵ��Ҫ���ǲ���һ��list
// ������������Щ���Ա�����Ķ���,��Ҫʹ�õ�ʱ��͵������в�ѯ�ǲ����Ѿ�
// ������,��������ھͳ�ʼ��һ��,Ȼ�󷵻���������ָ��.
// 
// version        date        Author        Description
// 0001-0001      2013-03-08  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __FLYWEIGHT__H__
#define __FLYWEIGHT__H__
#include <string>
#include <list>
typedef std::string STATE;
class Flyweight
{
public:
	virtual ~Flyweight(){};
	STATE GetIntrinsicState();
	virtual void Operation(STATE& ExtrinsicState) = 0;
protected:
	Flyweight(const STATE& state) : m_State(state){};
private:
	STATE m_State;
};
class FlyweightFactory
{
public:
	FlyweightFactory(){};
	~FlyweightFactory();
	Flyweight* GetFlyweight(const STATE& key);
private:
	std::list<Flyweight*> m_listFlyweight;
};
class ConcreteFlyweight
	: public Flyweight
{
public:
	ConcreteFlyweight(const STATE& state) : Flyweight(state){};
	virtual ~ConcreteFlyweight(){};
	virtual void Operation(STATE& ExtrinsticState);
};
#endif //__FLYWEIGHT__H__
