// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMDecorator.h
// FileTarget    : DMDecorator.h
// Description   : Decorator ģʽ
// 
// ����:
// ��̬�ظ�һ���������һЩ�����ְ�𡣾����ӹ�����˵��Decorator ģʽ������������Ϊ��
// �������:
// 1)Component:����һ������ӿ�,����Ϊ����ӿڶ�̬�����ְ��.
// 2)Decorator:ά��һ��ָ��Component��ָ��,������һ����Componentһ�µĽӿں���.
// �ӿں���:
// 1)Component::Operation:����ӿں�����Component����,���Component�������඼��Ҫʵ��,����������ӿں����Ļ����ϸ�����̬���ְ��.
// ����:
// Decorator�����������ΪConcreateComponent��Ķ���̬�����ְ��,���߿�����ô˵:Decorator��������װ��ConcreateComponent��Ķ���.
// ��������ôʵ�ֵ�,���ȳ�ʼ��һ��ConcreateComponent��Ķ���(��װ����),�����������ȥ����һ��Decorator����(װ����),֮���Operation����
// �ĵ������Ƕ����Decorator�����Ա�����Ķ�̬����.�����ʵ��Ҫ����Decorator���ConcreateComponent�඼�̳���Component,�Ӷ����ߵĽ�
// �ں�����һ�µ�;���,Decoratorά����һ��ָ��Component��ָ��,�Ӷ�����ʵ�ֶ�Component::Operation�����Ķ�̬����.
// 
// version        date        Author        Description
// 0001-0001      2013-03-04  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __DECORATOR__H__
#define __DECORATOR__H__
namespace Decorator    // ��ΪComponent��Compositeģʽ���������
{
	// ������࣬����һ������ӿڣ�����Ϊ����ӿڶ�̬�����ְ��
	class Component
	{
	public:
		Component(){};
		virtual ~Component(){};
		// ���麯������������ʵ��
		virtual void Operation() = 0;
	};
	// ������࣬ά��һ��ָ��Component�����ָ��
	class Decorator
		: public Component
	{
	public:
		Decorator(Component *pComponent) : m_pComponent(pComponent){};
		virtual ~Decorator();
	protected:
		Component* m_pComponent;
	};
	// ������Component���������ʾ��Ҫ������̬���ְ�����
	class ConcreteComponent
		: public Component
	{
	public:
		ConcreteComponent(){};
		virtual ~ConcreteComponent(){};
		virtual void Operation();
	};
	// ������Decorator,�������ΪConcreteComponent��̬���ְ�����
	class ConcreteDecorator
		: public Decorator
	{
	public:
		ConcreteDecorator(Component* pComponent) : Decorator(pComponent){};
		virtual ~ConcreteDecorator(){};
		virtual void Operation();
	private:
		void AddedBehavior();
	};
};
#endif // __DMDECORATOR__H__
