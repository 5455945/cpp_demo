// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMAdapter.h
// FileTarget    : DMAdapter.h
// Description   : Adapter ģʽ
// ����:
// ��һ����Ľӿ�ת���ɿͻ�ϣ��������һ���ӿڡ�Adapter ģʽʹ��ԭ�����ڽӿڲ����ݶ�����һ��������Щ�����һ������
// ����:
// Adapterģʽ��ʵ���ǰ����ͬ����һ�����ܵ��ǽӿڲ��ܼ��ݵ����Ž���һ��ʹ֮������һ����,���ģʽʹ�ø��þɵĽӿڳ�Ϊ����.
// ʵ��:
// Adapterģʽ������ʵ�ְ취,һ���ǲ��ü̳�ԭ�нӿ���ķ���,һ���ǲ������ԭ�нӿ���ķ���,������õ��ǵڶ���ʵ�ַ���.
// 
// version        date        Author        Description
// 0001-0001      2013-03-01  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __ADAPTER__H__
#define __ADAPTER__H__
// ��Ҫ��Adapter����
class Target
{
public:
	Target(){};
	virtual ~Target(){};
	virtual void Request() = 0;
};
// �뱻Adapter�����ṩ�����ݽӿڵ���
class Adaptee
{
public:
	Adaptee(){};
	~Adaptee(){};
	void SpecialRequest();
};
// ����Adapter���࣬���þۺ�ԭ�нӿ���ķ�ʽ
class Adapter
	: public Target
{
public:
	Adapter(Adaptee* pAdaptee);
	virtual ~Adapter();
	virtual void Request();
private:
	Adaptee* m_pAdaptee;
};
#endif// __ADAPTER__H__
