// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMObserver.h
// FileTarget    : DMObserver.h
// Description   : Observer 模式
//                 
// 作用:
// 定义对象间的一种一对多的依赖关系,当一个对象的状态发生改变时,所有依赖于它的对象都得到通知并被自动更新.
// 
// 解析:
// Observer模式定义的是一种一对多的关系,这里的一就是图中的Subject类,而多则是Obesrver类,当Subject类的状态发生变化的时候通知与之对应的O
// besrver类们也去相应的更新状态,同时支持动态的添加和删除Observer对象的功能.Obesrver模式的实现要点是,第一一般subject类都是采用链表等容器
// 来存放Observer对象,第二抽取出Observer对象的一些公共的属性形成Observer基类,而Subject中保存的则是Observer类对象的指针,这样就使Subj
// ect和具体的Observer实现了解耦,也就是Subject不需要去关心到底是哪个Observer对放进了自己的容器中.生活中有很多例子可以看做是Observer模
// 式的运用,比方说,一个班有一个班主任(Subject),他管理手下的一帮学生(Observer),当班里有一些事情发生需要通知学生的时候,班主任要做的不是逐个学
// 生挨个的通知而是把学生召集起来一起通知,实现了班主任和具体学生的关系解耦.
// 
// version        date        Author        Description
// 0001-0001      2013-03-12  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __OBSERVER__H__
#define __OBSERVER__H__
#include <list>
namespace OBSERVER
{
	typedef int STATE;
	class Observer;
	// Subject 抽象基类，只需要知道Observer基类的声明就可以了
	class Subject
	{
	public:
		Subject() : m_nSubjectState(-1){};
		virtual ~Subject();
		void Notify();    // 通知对象改变状态
		void Attach(Observer* pObserver);    // 新增对象
		void Detach(Observer* pObserver);    // 删除对象
		// 虚拟函数，提供默认的实现，派生类可以自己实现覆盖基类的实现
		virtual void SetState(STATE nState);    // 设置状态
		virtual STATE GetState();    // 得到状态
	protected:
		STATE m_nSubjectState;    // 模拟保存Subject状态的变量
		std::list<Observer*> m_ListObserver;    // 保存Observer指针的链表
	};
	// Observer抽象基类
	class Observer
	{
	public:
		Observer() : m_nObserverState(-1){};
		virtual ~Observer(){};
		// 纯虚函数，各个派生类可能有不同的实现
		// 通知Observer状态发生了变化
		virtual void Update(Subject* pSubject) = 0;
	protected:
		STATE m_nObserverState;   // 模拟保存Observer状态的变量
	};
	// ConcreteSubject类，派生自Subject类
	class ConcreteSubject : public Subject
	{
	public:
		ConcreteSubject() : Subject() {};
		virtual ~ConcreteSubject(){};
		// 派生类自己实现覆盖基类的实现
		virtual void SetState(STATE nState);    // 设置状态
		virtual STATE GetState();    // 得到状态
	};
	// ConcreteObserver类派生自Observer
	class ConcreteObserver
		: public Observer
	{
	public:
		ConcreteObserver() : Observer(){};
		virtual ~ConcreteObserver(){};
		// 虚函数，实现基类提供的接口
		virtual void Update(Subject* pSubject);
	};
};
#endif //__OBSERVER__H__
