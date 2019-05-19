// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMState.cpp
// FileTarget    : DMState.cpp
// Description   : State 模式
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       新建
// 
// *********************************************************************************************
#include <iostream>
#include "DMState.h"
namespace CSTATE
{
	Context::Context(State* pState) : m_pState(pState)
	{
	}
	Context::~Context()
	{
		if(m_pState)
		{
			delete m_pState;
			m_pState = NULL;
		}
	}
	void Context::Request()
	{
		if(NULL != m_pState)
		{
			m_pState->Handle(this);
		}
	}
	void Context::ChangeState(State* pState)
	{
		if(NULL != m_pState)
		{
			delete m_pState;
			m_pState = NULL;
		}
		m_pState = pState;
	}
	void ConcreteStateA::Handle(Context* pContext)
	{
		std::cout << "Handle by ConcreteStateA\n";
		if(NULL != pContext)
		{
			pContext->ChangeState(new ConcreteStateB());
		}
	}
	void ConcreteStateB::Handle(Context* pContext)
	{
		std::cout << "Handle by ConcreteStateB\n";
		if(NULL != pContext)
		{
			pContext->ChangeState(new ConcreteStateA());
		}
	}
};
