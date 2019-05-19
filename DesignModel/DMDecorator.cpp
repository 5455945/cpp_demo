// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMDecorator.cpp
// FileTarget    : DMDecorator.cpp
// Description   : Decorator 模式
// 
// version        date        Author        Description
// 0001-0001      2013-03-04  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMDecorator.h"
#include <iostream>
namespace Decorator
{
	Decorator::~Decorator()
	{
		if(m_pComponent)
		{
			delete m_pComponent;
			m_pComponent = NULL;
		}
	}
	void ConcreteComponent::Operation()
	{
		std::cout << "Operattion by ConcreteComponent\n";
	}
	void ConcreteDecorator::Operation()
	{
		m_pComponent->Operation();
		AddedBehavior();
	}
	void ConcreteDecorator::AddedBehavior()
	{
		std::cout << "AddedBehavior of ComncreteDecorator\n";
	}
}
