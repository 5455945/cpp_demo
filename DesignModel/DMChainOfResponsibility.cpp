// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMChainOfResponsibility.cpp
// FileTarget    : DMChainOfResponsibility.cpp
// Description   : ChainOfResponsibility 模式
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-03-05  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMChainOfResponsibility.h"
#include <iostream>
Handler::Handler(Handler *pSuccessor /* = NULL */) : m_pSuccessor(pSuccessor)
{
}
Handler::~Handler()
{
	if(m_pSuccessor)
	{
		delete m_pSuccessor;
		m_pSuccessor = NULL;
	}
}
void ConcreteHandler1::HandleRequest()
{
	if(NULL != m_pSuccessor)
	{
		m_pSuccessor->HandleRequest();
	}
	else
	{
		std::cout << "HandleRequest by ConcreteHandler1\n";
	}
}
void ConcreteHandler2::HandleRequest()
{
	if(NULL != m_pSuccessor)
	{
		m_pSuccessor->HandleRequest();
	}
	else
	{
		std::cout << "HandleRequest by ConcreteHandler2\n";
	}
}
