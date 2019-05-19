// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DesignModel.cpp
// FileTarget    : DesignModel.cpp
// Description   : 设置模式 测试主程序
//                 
// "面向接口编程而不是对实现编程","优先采用组合而不是继承"
// UML结构图解释的类与类之间的关系,时序图解释的是各个对象的实现方式
// C++老手和C++新手的区别就是前者手背上有很多伤疤。
// 高内聚(Cohesion)，而是低耦合(Coupling)
// 面向对象中的封装、继承和多态、面向接口编程、优先使用组合而不是继承、将抽象和实现分
// 
// version        date        Author        Description
// 0001-0001      2013-02-27  Zhangfj       新建
// 
// *********************************************************************************************
#include "DMFactory.h"
#include "DMAbstractFactory.h"
#include "DMBuilder.h"
#include "DMPrototype.h"
#include "DMSingleton.h"
#include "DMAdapter.h"
#include "DMBridge.h"
#include "DMComposite.h"
#include "DMDecorator.h"
#include "DMProxy.h"
#include "DMTemplateMethod.h"
#include "DMChainOfResponsibility.h"
#include "DMFlyweight.h"
#include "DMCommand.h"
#include "DMObserver.h"
#include "DMStrategy.h"
#include "DMState.h"
#include "DMIterator.h"
#include "DMMemento.h"
#include "DMVisitor.h"
