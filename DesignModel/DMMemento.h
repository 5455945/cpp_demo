// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMMemento.h
// FileTarget    : DMMemento.h
// Description   : Memento ģʽ
//                 
// ����:
// �ڲ��ƻ���װ�Ե�ǰ����,����һ��������ڲ�״̬,���ڸö���֮�Ᵽ�����״̬.�����Ժ�Ϳɽ��ö���ָ���ԭ�ȱ����״̬.
// 
// ����:
// Mementoģʽ�з�װ������Ҫ�����״̬,����Ҫ�ָ���ʱ���ȡ�������л�
// ��.ԭ��ܼ�,ʵ�ֵ�ʱ����Ҫע��һ���ط�:խ�ӿںͿ�ӿ�.��ν�Ŀ�ӿھ�
// ��һ�������ϵĽӿ�,�Ѷ���Ľӿ���Ϊpublic��Ա;��խ�ӿڷ�֮,�ѽӿ���Ϊ
// private��Ա,������Ҫ������Щ�ӿں���������Ϊ��������Ԫ��,Ҳ����˵��
// ��ֻ��¶���˶���Щ�ӿڸ���Ȥ����,�����Ǳ�¶���ⲿ.�����ʵ�־���խ�ӿ�
// �ķ�����ʵ�ֵ�.
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __MEMENTO__H__
#define __MEMENTO__H__
#include <string>
typedef std::string State;
class Memento;
class Originator
{
public:
	Originator(const State& rState);
	Originator();
	~Originator();
	Memento* CreatorMemento();
	void SetMemento(Memento* pMemento);
	State GetState();
	void SetState(const State& rState);
	void RestoreState(Memento* pMemento);
	void PrintState();
private:
	State m_State;
};
// ��Memento�ӿں�������Ϊ˽�У���Originator��������Ԫ
// ��ֻ֤��Originator���Է���Memento
class Memento
{
private:
	friend class Originator;
	Memento(const State& rState);
	void SetState(const State& rState);
	State GetState();
	State m_State;
};
#endif //__MEMENTO__H__
