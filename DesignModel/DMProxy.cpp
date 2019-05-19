// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMProxy.cpp
// FileTarget    : DMProxy.cpp
// Description   : Proxy 模式
// 
// version        date        Author        Description
// 0001-0001      2013-03-04  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMProxy.h"
#include <iostream>
RealSubject::RealSubject()
{
	std::cout << "Construction a RealSubject\n";
}
void RealSubject::Request()
{
	std::cout << "Request By RealSubject\n";
}
Proxy::Proxy() : m_pRealSubject(NULL)
{
	std::cout << "Construction a Proxy\n";
}
Proxy::~Proxy()
{
	if(m_pRealSubject)
	{
		delete m_pRealSubject;
		m_pRealSubject = NULL;
	}
}
void Proxy::Request()
{
	// 需要使用RealSubject的时候才初始化
	if(NULL == m_pRealSubject)
	{
		std::cout << "Request By Proxy\n";
		m_pRealSubject = new RealSubject();
	}
	m_pRealSubject->Request();
}
