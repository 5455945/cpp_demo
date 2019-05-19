// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMComposite.h
// FileTarget    : DMComposite.h
// Description   : Composite ģʽ
// 
// ����:
// ��������ϳ����νṹ�Ա�ʾ������-���塱�Ĳ�νṹ��Compositeʹ���û��Ե����������϶����ʹ�þ���һ���ԡ�
// 
// �������:
// 1)Component:Ϊ����еĶ��������ӿ�,�������๲�нӿڵ�ȱʡ��Ϊ(����
// ���Add,Remove,GetChild����),����һ���ӿں������Է���Component�������.
// 
// �ӿں���:
// 1)Component::Operatation:�����˸���������е���Ϊ�ӿ�,�ɸ�������ľ���ʵ��.
// 2)Component::Add���һ�������
// 3)Component::Remove::ɾ��һ�������.
// 4)Component::GetChild:����������ָ��.
// 
// ����:
// Componentģʽ��Ϊ������֮��ĵݹ�����ṩ�˽���İ취,����Ҫ��Ϊ
// ����������,���е�Leaf��Ҷ�ӽ��,Ҳ���ǲ�����������Ľ��,��Composit
// e�Ǻ������������.��һ��������˵�����ģʽ,��UI�������,������Ŀؼ�
// ������Button,Edit�����Ŀؼ�,�൱���������Leaf���,���Ƚϸ��ӵĿؼ�
// ����List����Կ���������Щ�����������������Ŀؼ�,�൱�������Comp
// osite,����֮����һЩ��Ϊ��������ͬ��,�����ڿؼ�����һ�����,�ƶ�������
// �ȵ�,��Щ�����Զ���Ϊ��������еĽӿ��麯��,�ɸ���������ȥʵ��֮,��Щ
// �����е���Ϊ���������Operation����,�����,ɾ���Ƚ��������ϵĲ���
// ֻ�з�Ҷ�ӽ��ſ�����,�������������ֻ���ṩ�ӿڶ���Ĭ�ϵ�ʵ����ʲô
// ������.
// 
// version        date        Author        Description
// 0001-0001      2013-03-01  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __COMPOSITE__H__
#define __COMPOSITE__H__
#include <list>

// ����еĳ������
class Component
{
public:
	Component(){};
	virtual ~Component(){};
	// ���麯����ֻ���ṩ�ӿڣ�û��Ĭ�ϵ�ʵ��
	virtual void Operation() = 0;
	// �麯�����ṩ�ӿڣ���Ĭ�ϵ�ʵ�־���ʲô������
	virtual void Add(Component* pChild);
	virtual void Remove(Component* pChild);
	virtual Component* GetChild(int nIndex);
};
// ������Component, �����е�Ҷ������Ļ���
class Leaf
	: public Component
{
public:
	Leaf(){};
	virtual ~Leaf(){};
	virtual void Operation();
};
// ������Component�������еĺ�����������������
class Composite
	: public Component
{
public:
	Composite(){};
	virtual ~Composite();
	virtual void Operation();
	virtual void Add(Component* pChild);
	virtual void Remove(Component* pChild);
	virtual Component* GetChild(int nIndex);
private:
	// ����list����ȥ���������
	std::list <Component*> m_ListOfComponent;
};
#endif //__COMPOSITE__H__
