// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMProxy.h
// FileTarget    : DMProxy.h
// Description   : Proxy 模式
// 
// 作用:
// 为其他对象提供一种代理以控制对这个对象的访问。
// 抽象基类:
// 1)Subject:定义了Proxy和RealSubject的公有接口,这样就可以在任何需要使用到RealSubject的地方都使用Proxy.
// 解析:
// Proxy其实是基于这样一种时常使用到的技术-某个对象直到它真正被使用到的
// 时候才被初始化,在没有使用到的时候就暂时用Proxy作一个占位符.这个模式
// 实现的要点就是Proxy和RealSubject都继承自Subject,这样保证了两个的
// 接口都是一致的.
// 
// version        date        Author        Description
// 0001-0001      2013-03-04  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __DMPROXY__H__
#define __DMPROXY__H__
// 定义了Proxy和RealSubject的公有接口，这样就可以在任何需要使用到RealSubject的地方都使用Proxy.
class Subject
{
public:
	Subject(){};
	virtual ~Subject(){};
	virtual void Request() = 0;
};
// 真正使用的实体
class RealSubject
	: public Subject
{
public:
	RealSubject();
	virtual ~RealSubject(){};
	virtual void Request();
};
// 代理类，含有一个指向RealSubject对象的指针
class Proxy
	: public Subject
{
public:
	Proxy();
	virtual ~Proxy();
	virtual void Request();
private:
	RealSubject* m_pRealSubject;
};
#endif // __DMPROXY__H__
