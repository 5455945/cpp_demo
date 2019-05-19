// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMStrategy.cpp
// FileTarget    : DMStrategy.cpp
// Description   : Strategy 模式
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       新建
// 
// *********************************************************************************************
#include <iostream>
#include "DMStrategy.h"
Context::Context(Strategy* pStrategy) : m_pStrategy(pStrategy)
{
}
Context::~Context()
{
	if(m_pStrategy)
	{
		delete m_pStrategy;
		m_pStrategy = NULL;
	}
}
void Context::ContextInterface()
{
	if(NULL != m_pStrategy)
	{
		m_pStrategy->AlgorithmInterface();
	}
}
void ConcreteStrategyA::AlgorithmInterface()
{
	std::cout << "AlgorithmInterface Implemented by ConcreteStrategyA\n";
}
