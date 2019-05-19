// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMTemplateMethod.cpp
// FileTarget    : DMTemplateMethod.cpp
// Description   : TemplateMethod 模式
// 
// version        date        Author        Description
// 0001-0001      2013-03-04  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMTemplateMethod.h"
#include <iostream>
void AbstractClass::TemplateMethod()
{
	PrimitiveOperation1();
	PrimitiveOperation2();
}
void ConcreteClass::PrimitiveOperation1()
{
	std::cout << "PrimitiveOperation1 by ConcreteClass\n";
}
void ConcreteClass::PrimitiveOperation2()
{
	std::cout << "PrimitiveOperation2 by ConcreteClass\n";
}
