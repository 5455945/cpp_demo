// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMAdapter.h
// FileTarget    : DMAdapter.h
// Description   : Adapter 模式
// 作用:
// 将一个类的接口转换成客户希望的另外一个接口。Adapter 模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。
// 解析:
// Adapter模式其实就是把完成同样的一个功能但是接口不能兼容的类桥接在一起使之可以在一起工作,这个模式使得复用旧的接口成为可能.
// 实现:
// Adapter模式有两种实现办法,一种是采用继承原有接口类的方法,一种是采用组合原有接口类的方法,这里采用的是第二种实现方法.
// 
// version        date        Author        Description
// 0001-0001      2013-03-01  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __ADAPTER__H__
#define __ADAPTER__H__
// 需要被Adapter的类
class Target
{
public:
	Target(){};
	virtual ~Target(){};
	virtual void Request() = 0;
};
// 与被Adapter对象提供不兼容接口的类
class Adaptee
{
public:
	Adaptee(){};
	~Adaptee(){};
	void SpecialRequest();
};
// 进行Adapter的类，采用聚合原有接口类的方式
class Adapter
	: public Target
{
public:
	Adapter(Adaptee* pAdaptee);
	virtual ~Adapter();
	virtual void Request();
private:
	Adaptee* m_pAdaptee;
};
#endif// __ADAPTER__H__
