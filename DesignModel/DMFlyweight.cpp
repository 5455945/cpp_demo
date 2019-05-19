// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMFlyweight.cpp
// FileTarget    : DMFlyweight.cpp
// Description   : Flyweight 模式
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-03-08  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMFlyweight.h"
#include <iostream>
inline STATE Flyweight::GetIntrinsicState()
{
	return m_State;
}
FlyweightFactory::~FlyweightFactory()
{
	std::list<Flyweight*>::iterator iter1, iter2, temp;
	for(iter1 = m_listFlyweight.begin(), iter2 = m_listFlyweight.end(); iter1 != iter2;)
	{
		temp = iter1;
		++iter1;
		delete(*temp);
	}
	m_listFlyweight.clear();
}
Flyweight* FlyweightFactory::GetFlyweight(const STATE& key)
{
	std::list <Flyweight*>::iterator iter1, iter2;
	for(iter1 = m_listFlyweight.begin(), iter2 = m_listFlyweight.end(); iter1 != iter2; ++iter1)
	{
		if((*iter1)->GetIntrinsicState() == key)
		{
			std::cout << "The Flyweight:" << key << " already exists" << std::endl;
			return (*iter1);
		}
	}
	std::cout << "Creating a new Flyweight:" << key << std::endl;
	Flyweight* flyweight = new ConcreteFlyweight(key);
	m_listFlyweight.push_back(flyweight);
	return flyweight;
}
void ConcreteFlyweight::Operation(STATE& ExtrinsticState)
{
}
