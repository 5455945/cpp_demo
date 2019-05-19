// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMTemplateMethod.h
// FileTarget    : DMTemplateMethod.h
// Description   : TemplateMethod ģʽ
// 
// ����:
// ����һ�������е��㷨�ĹǼܣ�����һЩ�����ӳٵ������С�TemplateMethod ʹ��������Բ��ı�һ���㷨�Ľṹ�����ض�����㷨��ĳЩ�ض����衣
// �������:
// 1)AbstractClass:�������,�����㷨������
// ����:
// TemplateMethod �Ĺؼ������ڻ����ж�����һ���㷨������,�����㷨ÿһ�������ʵ��������������.��������Ҳ�������Ƶ�����Բ��ߵ�ȱ��,��Ϊ
// �����Ѿ���������Ҫ��ı�ͱȽ�����,��Ҳ��Ϊʲô���Ȳ��þۺ϶����Ǽ̳е�ԭ��.
// 
// version        date        Author        Description
// 0001-0001      2013-03-04  Zhangfj       �½�
// 
// *********************************************************************************************
// ������࣬�����㷨������
class AbstractClass
{
public:
	AbstractClass(){};
	virtual ~AbstractClass(){};
	// ��������ж����㷨����
	void TemplateMethod();
protected:
	// ���麯������������ʵ��
	virtual void PrimitiveOperation1() = 0;
	virtual void PrimitiveOperation2() = 0;
};
// �̳���AbstractClass��ʵ���㷨
class ConcreteClass
	: public AbstractClass
{
public:
	ConcreteClass(){};
protected:
	virtual void PrimitiveOperation1();
	virtual void PrimitiveOperation2();
};
