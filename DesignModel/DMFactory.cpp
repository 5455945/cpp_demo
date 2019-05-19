// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMFactory.cpp
// FileTarget    : DMFactory.cpp
// Description   : Factory 设置模式
//                 定义一个用于创建对象的接口，让子类决定实例化哪一个类。Factory Method使一个类的实例化延迟到其子类。
// 
// 抽象基类:
// 1)Product:创建出来的对象的抽象基类.
// 2)Factory创建对象的工厂方法的抽象基类.
// 
// 接口函数:
// 1)Creator::FactoryMethod:纯虚函数,由派生类实现,创建出对应的Product.
// 
// version        date        Author        Description
// 0001-0001      2013-02-27  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMFactory.h"
#include <iostream>
using namespace std;
ConcreteProduct::ConcreteProduct()
{
	std::cout << "construction of ConcreteProduct\n";
}
ConcreteProduct::~ConcreteProduct()
{
	std::cout << "destruction of ConcreteProduct\n";
}
void Creator::AnOperation()
{
	Product* p = FactoryMethod();
	std::cout << "an operation of product\n";
}
ConcreteCreator::ConcreteCreator()
{
	std::cout << "construction of ConcreteCreator\n";
}
ConcreteCreator::~ConcreteCreator()
{
	std::cout << "destruction of ConcreteCreator\n";
}
Product* ConcreteCreator::FactoryMethod()
{
	return new ConcreteProduct();
}
