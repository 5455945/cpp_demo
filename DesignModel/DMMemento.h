// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMMemento.h
// FileTarget    : DMMemento.h
// Description   : Memento 模式
//                 
// 作用:
// 在不破坏封装性的前提下,捕获一个对象的内部状态,并在该对象之外保存这个状态.这样以后就可将该对象恢复到原先保存的状态.
// 
// 解析:
// Memento模式中封装的是需要保存的状态,当需要恢复的时候才取出来进行恢
// 复.原理很简单,实现的时候需要注意一个地方:窄接口和宽接口.所谓的宽接口就
// 是一般意义上的接口,把对外的接口作为public成员;而窄接口反之,把接口作为
// private成员,而把需要访问这些接口函数的类作为这个类的友元类,也就是说接
// 口只暴露给了对这些接口感兴趣的类,而不是暴露在外部.下面的实现就是窄接口
// 的方法来实现的.
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __MEMENTO__H__
#define __MEMENTO__H__
#include <string>
typedef std::string State;
class Memento;
class Originator
{
public:
	Originator(const State& rState);
	Originator();
	~Originator();
	Memento* CreatorMemento();
	void SetMemento(Memento* pMemento);
	State GetState();
	void SetState(const State& rState);
	void RestoreState(Memento* pMemento);
	void PrintState();
private:
	State m_State;
};
// 把Memento接口函数设置为私有，而Originator是他的友元
// 保证只有Originator可以访问Memento
class Memento
{
private:
	friend class Originator;
	Memento(const State& rState);
	void SetState(const State& rState);
	State GetState();
	State m_State;
};
#endif //__MEMENTO__H__
