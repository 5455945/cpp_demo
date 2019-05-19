// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMVisitor.cpp
// FileTarget    : DMVisitor.cpp
// Description   : Visitor ģʽ
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       �½�
// 
// *********************************************************************************************
#include "DMVisitor.h"
#include <iostream>
void ConcreteElementA::Accept(Visitor& rVisitor)
{
	rVisitor.VisitConcreteElementA(this);
}
void ConcreteElementB::Accept(Visitor& rVisitor)
{
	rVisitor.VisitConcreteElementB(this);
}
void ConcreteVisitorA::VisitConcreteElementA(ConcreteElementA* pConcreteElementA)
{
	std::cout << "VisitConcreteElementA By ConcreteVisitorA\n";
}
void ConcreteVisitorA::VisitConcreteElementB(ConcreteElementB* pConcreteElementB)
{
	std::cout << "VisitConcreteElementB By ConcreteVisitorA\n";
}
void ConcreteVisitorB::VisitConcreteElementA(ConcreteElementA* pConcreteElementA)
{
	std::cout << "VisitConcreteElementA By ConcreteVisitorB\n";
}
void ConcreteVisitorB::VisitConcreteElementB(ConcreteElementB* pConcreteElementB)
{
	std::cout << "VisitorConcreteElementB By ConcreteVisitorB\n";
}
