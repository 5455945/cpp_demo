// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMBuilder.cpp
// FileTarget    : DMBuilder.cpp
// Description   : Builder 模式
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-02-28  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMBuilder.h"
#include <iostream>
void ConcreteBuilder1::BuilderPartA()
{
	std::cout << "BuilderPartA by ConcreteBuilder1\n";
}
void ConcreteBuilder1::BuilderPartB()
{
	std::cout << "BuilderPartB by ConcreteBuilder1\n";
}
void ConcreteBuilder2::BuilderPartA()
{
	std::cout << "BuilderPartA by ConcreteBuilder2\n";
}
void ConcreteBuilder2::BuilderPartB()
{
	std::cout << "BuilderPartB by ConcreteBuilder2\n";
}
Director::Director(Builder* pBuilder) : m_pBuilder(pBuilder)
{
}
Director::~Director()
{
	if(m_pBuilder != NULL)
	{
		delete m_pBuilder;
		m_pBuilder = NULL;
	}
}
// Construct 函数表示一个对象的整体构建过程，不同的部分之间的装配方式都是一致的，
// 首先构建PartA其次是PartB，只是根据不同的构建者会有不同的表示
void Director::Construct()
{
	m_pBuilder->BuilderPartA();
	m_pBuilder->BuilderPartB();
}
