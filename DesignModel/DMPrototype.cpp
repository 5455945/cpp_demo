// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMPrototype.cpp
// FileTarget    : DMPrototype.cpp
// Description   : Prototype 模式
// 
// version        date        Author        Description
// 0001-0001      2013-02-28  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMPrototype.h"
#include <iostream>
ConcretePrototype1::ConcretePrototype1()
{
	std::cout << "construction of ConcretePrototype1\n";
}
ConcretePrototype1::~ConcretePrototype1()
{
	std::cout << "destruction of ConcretePrototype1\n";
}
ConcretePrototype1::ConcretePrototype1(const ConcretePrototype1 &)
{
	std::cout << "copy constuction of ConcretePrototype1\n";
}
Prototype* ConcretePrototype1::Clone()
{
	return new ConcretePrototype1(*this);
}
ConcretePrototype2::ConcretePrototype2()
{
	std::cout << "construction of ConcretePrototype2\n";
}
ConcretePrototype2::~ConcretePrototype2()
{
	std::cout << "destruction of ConcretePrototype2\n";
}
ConcretePrototype2::ConcretePrototype2(const ConcretePrototype2&)
{
	std::cout << "copy construction of ConcretePrototype2\n";
}
Prototype* ConcretePrototype2::Clone()
{
	return new ConcretePrototype2(*this);
}
