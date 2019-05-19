// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMProxy.cpp
// FileTarget    : DMProxy.cpp
// Description   : Proxy ģʽ
// 
// version        date        Author        Description
// 0001-0001      2013-03-04  Zhangfj       �½�
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
	// ��Ҫʹ��RealSubject��ʱ��ų�ʼ��
	if(NULL == m_pRealSubject)
	{
		std::cout << "Request By Proxy\n";
		m_pRealSubject = new RealSubject();
	}
	m_pRealSubject->Request();
}
