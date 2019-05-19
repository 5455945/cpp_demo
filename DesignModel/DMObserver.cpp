// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMObserver.cpp
// FileTarget    : DMObserver.cpp
// Description   : Observer ģʽ
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-03-12  Zhangfj       �½�
// 
// *********************************************************************************************
#include "DMObserver.h"
#include <iostream>
#include <algorithm>
namespace OBSERVER
{
	// Subject ���Ա������ʵ��
	void Subject::Attach(Observer* pObserver)
	{
		std::cout << "Attach an Observer\n";
		m_ListObserver.push_back(pObserver);
	}
	void Subject::Detach(Observer* pObserver)
	{
		std::list<Observer*>::iterator iter;
		iter = std::find(m_ListObserver.begin(), m_ListObserver.end(), pObserver);
		if(m_ListObserver.end() != iter)
		{
			m_ListObserver.erase(iter);
		}
		std::cout << "Detach an Observer\n";
	}
	void Subject::Notify()
	{
		std::cout << "Notify Observer's State\n";
		std::list<Observer*>::iterator iter1, iter2;
		for(iter1 = m_ListObserver.begin(), iter2 = m_ListObserver.end(); iter1 != iter2; ++iter1)
		{
			(*iter1)->Update(this);
		}
	}
	void Subject::SetState(STATE nState)
	{
		std::cout << "SetState By Subject\n";
		m_nSubjectState = nState;
	}
	STATE Subject::GetState()
	{
		std::cout << "GetState By Subject\n";
		return m_nSubjectState;
	}
	Subject::~Subject()
	{
		std::list<Observer*>::iterator iter1, iter2, temp;
		for(iter1 = m_ListObserver.begin(), iter2 = m_ListObserver.end(); iter1 != iter2; )
		{
			temp = iter1;
			++iter1;
			delete(*temp);
		}
		m_ListObserver.clear();
	}
	// ConcreteSubject ���Ա������ʵ��
	void ConcreteSubject::SetState(STATE nState)
	{
		std::cout << "SetState By ConcreteSubject\n";
		m_nSubjectState = nState;
	}
	STATE ConcreteSubject::GetState()
	{
		std::cout << "GetState By ConcreteSubject\n";
		return m_nSubjectState;
	}
	// ConcreteObserver ���Ա������ʵ��
	void ConcreteObserver::Update(Subject* pSubject)
	{
		if(NULL == pSubject)
		{
			return;
		}
		m_nObserverState = pSubject->GetState();
		std::cout << "The ObserverState is " << m_nObserverState << std::endl;
	}
};
