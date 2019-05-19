// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMAbstractFactory.cpp
// FileTarget    : DMAbstractFactory.cpp
// Description   : AbstractFactory模式
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-02-27  Zhangfj       新建
// 
// *********************************************************************************************
#include <iostream>
#include "DMAbstractFactory.h"
ConcreteProductA1::ConcreteProductA1()
{
	std::cout << "construction of ConcreteProductA1\n";
}
ConcreteProductA1::~ConcreteProductA1()
{
	std::cout << "destruction of ConcreteProductA1\n";
}
ConcreteProductA2::ConcreteProductA2()
{
	std::cout << "construction of ConcreteProductA2\n";
}
ConcreteProductA2::~ConcreteProductA2()
{
	std::cout << "destruction of ConcreteProductA2\n";
}
ConcreteProductB1::ConcreteProductB1()
{
	std::cout << "construction of ConcreteProductB1\n";
}
ConcreteProductB1::~ConcreteProductB1()
{
	std::cout << "destruction of ConcreteProductB1\n";
}
ConcreteProductB2::ConcreteProductB2()
{
	std::cout << "construction of ConcreteProductB2\n";
}
ConcreteProductB2::~ConcreteProductB2()
{
	std::cout << "destruction of ConcreteProductB2\n";
}
ConcreteFactory1::ConcreteFactory1()
{
	std::cout << "construction of ConcreteFactory1\n";
}
ConcreteFactory1::~ConcreteFactory1()
{
	std::cout << "destruction of ConcreteFactory1\n";
}
AbstractProductA* ConcreteFactory1::CreateProductA()
{
	return new ConcreteProductA1();
}
AbstractProductB* ConcreteFactory1::CreateProductB()
{
	return new ConcreteProductB1();
}
ConcreteFactory2::ConcreteFactory2()
{
	std::cout << "construction of ConcreteFactory2\n";
}
ConcreteFactory2::~ConcreteFactory2()
{
	std::cout << "destruction of ConcreteFactory2\n";
}
AbstractProductA* ConcreteFactory2::CreateProductA()
{
	return new ConcreteProductA2();
}
AbstractProductB* ConcreteFactory2::CreateProductB()
{
	return new ConcreteProductB2();
}
