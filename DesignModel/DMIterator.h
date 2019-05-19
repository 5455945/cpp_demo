// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMIterator.h
// FileTarget    : DMIterator.h
// Description   : Iterator 模式
//                 
// 作用:
// 提供一种方法顺序访问一个聚合对象中各个元素,而又不需暴露该对象的内部表示.
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __ITERATOR__H__
#define __ITERATOR__H__
typedef int DATA;
class Iterator;
// 容器抽象基类
class Aggregate
{
public:
	virtual ~Aggregate(){};
	virtual Iterator* CreateIterator(Aggregate* pAggregate) = 0;
	virtual int GetSize() = 0;
	virtual DATA GetItem(int nIndex) = 0;
};
// 迭代器的抽象基类
class Iterator
{
public:
	virtual ~Iterator(){};
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual DATA CurrentItem() = 0;
};
// 一个具体容器类
class ConcreteAggregate :public Aggregate
{
public:
	ConcreteAggregate(int nSzie);
	virtual ~ConcreteAggregate();
	virtual Iterator* CreateIterator(Aggregate* pAggregate);
	virtual int GetSize();
	virtual DATA GetItem(int nIndex);
private:
	int    m_nSize;
	DATA*  m_pData;
};
// 访问ConcreteAggregate容器类的迭代器类
class ConcreteIterator : public Iterator
{
public:
	ConcreteIterator(Aggregate* pAggregate);
	virtual ~ConcreteIterator(){};
	virtual void First();
	virtual void Next();
	virtual bool IsDone();
	virtual DATA CurrentItem();
private:
	Aggregate* m_pConcreteAggregate;
	int m_nIndex;
};
#endif //__ITERATOR__H__
