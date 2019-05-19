// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMTemplateMethod.h
// FileTarget    : DMTemplateMethod.h
// Description   : TemplateMethod 模式
// 
// 作用:
// 定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。TemplateMethod 使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。
// 抽象基类:
// 1)AbstractClass:抽象基类,定义算法的轮廓
// 解析:
// TemplateMethod 的关键在于在基类中定义了一个算法的轮廓,但是算法每一步具体的实现留给了派生类.但是这样也会造成设计的灵活性不高的缺点,因为
// 轮廓已经定下来了要想改变就比较难了,这也是为什么优先采用聚合而不是继承的原因.
// 
// version        date        Author        Description
// 0001-0001      2013-03-04  Zhangfj       新建
// 
// *********************************************************************************************
// 抽象基类，定义算法的轮廓
class AbstractClass
{
public:
	AbstractClass(){};
	virtual ~AbstractClass(){};
	// 这个函数中定义算法轮廓
	void TemplateMethod();
protected:
	// 纯虚函数，由派生类实现
	virtual void PrimitiveOperation1() = 0;
	virtual void PrimitiveOperation2() = 0;
};
// 继承自AbstractClass，实现算法
class ConcreteClass
	: public AbstractClass
{
public:
	ConcreteClass(){};
protected:
	virtual void PrimitiveOperation1();
	virtual void PrimitiveOperation2();
};
