// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMSingleton.cpp
// FileTarget    : DMSingleton.cpp
// Description   : Singleton 模式
// 
// version        date        Author        Description
// 0001-0001      2013-02-28  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMSingleton.h"
#include <iostream>

Singleton* Singleton::m_pSingleton = NULL;

Singleton::Singleton()
{
	std::cout << "construction of Singleton.\n";
}
Singleton::~Singleton()
{
	std::cout << "destruction of Singleton.\n";
	if(m_pSingleton)
	{
		delete m_pSingleton;
		m_pSingleton = NULL;
	}
}
void Singleton::Test()
{
	std::cout << "Call Singleton::Test()\n";
}
Singleton* Singleton::Instance()
{
    if(NULL == m_pSingleton)
	{
		m_pSingleton = new Singleton();
	}
	return m_pSingleton;
}