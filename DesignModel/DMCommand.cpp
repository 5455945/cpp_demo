// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMCommand.cpp
// FileTarget    : DMCommand.cpp
// Description   : Command 模式
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-03-11  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMCommand.h"
#include <iostream>
void Receiver::Action()
{
	std::cout << "Receiver Action\n";
}
Invoker::Invoker(Command* pCommand) : m_pCommand(pCommand)
{
}
Invoker::~Invoker()
{
	if(m_pCommand)
	{
		delete m_pCommand;
		m_pCommand = NULL;
	}
}
void Invoker::Invoke()
{
	if(NULL != m_pCommand)
	{
		m_pCommand->Execute();
	}
}
ConcreteCommand::ConcreteCommand(Receiver* pReceiver) : m_pReceiver(pReceiver)
{
}
ConcreteCommand::~ConcreteCommand()
{
	if(m_pReceiver)
	{
		delete m_pReceiver;
		m_pReceiver = NULL;
	}
}
void ConcreteCommand::Execute()
{
	if(NULL != m_pReceiver)
	{
		m_pReceiver->Action();
	}
	std::cout << "Execute by ConcreteCommand\n";
}
