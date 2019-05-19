// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMState.h
// FileTarget    : DMState.h
// Description   : State ģʽ
//                 
// ����:
// ����һ�����������ڲ�״̬�ı�ʱ�ı�������Ϊ.
// 
// ����:
// Stateģʽ��Ҫ��������ڿ�����ʱ�������ĸ��ݲ�ͬ��״̬��Ҫ���в�ͬ��
// �������������,������������,�󲿷����ǲ���switch-case�����д����,
// ���������һ������:��֧����,�����������һ���µ�״̬����Ҫ��ԭ���Ĵ�
// ����б���.Stateģʽ�����˶���Щ��ͬ��״̬���з�װ�ķ�ʽ������������,
// ��״̬�ı��ʱ����д���Ȼ�����л�����һ��״̬,Ҳ����˵��״̬���л���
// �ν����˾����״̬��ȥ����.ͬʱ,Stateģʽ��Strategyģʽ��ͼʾ���к�
// �����Ƶĵط�,��Ҫ˵���������ߵ�˼�붼��һ�µ�,ֻ������װ�Ķ�����ͬ:St
// ateģʽ��װ���ǲ�ͬ��״̬,��Stategyģʽ��װ���ǲ�ͬ���㷨.
// 
// version        date        Author        Description
// 0001-0001      2013-03-15  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __STATE__H__
#define __STATE__H__
namespace CSTATE
{
	class State;
	class Context
	{
	public:
		Context(State* pState);
		~Context();
		void Request();
		void ChangeState(State* pState);
	private:
		State* m_pState;
	};
	class State
	{
	public:
		virtual ~State(){};
		virtual void Handle(Context* pContext) = 0;
	};
	class ConcreteStateA : public State
	{
	public:
		void Handle(Context* pContext);
	};
	class ConcreteStateB : public State
	{
	public:
		void Handle(Context* pContext);
	};
};
#endif //__STATE__H__
