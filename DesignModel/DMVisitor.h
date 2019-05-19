// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMVisitor.h
// FileTarget    : DMVisitor.h
// Description   : Visitor 模式
//                 
// 作用:
// 表示一个作用于某对象结构中的各元素的操作.它使你可以在不改变各元素的类的前提下定义作用于这些元素的新操作.
// 
// 解析:
// Visitor模式把对结点的访问封装成一个抽象基类,通过派生出不同的类生成新
// 的访问方式.在实现的时候,在visitor抽象基类中声明了对所有不同结点进行访
// 问的接口函数,如图中的VisitConcreateElementA函数等,这样也造成了Visit
// or模式的一个缺陷--新加入一个结点的时候都要添加Visitor中的对其进行访问
// 接口函数,这样使得所有的Visitor及其派生类都要重新编译了,也就是说Visitor
// 模式一个缺点就是添加新的结点十分困难.另外,还需要指出的是Visitor模式采
// 用了所谓的"双重分派"的技术,拿上图来作为例子,要对某一个结点进行访问,首
// 先需要产生一个Element的派生类对象,其次要传入一个Visitor类派生类对象
// 来调用对应的Accept函数,也就是说,到底对哪种Element采用哪种Visitor访
// 问,需要两次动态绑定才可以确定下来
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __VISITOR__H__
#define __VISITOR__H__
class Visitor;
class Element
{
public:
	virtual ~Element(){};
	virtual void Accept(Visitor& Visitor) = 0;
protected:
	Element(){};
};
class ConcreteElementA : public Element
{
public:
	virtual ~ConcreteElementA(){};
	virtual void Accept(Visitor& rVisitor);
};
class ConcreteElementB : public Element
{
public:
	virtual ~ConcreteElementB(){};
	virtual void Accept(Visitor& rVisitor);
};
class Visitor
{
public:
	virtual ~Visitor(){};
	virtual void VisitConcreteElementA(ConcreteElementA* pConcreteElementA) = 0;
	virtual void VisitConcreteElementB(ConcreteElementB* pConcreteElementB) = 0;
protected:
	Visitor(){};
};
class ConcreteVisitorA : public Visitor
{
public:
	~ConcreteVisitorA(){};
	virtual void VisitConcreteElementA(ConcreteElementA* pConcreteElementA);
	virtual void VisitConcreteElementB(ConcreteElementB* pConcreteElementB);
};
class ConcreteVisitorB : public Visitor
{
public:
	virtual ~ConcreteVisitorB(){};
	virtual void VisitConcreteElementA(ConcreteElementA* pConcreteElementA);
	virtual void VisitConcreteElementB(ConcreteElementB* pConcreteElementB);
};
#endif //__VISITOR__H__
