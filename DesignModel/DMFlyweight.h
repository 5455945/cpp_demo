// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMFlyweight.h
// FileTarget    : DMFlyweight.h
// Description   : Flyweight 模式
//                 
// 作用:
// 运用共享技术有效地支持大量细粒度的对象。
// 
// 解析:
// Flyweight模式在大量使用一些可以被共享的对象的时候经常使用.比如,在QQ
// 聊天的时候很多时候你懒得回复又不得不回复的时候,一般会用一些客套的话语
// 敷衍别人,如"呵呵","好的"等等之类的,这些简单的答复其实每个人都是提前定
// 义好的,在使用的时候才调用出来.Flyweight就是基于解决这种问题的思路而
// 产生的,当需要一个可以在其它地方共享使用的对象的时候,先去查询是否已经
// 存在了同样的对象,如果没有就生成之有的话就直接使用.因此,Flyweight模式
// 和Factory模式也经常混用.
// 
// 实现:
// 需要说明的是下面的实现仅仅实现了对可共享对象的使用,非可共享对象的使用
// 没有列出,因为这个不是Flyweight模式的重点.这里的实现要点是采用一个list
// 链表来保存这些可以被共享的对象,需要使用的时候就到链表中查询是不是已经
// 存在了,如果不存在就初始化一个,然后返回这个对象的指针.
// 
// version        date        Author        Description
// 0001-0001      2013-03-08  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __FLYWEIGHT__H__
#define __FLYWEIGHT__H__
#include <string>
#include <list>
typedef std::string STATE;
class Flyweight
{
public:
	virtual ~Flyweight(){};
	STATE GetIntrinsicState();
	virtual void Operation(STATE& ExtrinsicState) = 0;
protected:
	Flyweight(const STATE& state) : m_State(state){};
private:
	STATE m_State;
};
class FlyweightFactory
{
public:
	FlyweightFactory(){};
	~FlyweightFactory();
	Flyweight* GetFlyweight(const STATE& key);
private:
	std::list<Flyweight*> m_listFlyweight;
};
class ConcreteFlyweight
	: public Flyweight
{
public:
	ConcreteFlyweight(const STATE& state) : Flyweight(state){};
	virtual ~ConcreteFlyweight(){};
	virtual void Operation(STATE& ExtrinsticState);
};
#endif //__FLYWEIGHT__H__
