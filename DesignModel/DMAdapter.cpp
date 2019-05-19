// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMAdapter.cpp
// FileTarget    : DMAdapter.cpp
// Description   : Adapter 模式
// 
// version        date        Author        Description
// 0001-0001      2013-03-01  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMAdapter.h"
#include <iostream>
void Adaptee::SpecialRequest()
{
	std::cout << "SpecialRequest of Adaptee\n";
}
Adapter::Adapter(Adaptee* pAdaptee) : m_pAdaptee(pAdaptee)
{
}
Adapter::~Adapter()
{
	if(m_pAdaptee)
	{
		delete m_pAdaptee;
		m_pAdaptee = NULL;
	}
}
void Adapter::Request()
{
	std::cout << "Request of Adapter\n";
	m_pAdaptee->SpecialRequest();
}
