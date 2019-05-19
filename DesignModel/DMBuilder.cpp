// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMBuilder.cpp
// FileTarget    : DMBuilder.cpp
// Description   : Builder ģʽ
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-02-28  Zhangfj       �½�
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
// Construct ������ʾһ����������幹�����̣���ͬ�Ĳ���֮���װ�䷽ʽ����һ�µģ�
// ���ȹ���PartA�����PartB��ֻ�Ǹ��ݲ�ͬ�Ĺ����߻��в�ͬ�ı�ʾ
void Director::Construct()
{
	m_pBuilder->BuilderPartA();
	m_pBuilder->BuilderPartB();
}
