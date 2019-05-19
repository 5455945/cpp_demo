// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMIterator.h
// FileTarget    : DMIterator.h
// Description   : Iterator ģʽ
//                 
// ����:
// �ṩһ�ַ���˳�����һ���ۺ϶����и���Ԫ��,���ֲ��豩¶�ö�����ڲ���ʾ.
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __ITERATOR__H__
#define __ITERATOR__H__
typedef int DATA;
class Iterator;
// �����������
class Aggregate
{
public:
	virtual ~Aggregate(){};
	virtual Iterator* CreateIterator(Aggregate* pAggregate) = 0;
	virtual int GetSize() = 0;
	virtual DATA GetItem(int nIndex) = 0;
};
// �������ĳ������
class Iterator
{
public:
	virtual ~Iterator(){};
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual bool IsDone() = 0;
	virtual DATA CurrentItem() = 0;
};
// һ������������
class ConcreteAggregate :public Aggregate
{
public:
	ConcreteAggregate(int nSzie);
	virtual ~ConcreteAggregate();
	virtual Iterator* CreateIterator(Aggregate* pAggregate);
	virtual int GetSize();
	virtual DATA GetItem(int nIndex);
private:
	int    m_nSize;
	DATA*  m_pData;
};
// ����ConcreteAggregate������ĵ�������
class ConcreteIterator : public Iterator
{
public:
	ConcreteIterator(Aggregate* pAggregate);
	virtual ~ConcreteIterator(){};
	virtual void First();
	virtual void Next();
	virtual bool IsDone();
	virtual DATA CurrentItem();
private:
	Aggregate* m_pConcreteAggregate;
	int m_nIndex;
};
#endif //__ITERATOR__H__
