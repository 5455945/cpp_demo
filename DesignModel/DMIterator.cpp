// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMIterator.cpp
// FileTarget    : DMIterator.cpp
// Description   : Iterator 模式
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       新建
// 
// *********************************************************************************************
#include <iostream>
#include "DMIterator.h"
ConcreteAggregate::ConcreteAggregate(int nSize) : m_nSize(nSize), m_pData(NULL)
{
	if(m_nSize > 0)
	{
		m_pData = new DATA[m_nSize];
		for(int i = 0; i < nSize; i++)
		{
			m_pData[i] = i;
		}
	}
	else
	{
		m_nSize = 0;
		m_pData = NULL;
	}
}
ConcreteAggregate::~ConcreteAggregate()
{
	if(NULL != m_pData)
	{
		delete [] m_pData;
		m_pData = NULL;
	}
}
Iterator* ConcreteAggregate::CreateIterator(Aggregate* pAggregate)
{
	return new ConcreteIterator(this);
}
int ConcreteAggregate::GetSize()
{
	return m_nSize;
}
DATA ConcreteAggregate::GetItem(int nIndex)
{
	if(nIndex < m_nSize)
	{
		return m_pData[nIndex];
	}
	else
	{
		return -1;
	}
}
ConcreteIterator::ConcreteIterator(Aggregate* pAggregate)
: m_pConcreteAggregate(pAggregate), m_nIndex(0)
{
}
void ConcreteIterator::First()
{
	m_nIndex = 0;
}
void ConcreteIterator::Next()
{
	if(m_nIndex < m_pConcreteAggregate->GetSize())
	{
		++m_nIndex;
	}
}
bool ConcreteIterator::IsDone()
{
	return m_nIndex == m_pConcreteAggregate->GetSize();
}
DATA ConcreteIterator::CurrentItem()
{
	return m_pConcreteAggregate->GetItem(m_nIndex);
}
