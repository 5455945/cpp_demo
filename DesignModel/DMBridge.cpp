// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMBridge.cpp
// FileTarget    : DMBridge.cpp
// Description   : Bridge 模式
// 
// version        date        Author        Description
// 0001-0001      2013-03-01  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMBridge.h"
#include <iostream>

void ConcreteImplementorA::OperationImpl()
{
	std::cout << "Implementation by ConcreteImplementorA\n";
}
void ConcreteImplementorB::OperationImpl()
{
	std::cout << "Implementation by ConcreteImplementorB\n";
}
Abstraction::Abstraction(Implementor* pImplementor)
: m_pImplementor(pImplementor)
{
}
Abstraction::~Abstraction()
{
	if(m_pImplementor)
	{
		delete m_pImplementor;
		m_pImplementor = NULL;
	}
}
void Abstraction::Operation()
{
	m_pImplementor->OperationImpl();
}
