// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMComposite.cpp
// FileTarget    : DMComposite.cpp
// Description   : Composite 模式
// 
// version        date        Author        Description
// 0001-0001      2013-03-01  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMComposite.h"
#include <iostream>
#include <algorithm>
// Component成员函数的实现
void Component::Add(Component *pChild)
{
}
void Component::Remove(Component *pChild)
{
}
Component* Component::GetChild(int nIndex)
{
	return NULL;
}
// Leaf成员函数实现
void Leaf::Operation()
{
	std::cout << "Operation by Leaf\n";
}
// Composite成员函数实现
Composite::~Composite()
{
	std::list<Component*>::iterator iter1, iter2, temp;
	for(iter1 = m_ListOfComponent.begin(), iter2 = m_ListOfComponent.end(); iter1 != iter2;)
	{
		temp = iter1;
		++iter1;
		delete (*temp);
	}
}
void Composite::Add(Component *pChild)
{
	m_ListOfComponent.push_back(pChild);
}
void Composite::Remove(Component *pChild)
{
	std::list<Component*>::iterator iter;
	iter = find(m_ListOfComponent.begin(), m_ListOfComponent.end(), pChild);
	if(m_ListOfComponent.end() != iter)
	{
		m_ListOfComponent.erase(iter);
	}
}
Component* Composite::GetChild(int nIndex)
{
	if(nIndex <= 0 || nIndex > (int)m_ListOfComponent.size())
	{
		return NULL;
	}
	std::list<Component*>::iterator iter1, iter2;
	int i;
	for(i = 1, iter1 = m_ListOfComponent.begin(), iter2 = m_ListOfComponent.end(); iter1 != iter2; ++iter1, i++)
	{
		if(i == nIndex)
		{
			break;
		}
	}
	return *iter1;
}
void Composite::Operation()
{
	std::cout << "Operation by Composite\n";
	std::list<Component*>::iterator iter1, iter2;
	for(iter1 = m_ListOfComponent.begin(), iter2 = m_ListOfComponent.end(); iter1 != iter2; ++iter1)
	{
		(*iter1)->Operation();
	}
}
