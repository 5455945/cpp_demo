// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMDecorator.h
// FileTarget    : DMDecorator.h
// Description   : Decorator 模式
// 
// 作用:
// 动态地给一个对象添加一些额外的职责。就增加功能来说，Decorator 模式相比生成子类更为灵活。
// 抽象基类:
// 1)Component:定义一个对象接口,可以为这个接口动态的添加职责.
// 2)Decorator:维持一个指向Component的指针,并且有一个和Component一致的接口函数.
// 接口函数:
// 1)Component::Operation:这个接口函数由Component声明,因此Component的派生类都需要实现,可以在这个接口函数的基础上给它动态添加职责.
// 解析:
// Decorator的派生类可以为ConcreateComponent类的对象动态的添加职责,或者可以这么说:Decorator的派生类装饰ConcreateComponent类的对象.
// 具体是这么实现的,首先初始化一个ConcreateComponent类的对象(被装饰者),采用这个对象去生成一个Decorator对象(装饰者),之后对Operation函数
// 的调用则是对这个Decorator对象成员函数的多态调用.这里的实现要点是Decorator类和ConcreateComponent类都继承自Component,从而两者的接
// 口函数是一致的;其次,Decorator维护了一个指向Component的指针,从而可以实现对Component::Operation函数的动态调用.
// 
// version        date        Author        Description
// 0001-0001      2013-03-04  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __DECORATOR__H__
#define __DECORATOR__H__
namespace Decorator    // 因为Component和Composite模式里的类重名
{
	// 抽象基类，定义一个对象接口，可以为这个接口动态的添加职责
	class Component
	{
	public:
		Component(){};
		virtual ~Component(){};
		// 纯虚函数，由派生类实现
		virtual void Operation() = 0;
	};
	// 抽象基类，维护一个指向Component对象的指针
	class Decorator
		: public Component
	{
	public:
		Decorator(Component *pComponent) : m_pComponent(pComponent){};
		virtual ~Decorator();
	protected:
		Component* m_pComponent;
	};
	// 派生自Component，在这里表示需要给他动态添加职责的类
	class ConcreteComponent
		: public Component
	{
	public:
		ConcreteComponent(){};
		virtual ~ConcreteComponent(){};
		virtual void Operation();
	};
	// 派生自Decorator,这里代表为ConcreteComponent动态添加职责的类
	class ConcreteDecorator
		: public Decorator
	{
	public:
		ConcreteDecorator(Component* pComponent) : Decorator(pComponent){};
		virtual ~ConcreteDecorator(){};
		virtual void Operation();
	private:
		void AddedBehavior();
	};
};
#endif // __DMDECORATOR__H__
