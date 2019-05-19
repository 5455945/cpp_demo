// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMBridge.h
// FileTarget    : DMBridge.h
// Description   : Bridge ģʽ
//
// ����:
// �����󲿷�������ʵ�ֲ��ַ��룬ʹ���Ƕ����Զ����ر仯��
// �������:
// 1)Abstraction:ĳ��������,����ʵ�ַ�ʽ��Implementor���.
// 2)Implementor:ʵ����ĳ������,������ʵ��Abastraction�Ļ�������,������������ʵ����Щ�ӿ�.
// �ӿں���:
// 1)Implementor::OperationImpl:������Ϊʵ��Abstraction��Ҫ�Ļ�����
// ��,��Implementor��������ʵ��֮,����Abstraction::Operation�����и��ݲ�ͬ��ָ���̬�����������.
// ����:
// Bridge���ڽ���ʾ��ʵ�ֽ���,���߿��Զ����ı仯.��Abstraction����ά��
// һ��Implementor��ָ��,��Ҫ���ò�ͬ��ʵ�ַ�ʽ��ʱ��ֻ��Ҫ���벻ͬ��Implementor������Ϳ�����.
// 
// Bridge��ʵ�ַ�ʽ��ʵ��Builderʮ�ֵ����,������ô˵:��������һ����,ֻ
// �Ƿ�װ�Ķ�����һ������.���ߵ�ʵ�ֶ������µĹ�ͬ��:�������һ������,��
// ���������涨���˹��е�һЩ��Ϊ,�γɽӿں���(�Խӿڱ�̶����Ƕ�ʵ�ֱ�
// ��),����ӿں�����Buildier����BuildePart������Bridge����Operation
// Impl ����;���,�ۺ�һ�������ָ��,��Builderģʽ��Director��ۺ���һ
// ��Builder�����ָ��,��Brigeģʽ��Abstraction��ۺ���һ��Impleme
// ntor�����ָ��(���Ȳ��þۺ϶����Ǽ̳�);����ʹ�õ�ʱ��,���Ѷ�������
// ʹ�÷�װ��һ��������,��Bridge���Ƿ�װ��Director::Construct������,��
// Ϊװ�䲻ͬ���ֵĹ�����һ�µ�,����Bridgeģʽ�����Ƿ�װ��Abstraction::
// Operation������,����������е��ö�Ӧ��Implementor::OperationImpl
// ����.������ģʽ����,Builder��װ�˲�ͬ��������ɲ��ֵķ�ʽ,��Bridge��
// װ�˲�ͬ��ʵ�ַ�ʽ.
// 
// ���,�����һЩ������������������ԭ����������Щģʽ��ʵ�ֵĻ�,��
// �ǿ��Կ����ܶ๲ͬ�ĵط���.
// 
// version        date        Author        Description
// 0001-0001      2013-03-01  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __DMBRIDGE__H__
#define __DMBRIDGE__H__
class Implementor;
// ά��һ��Implementor���ָ��
class Abstraction
{
public:
	Abstraction(Implementor* pImplementor);
	virtual ~Abstraction();
	void Operation();
protected:
	Implementor* m_pImplementor;
};
// Ϊʵ��Abstraction����ĳ�����࣬������ʵ�ֵĽӿں���
class Implementor
{
public:
	Implementor(){};
	virtual ~Implementor(){};
	virtual void OperationImpl() = 0;
};
// �̳���Implementor����Implementor��һ����ͬʵ��֮һ
class ConcreteImplementorA
	: public Implementor
{
public:
	ConcreteImplementorA(){};
	virtual ~ConcreteImplementorA(){};
	virtual void OperationImpl();
};
// �̳���Implementor����Implementor��һ����ͬʵ��֮һ
class ConcreteImplementorB
	: public Implementor
{
public:
	ConcreteImplementorB(){};
	virtual ~ConcreteImplementorB(){};
	virtual void OperationImpl();
};
#endif //__BRIDGE__H__
