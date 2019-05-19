// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMFactory.h
// FileTarget    : DMFactory.h
// Description   : Factory 模式
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-02-27  Zhangfj       新建
// 
// *********************************************************************************************

#ifndef __DMFACTORY__H__
#define __DMFACTORY__H__
class Product
{
public:
	Product(){}
	virtual ~Product(){}
};
class ConcreteProduct
	: public Product
{
public:
	ConcreteProduct();
	virtual ~ConcreteProduct();
};
class Creator
{
public:
	Creator(){}
	virtual ~Creator(){}
	void AnOperation();
protected:
	virtual Product* FactoryMethod() = 0;
};
class ConcreteCreator
	: public Creator
{
public:
	ConcreteCreator();
	virtual ~ ConcreteCreator();
protected:
	Product* FactoryMethod();
};
#endif // __DMFactory__H__
