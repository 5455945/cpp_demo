// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMProxy.h
// FileTarget    : DMProxy.h
// Description   : Proxy ģʽ
// 
// ����:
// Ϊ���������ṩһ�ִ����Կ��ƶ��������ķ��ʡ�
// �������:
// 1)Subject:������Proxy��RealSubject�Ĺ��нӿ�,�����Ϳ������κ���Ҫʹ�õ�RealSubject�ĵط���ʹ��Proxy.
// ����:
// Proxy��ʵ�ǻ�������һ��ʱ��ʹ�õ��ļ���-ĳ������ֱ����������ʹ�õ���
// ʱ��ű���ʼ��,��û��ʹ�õ���ʱ�����ʱ��Proxy��һ��ռλ��.���ģʽ
// ʵ�ֵ�Ҫ�����Proxy��RealSubject���̳���Subject,������֤��������
// �ӿڶ���һ�µ�.
// 
// version        date        Author        Description
// 0001-0001      2013-03-04  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __DMPROXY__H__
#define __DMPROXY__H__
// ������Proxy��RealSubject�Ĺ��нӿڣ������Ϳ������κ���Ҫʹ�õ�RealSubject�ĵط���ʹ��Proxy.
class Subject
{
public:
	Subject(){};
	virtual ~Subject(){};
	virtual void Request() = 0;
};
// ����ʹ�õ�ʵ��
class RealSubject
	: public Subject
{
public:
	RealSubject();
	virtual ~RealSubject(){};
	virtual void Request();
};
// �����࣬����һ��ָ��RealSubject�����ָ��
class Proxy
	: public Subject
{
public:
	Proxy();
	virtual ~Proxy();
	virtual void Request();
private:
	RealSubject* m_pRealSubject;
};
#endif // __DMPROXY__H__
