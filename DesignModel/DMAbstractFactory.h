// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMAbstractFactory.h
// FileTarget    : DMAbstractFactory.h
// Description   : AbstractFactory 模式
//    提供一个创建一系列相关或相互依赖对象的接口，而无需指定它们具体的类。
// 抽象基类:
// 1)ProductA,ProductB:分别代表不同类型的产品,而它们的派生类则是这种产品的一个实现.
// 2)AbstractFactory:生产这一系列产品的一个抽象工厂,它的派生类是不同的
// 实现.
// 接口函数:
// 1)AbstractFactory::CreateProductA和AbstractFactory::CreateProductB:分别是生产不同产品的不同的实现,由各个派生出来的抽象工厂实现之.
// 解析:
// Abstract Factory模式和Factory最大的差别就是抽象工厂创建的是一系列相关的对象,其中创建的实现其实采用的就是Factory模式的方法,对于某个实现
// 的有一个派生出来的抽象工厂,另一个实现有另一个派生出来的工厂,等等.
// 可以举一个简单的例子来解释这个模式:比如,同样是鸡腿(ProductA)和汉堡(ProductB),它们都可以有商店出售(AbstractFactory),但是有不同的实现,有肯
// 德基(ConcreateFactory1)和麦当劳(ConcreateFactory2)两家生产出来的不同风味的鸡腿和汉堡(也就是ProductA 和ProductB的不同实现).
// 而负责生产汉堡和鸡腿的就是之前提过的Factory模式了.
// 抽象工厂需要特别注意的地方就是区分不同类型的产品和这些产品的不同实现.显而易见的,如果有n种产品同时有m中不同的实现,那么根据乘法原理可知有n
// *m个Factory模式的使用.
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-02-27  Zhangfj       新建
// 
// *********************************************************************************************

#ifndef __DMABSTRACTFACTORY__H__
#define __DMABSTRACTFACTORY__H__
// 抽象基类AbstractProductA，代表产品A的抽象
class AbstractProductA
{
public:
	AbstractProductA(){}
	virtual ~AbstractProductA(){};
};
// 派生类ConcreteProductA1,继承自AbstractProductA,代表产品A的第一种实现
class ConcreteProductA1
	: public AbstractProductA
{
public:
	ConcreteProductA1();
	virtual ~ConcreteProductA1();
};
// 派生类ConcreteProductA2，继承自AbstractProductA,代表产品A的第二种实现
class ConcreteProductA2
	: public AbstractProductA
{
public:
	ConcreteProductA2();
	virtual ~ConcreteProductA2();
};
// 抽象基类AbstractProductB,代表产品B的抽象
class AbstractProductB
{
public:
	AbstractProductB(){}
	virtual ~AbstractProductB(){};
};
// 派生类ConcreteProductB1，继承自AbstractProductB，代表产品B的第一种实现
class ConcreteProductB1
	:public AbstractProductB
{
public:
	ConcreteProductB1();
	virtual ~ConcreteProductB1();
};
// 派生类ConcreteProductB2,继承自AbstractProductB，代表产品B的第二种实现
class ConcreteProductB2
	: public AbstractProductB
{
public:
	ConcreteProductB2();
	virtual ~ConcreteProductB2();
};
// 抽象基类AbstractFactory，工厂的抽象类，生产产品A和产品B
class AbstractFactory
{
public:
	AbstractFactory(){}
	virtual ~AbstractFactory(){}
	virtual AbstractProductA* CreateProductA() = 0;
	virtual AbstractProductB* CreateProductB() = 0;
};
// 派生类ConcreteFactory1,继承自AbstractFactory,生产产品A和产品B的第一种实现
class ConcreteFactory1
	: public AbstractFactory
{
public:
	ConcreteFactory1();
	virtual ~ConcreteFactory1();
	virtual AbstractProductA* CreateProductA();
	virtual AbstractProductB* CreateProductB();
};
// 派生类ConcreteFactory2，继承自AbstractFactory，生产产品A和产品B的第二种实现
class ConcreteFactory2
	:public AbstractFactory
{
public:
	ConcreteFactory2();
	virtual ~ConcreteFactory2();
	virtual AbstractProductA* CreateProductA();
	virtual AbstractProductB* CreateProductB();
};
#endif //__DMABSTRACTFACTORY__H__
