// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMObserver.h
// FileTarget    : DMObserver.h
// Description   : Observer ģʽ
//                 
// ����:
// ���������һ��һ�Զ��������ϵ,��һ�������״̬�����ı�ʱ,�������������Ķ��󶼵õ�֪ͨ�����Զ�����.
// 
// ����:
// Observerģʽ�������һ��һ�Զ�Ĺ�ϵ,�����һ����ͼ�е�Subject��,��������Obesrver��,��Subject���״̬�����仯��ʱ��֪ͨ��֮��Ӧ��O
// besrver����Ҳȥ��Ӧ�ĸ���״̬,ͬʱ֧�ֶ�̬����Ӻ�ɾ��Observer����Ĺ���.Obesrverģʽ��ʵ��Ҫ����,��һһ��subject�඼�ǲ������������
// �����Observer����,�ڶ���ȡ��Observer�����һЩ�����������γ�Observer����,��Subject�б��������Observer������ָ��,������ʹSubj
// ect�;����Observerʵ���˽���,Ҳ����Subject����Ҫȥ���ĵ������ĸ�Observer�ԷŽ����Լ���������.�������кܶ����ӿ��Կ�����Observerģ
// ʽ������,�ȷ�˵,һ������һ��������(Subject),���������µ�һ��ѧ��(Observer),��������һЩ���鷢����Ҫ֪ͨѧ����ʱ��,������Ҫ���Ĳ������ѧ
// ��������֪ͨ���ǰ�ѧ���ټ�����һ��֪ͨ,ʵ���˰����κ;���ѧ���Ĺ�ϵ����.
// 
// version        date        Author        Description
// 0001-0001      2013-03-12  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __OBSERVER__H__
#define __OBSERVER__H__
#include <list>
namespace OBSERVER
{
	typedef int STATE;
	class Observer;
	// Subject ������ֻ࣬��Ҫ֪��Observer����������Ϳ�����
	class Subject
	{
	public:
		Subject() : m_nSubjectState(-1){};
		virtual ~Subject();
		void Notify();    // ֪ͨ����ı�״̬
		void Attach(Observer* pObserver);    // ��������
		void Detach(Observer* pObserver);    // ɾ������
		// ���⺯�����ṩĬ�ϵ�ʵ�֣�����������Լ�ʵ�ָ��ǻ����ʵ��
		virtual void SetState(STATE nState);    // ����״̬
		virtual STATE GetState();    // �õ�״̬
	protected:
		STATE m_nSubjectState;    // ģ�Ᵽ��Subject״̬�ı���
		std::list<Observer*> m_ListObserver;    // ����Observerָ�������
	};
	// Observer�������
	class Observer
	{
	public:
		Observer() : m_nObserverState(-1){};
		virtual ~Observer(){};
		// ���麯������������������в�ͬ��ʵ��
		// ֪ͨObserver״̬�����˱仯
		virtual void Update(Subject* pSubject) = 0;
	protected:
		STATE m_nObserverState;   // ģ�Ᵽ��Observer״̬�ı���
	};
	// ConcreteSubject�࣬������Subject��
	class ConcreteSubject : public Subject
	{
	public:
		ConcreteSubject() : Subject() {};
		virtual ~ConcreteSubject(){};
		// �������Լ�ʵ�ָ��ǻ����ʵ��
		virtual void SetState(STATE nState);    // ����״̬
		virtual STATE GetState();    // �õ�״̬
	};
	// ConcreteObserver��������Observer
	class ConcreteObserver
		: public Observer
	{
	public:
		ConcreteObserver() : Observer(){};
		virtual ~ConcreteObserver(){};
		// �麯����ʵ�ֻ����ṩ�Ľӿ�
		virtual void Update(Subject* pSubject);
	};
};
#endif //__OBSERVER__H__
