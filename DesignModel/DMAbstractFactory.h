// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMAbstractFactory.h
// FileTarget    : DMAbstractFactory.h
// Description   : AbstractFactory ģʽ
//    �ṩһ������һϵ����ػ��໥��������Ľӿڣ�������ָ�����Ǿ�����ࡣ
// �������:
// 1)ProductA,ProductB:�ֱ����ͬ���͵Ĳ�Ʒ,�����ǵ��������������ֲ�Ʒ��һ��ʵ��.
// 2)AbstractFactory:������һϵ�в�Ʒ��һ�����󹤳�,�����������ǲ�ͬ��
// ʵ��.
// �ӿں���:
// 1)AbstractFactory::CreateProductA��AbstractFactory::CreateProductB:�ֱ���������ͬ��Ʒ�Ĳ�ͬ��ʵ��,�ɸ������������ĳ��󹤳�ʵ��֮.
// ����:
// Abstract Factoryģʽ��Factory���Ĳ����ǳ��󹤳���������һϵ����صĶ���,���д�����ʵ����ʵ���õľ���Factoryģʽ�ķ���,����ĳ��ʵ��
// ����һ�����������ĳ��󹤳�,��һ��ʵ������һ�����������Ĺ���,�ȵ�.
// ���Ծ�һ���򵥵��������������ģʽ:����,ͬ���Ǽ���(ProductA)�ͺ���(ProductB),���Ƕ��������̵����(AbstractFactory),�����в�ͬ��ʵ��,�п�
// �»�(ConcreateFactory1)������(ConcreateFactory2)�������������Ĳ�ͬ��ζ�ļ��Ⱥͺ���(Ҳ����ProductA ��ProductB�Ĳ�ͬʵ��).
// ���������������ͼ��ȵľ���֮ǰ�����Factoryģʽ��.
// ���󹤳���Ҫ�ر�ע��ĵط��������ֲ�ͬ���͵Ĳ�Ʒ����Щ��Ʒ�Ĳ�ͬʵ��.�Զ��׼���,�����n�ֲ�Ʒͬʱ��m�в�ͬ��ʵ��,��ô���ݳ˷�ԭ���֪��n
// *m��Factoryģʽ��ʹ��.
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-02-27  Zhangfj       �½�
// 
// *********************************************************************************************

#ifndef __DMABSTRACTFACTORY__H__
#define __DMABSTRACTFACTORY__H__
// �������AbstractProductA�������ƷA�ĳ���
class AbstractProductA
{
public:
	AbstractProductA(){}
	virtual ~AbstractProductA(){};
};
// ������ConcreteProductA1,�̳���AbstractProductA,�����ƷA�ĵ�һ��ʵ��
class ConcreteProductA1
	: public AbstractProductA
{
public:
	ConcreteProductA1();
	virtual ~ConcreteProductA1();
};
// ������ConcreteProductA2���̳���AbstractProductA,�����ƷA�ĵڶ���ʵ��
class ConcreteProductA2
	: public AbstractProductA
{
public:
	ConcreteProductA2();
	virtual ~ConcreteProductA2();
};
// �������AbstractProductB,�����ƷB�ĳ���
class AbstractProductB
{
public:
	AbstractProductB(){}
	virtual ~AbstractProductB(){};
};
// ������ConcreteProductB1���̳���AbstractProductB�������ƷB�ĵ�һ��ʵ��
class ConcreteProductB1
	:public AbstractProductB
{
public:
	ConcreteProductB1();
	virtual ~ConcreteProductB1();
};
// ������ConcreteProductB2,�̳���AbstractProductB�������ƷB�ĵڶ���ʵ��
class ConcreteProductB2
	: public AbstractProductB
{
public:
	ConcreteProductB2();
	virtual ~ConcreteProductB2();
};
// �������AbstractFactory�������ĳ����࣬������ƷA�Ͳ�ƷB
class AbstractFactory
{
public:
	AbstractFactory(){}
	virtual ~AbstractFactory(){}
	virtual AbstractProductA* CreateProductA() = 0;
	virtual AbstractProductB* CreateProductB() = 0;
};
// ������ConcreteFactory1,�̳���AbstractFactory,������ƷA�Ͳ�ƷB�ĵ�һ��ʵ��
class ConcreteFactory1
	: public AbstractFactory
{
public:
	ConcreteFactory1();
	virtual ~ConcreteFactory1();
	virtual AbstractProductA* CreateProductA();
	virtual AbstractProductB* CreateProductB();
};
// ������ConcreteFactory2���̳���AbstractFactory��������ƷA�Ͳ�ƷB�ĵڶ���ʵ��
class ConcreteFactory2
	:public AbstractFactory
{
public:
	ConcreteFactory2();
	virtual ~ConcreteFactory2();
	virtual AbstractProductA* CreateProductA();
	virtual AbstractProductB* CreateProductB();
};
#endif //__DMABSTRACTFACTORY__H__
