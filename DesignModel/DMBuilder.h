// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMBuilder.h
// FileTarget    : DMBuilder.h
// Description   : Builder ģʽ
// ��һ�����Ӷ���Ĺ��������ı�ʾ���룬ʹ��ͬ���Ĺ������̿��Դ�����ͬ�ı�ʾ��
// 1)���������Ӷ�����㷨Ӧ�ö����ڸö������ɲ����Լ����ǵ�װ�䷽ʽʱ��
// 2)��������̱�����������Ķ����в�ͬ�ı�ʾʱ��
// 
// �������:
// 1)Builder:���������ȫ������������̵ĳ���,�ṩ������ͬ��ɲ��ֵĽӿں���
// �ӿ�:
// 1)Builder::BuildPartA,Builder::BuildPartB:�Ƕ�һ������ͬ���ֵĹ��������ӿ�,Builder��������������ʵ��.
// ���⻹��һ����Ҫע��ĺ���,����Director::Construct����,�����������
// ͨ����������������ӿں�����ɶ���Ĺ���--Ҳ����˵������ͬ����װ���
// ���̶���һ�µ�(ͬ���ĵ��õ�Construct����),���ǲ�ͬ�Ĺ�����ʽ���в�ͬ
// �ı�ʾ(����Builder��ʵ��������������ι���,Ҳ���Ƕ�̬)
// 
// version        date        Author        Description
// 0001-0001      2013-02-28  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __DMBUILDER__H__
#define __DMBUILDER__H__
// ������࣬������Builder�Ļ��࣬�ṩ��ͬ���ֵĹ����ӿں���
class Builder
{
public:
	Builder(){};
	virtual ~Builder(){};
	// ���麯�����ṩ������ͬ���ֵĹ����ӿں���
	virtual void BuilderPartA() = 0;
	virtual void BuilderPartB() = 0;
};
// ʹ��Builder������Ʒ��������Ʒ�Ĺ��̶�һ�£����ǲ�ͬ��builder�в�ͬ��ʵ��
// �����ͬ��ʵ��ͨ����ͬ��Builder��������ʵ�֣�����һ��Builder��ָ�룬ͨ�������ʵ�ֶ�̬����
class Director
{
public:
	Director(Builder * pBuilder);
	virtual ~Director();
	void Construct();
private:
	Builder* m_pBuilder;
};
// Builder�������࣬ʵ��BuilderPartA��BuilderPartB�ӿں���
class ConcreteBuilder1
	: public Builder
{
public:
	ConcreteBuilder1(){};
	virtual ~ConcreteBuilder1(){};
	virtual void BuilderPartA();
	virtual void BuilderPartB();
};
// Builder�����࣬ʵ��BuilderPartA��BuilderPartB�ӿں���
class ConcreteBuilder2
	: public Builder
{
public:
	ConcreteBuilder2(){};
	virtual ~ConcreteBuilder2(){}
	virtual void BuilderPartA();
	virtual void BuilderPartB();
};
#endif // __DMBUILDER__H__
