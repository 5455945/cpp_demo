// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMPrototype.h
// FileTarget    : DMPrototype.h
// Description   : Prototype 模式
// 用原型实例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。
// 抽象基类:
// 1)Prototype:虚拟基类,所有原型的基类,提供Clone接口函数
// 
// 接口函数:
// 1)Prototype::Clone函数:纯虚函数,根据不同的派生类来实例化创建对象.
// 
// 解析:
// Prototype模式其实就是常说的"虚拟构造函数"一个实现,C++的实现机制中并
// 没有支持这个特性,但是通过不同派生类实现的Clone接口函数可以完成与"虚
// 拟构造函数"同样的效果.举一个例子来解释这个模式的作用,假设有一家店铺是
// 配钥匙的,他对外提供配制钥匙的服务(提供Clone接口函数),你需要配什么钥
// 匙它不知道只是提供这种服务,具体需要配什么钥匙只有到了真正看到钥匙的原
// 型才能配好.也就是说,需要一个提供这个服务的对象,同时还需要一个原型(Prot
// otype),不然不知道该配什么样的钥匙.
// 
// version        date        Author        Description
// 0001-0001      2013-02-28  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __DMPROTOTYPE__H__
#define __DMPROTOTYPE__H__
class Prototype
{
public:
	Prototype(){};
	virtual ~Prototype(){};
	virtual Prototype* Clone() = 0;
};
// 派生自Prototype，实现Clone方法
class ConcretePrototype1
	: public Prototype
{
public:
	ConcretePrototype1();
	ConcretePrototype1(const ConcretePrototype1&);
	virtual ~ConcretePrototype1();
	virtual Prototype* Clone();
};
// 派生自Prototype,实现Clone方法
class ConcretePrototype2
	: public Prototype
{
public:
	ConcretePrototype2();
	ConcretePrototype2(const ConcretePrototype2&);
	virtual ~ConcretePrototype2();
	virtual Prototype* Clone();
};
#endif //__DMPROTOTYPE__H__
