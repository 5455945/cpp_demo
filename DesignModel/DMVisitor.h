// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMVisitor.h
// FileTarget    : DMVisitor.h
// Description   : Visitor ģʽ
//                 
// ����:
// ��ʾһ��������ĳ����ṹ�еĸ�Ԫ�صĲ���.��ʹ������ڲ��ı��Ԫ�ص����ǰ���¶�����������ЩԪ�ص��²���.
// 
// ����:
// Visitorģʽ�ѶԽ��ķ��ʷ�װ��һ���������,ͨ����������ͬ����������
// �ķ��ʷ�ʽ.��ʵ�ֵ�ʱ��,��visitor��������������˶����в�ͬ�����з�
// �ʵĽӿں���,��ͼ�е�VisitConcreateElementA������,����Ҳ�����Visit
// orģʽ��һ��ȱ��--�¼���һ������ʱ��Ҫ���Visitor�еĶ�����з���
// �ӿں���,����ʹ�����е�Visitor���������඼Ҫ���±�����,Ҳ����˵Visitor
// ģʽһ��ȱ���������µĽ��ʮ������.����,����Ҫָ������Visitorģʽ��
// ������ν��"˫�ط���"�ļ���,����ͼ����Ϊ����,Ҫ��ĳһ�������з���,��
// ����Ҫ����һ��Element�����������,���Ҫ����һ��Visitor�����������
// �����ö�Ӧ��Accept����,Ҳ����˵,���׶�����Element��������Visitor��
// ��,��Ҫ���ζ�̬�󶨲ſ���ȷ������
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __VISITOR__H__
#define __VISITOR__H__
class Visitor;
class Element
{
public:
	virtual ~Element(){};
	virtual void Accept(Visitor& Visitor) = 0;
protected:
	Element(){};
};
class ConcreteElementA : public Element
{
public:
	virtual ~ConcreteElementA(){};
	virtual void Accept(Visitor& rVisitor);
};
class ConcreteElementB : public Element
{
public:
	virtual ~ConcreteElementB(){};
	virtual void Accept(Visitor& rVisitor);
};
class Visitor
{
public:
	virtual ~Visitor(){};
	virtual void VisitConcreteElementA(ConcreteElementA* pConcreteElementA) = 0;
	virtual void VisitConcreteElementB(ConcreteElementB* pConcreteElementB) = 0;
protected:
	Visitor(){};
};
class ConcreteVisitorA : public Visitor
{
public:
	~ConcreteVisitorA(){};
	virtual void VisitConcreteElementA(ConcreteElementA* pConcreteElementA);
	virtual void VisitConcreteElementB(ConcreteElementB* pConcreteElementB);
};
class ConcreteVisitorB : public Visitor
{
public:
	virtual ~ConcreteVisitorB(){};
	virtual void VisitConcreteElementA(ConcreteElementA* pConcreteElementA);
	virtual void VisitConcreteElementB(ConcreteElementB* pConcreteElementB);
};
#endif //__VISITOR__H__
