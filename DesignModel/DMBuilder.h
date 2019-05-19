// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMBuilder.h
// FileTarget    : DMBuilder.h
// Description   : Builder 模式
// 将一个复杂对象的构建与它的表示分离，使得同样的构建过程可以创建不同的表示。
// 1)当创建复杂对象的算法应该独立于该对象的组成部分以及它们的装配方式时。
// 2)当构造过程必须允许被构造的对象有不同的表示时。
// 
// 抽象基类:
// 1)Builder:这个基类是全部创建对象过程的抽象,提供构建不同组成部分的接口函数
// 接口:
// 1)Builder::BuildPartA,Builder::BuildPartB:是对一个对象不同部分的构建函数接口,Builder的派生类来具体实现.
// 另外还有一个需要注意的函数,就是Director::Construct函数,这个函数里面
// 通过调用上面的两个接口函数完成对象的构建--也就是说各个不同部分装配的
// 过程都是一致的(同样的调用的Construct函数),但是不同的构建方式会有不同
// 的表示(根据Builder的实际类型来决定如何构建,也就是多态)
// 
// version        date        Author        Description
// 0001-0001      2013-02-28  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __DMBUILDER__H__
#define __DMBUILDER__H__
// 虚拟基类，是所有Builder的基类，提供不同部分的构建接口函数
class Builder
{
public:
	Builder(){};
	virtual ~Builder(){};
	// 纯虚函数，提供构建不同部分的构建接口函数
	virtual void BuilderPartA() = 0;
	virtual void BuilderPartB() = 0;
};
// 使用Builder构建产品，构建产品的过程都一致，但是不同德builder有不同的实现
// 这个不同德实现通过不同的Builder派生类来实现，存有一个Builder的指针，通过这个来实现多态调用
class Director
{
public:
	Director(Builder * pBuilder);
	virtual ~Director();
	void Construct();
private:
	Builder* m_pBuilder;
};
// Builder的派生类，实现BuilderPartA和BuilderPartB接口函数
class ConcreteBuilder1
	: public Builder
{
public:
	ConcreteBuilder1(){};
	virtual ~ConcreteBuilder1(){};
	virtual void BuilderPartA();
	virtual void BuilderPartB();
};
// Builder派生类，实现BuilderPartA和BuilderPartB接口函数
class ConcreteBuilder2
	: public Builder
{
public:
	ConcreteBuilder2(){};
	virtual ~ConcreteBuilder2(){}
	virtual void BuilderPartA();
	virtual void BuilderPartB();
};
#endif // __DMBUILDER__H__
