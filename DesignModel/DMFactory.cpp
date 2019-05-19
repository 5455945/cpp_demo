// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMFactory.cpp
// FileTarget    : DMFactory.cpp
// Description   : Factory ����ģʽ
//                 ����һ�����ڴ�������Ľӿڣ����������ʵ������һ���ࡣFactory Methodʹһ�����ʵ�����ӳٵ������ࡣ
// 
// �������:
// 1)Product:���������Ķ���ĳ������.
// 2)Factory��������Ĺ��������ĳ������.
// 
// �ӿں���:
// 1)Creator::FactoryMethod:���麯��,��������ʵ��,��������Ӧ��Product.
// 
// version        date        Author        Description
// 0001-0001      2013-02-27  Zhangfj       �½�
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
