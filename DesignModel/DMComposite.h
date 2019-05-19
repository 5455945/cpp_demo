// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMComposite.h
// FileTarget    : DMComposite.h
// Description   : Composite 模式
// 
// 作用:
// 将对象组合成树形结构以表示“部分-整体”的层次结构。Composite使得用户对单个对象和组合对象的使用具有一致性。
// 
// 抽象基类:
// 1)Component:为组合中的对象声明接口,声明了类共有接口的缺省行为(如这
// 里的Add,Remove,GetChild函数),声明一个接口函数可以访问Component的子组件.
// 
// 接口函数:
// 1)Component::Operatation:定义了各个组件共有的行为接口,由各个组件的具体实现.
// 2)Component::Add添加一个子组件
// 3)Component::Remove::删除一个子组件.
// 4)Component::GetChild:获得子组件的指针.
// 
// 解析:
// Component模式是为解决组件之间的递归组合提供了解决的办法,它主要分为
// 两个派生类,其中的Leaf是叶子结点,也就是不含有子组件的结点,而Composit
// e是含有子组件的类.举一个例子来说明这个模式,在UI的设计中,最基本的控件
// 是诸如Button,Edit这样的控件,相当于是这里的Leaf组件,而比较复杂的控件
// 比如List则可以看做是由这些基本的组件组合起来的控件,相当于这里的Comp
// osite,它们之间有一些行为含义是相同的,比如在控件上作一个点击,移动操作等
// 等的,这些都可以定义为抽象基类中的接口虚函数,由各个派生类去实现之,这些
// 都会有的行为就是这里的Operation函数,而添加,删除等进行组件组合的操作
// 只有非叶子结点才可能有,所以虚拟基类中只是提供接口而且默认的实现是什么
// 都不做.
// 
// version        date        Author        Description
// 0001-0001      2013-03-01  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __COMPOSITE__H__
#define __COMPOSITE__H__
#include <list>

// 组合中的抽象基类
class Component
{
public:
	Component(){};
	virtual ~Component(){};
	// 纯虚函数，只是提供接口，没有默认的实现
	virtual void Operation() = 0;
	// 虚函数，提供接口，有默认的实现就是什么都不做
	virtual void Add(Component* pChild);
	virtual void Remove(Component* pChild);
	virtual Component* GetChild(int nIndex);
};
// 派生自Component, 是其中的叶子组件的基类
class Leaf
	: public Component
{
public:
	Leaf(){};
	virtual ~Leaf(){};
	virtual void Operation();
};
// 派生自Component，是其中的含有子组件的组件基类
class Composite
	: public Component
{
public:
	Composite(){};
	virtual ~Composite();
	virtual void Operation();
	virtual void Add(Component* pChild);
	virtual void Remove(Component* pChild);
	virtual Component* GetChild(int nIndex);
private:
	// 采用list容器去保存子组件
	std::list <Component*> m_ListOfComponent;
};
#endif //__COMPOSITE__H__
