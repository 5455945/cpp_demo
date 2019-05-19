// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMPrototype.h
// FileTarget    : DMPrototype.h
// Description   : Prototype ģʽ
// ��ԭ��ʵ��ָ��������������࣬����ͨ��������Щԭ�ʹ����µĶ���
// �������:
// 1)Prototype:�������,����ԭ�͵Ļ���,�ṩClone�ӿں���
// 
// �ӿں���:
// 1)Prototype::Clone����:���麯��,���ݲ�ͬ����������ʵ������������.
// 
// ����:
// Prototypeģʽ��ʵ���ǳ�˵��"���⹹�캯��"һ��ʵ��,C++��ʵ�ֻ����в�
// û��֧���������,����ͨ����ͬ������ʵ�ֵ�Clone�ӿں������������"��
// �⹹�캯��"ͬ����Ч��.��һ���������������ģʽ������,������һ�ҵ�����
// ��Կ�׵�,�������ṩ����Կ�׵ķ���(�ṩClone�ӿں���),����Ҫ��ʲôԿ
// ������֪��ֻ���ṩ���ַ���,������Ҫ��ʲôԿ��ֻ�е�����������Կ�׵�ԭ
// �Ͳ������.Ҳ����˵,��Ҫһ���ṩ�������Ķ���,ͬʱ����Ҫһ��ԭ��(Prot
// otype),��Ȼ��֪������ʲô����Կ��.
// 
// version        date        Author        Description
// 0001-0001      2013-02-28  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __DMPROTOTYPE__H__
#define __DMPROTOTYPE__H__
class Prototype
{
public:
	Prototype(){};
	virtual ~Prototype(){};
	virtual Prototype* Clone() = 0;
};
// ������Prototype��ʵ��Clone����
class ConcretePrototype1
	: public Prototype
{
public:
	ConcretePrototype1();
	ConcretePrototype1(const ConcretePrototype1&);
	virtual ~ConcretePrototype1();
	virtual Prototype* Clone();
};
// ������Prototype,ʵ��Clone����
class ConcretePrototype2
	: public Prototype
{
public:
	ConcretePrototype2();
	ConcretePrototype2(const ConcretePrototype2&);
	virtual ~ConcretePrototype2();
	virtual Prototype* Clone();
};
#endif //__DMPROTOTYPE__H__
