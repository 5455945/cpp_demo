// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DesignModel.cpp
// FileTarget    : DesignModel.cpp
// Description   : ����ģʽ ����������
//                 
// 
// version        date        Author        Description
// 0001-0001      2013-02-27  Zhangfj       �½�
// 
// *********************************************************************************************
#include "DesignModel.h"
#include "stdlib.h"
#include <iostream>

int main(int argc, char* argv[])
{
	// Factory Method
	Creator *p = new ConcreteCreator();
	p->AnOperation();
	delete p;

	// Abstract Factory
	// ������ƷA�ĵ�һ��ʵ��
	ConcreteFactory1 *pFactory1 = new ConcreteFactory1;
	AbstractProductA *pProductA = pFactory1->CreateProductA();

	// ������ƷB�ĵڶ���ʵ��
	ConcreteFactory2 *pFactory2 = new ConcreteFactory2;
	AbstractProductB *pProductB = pFactory2->CreateProductB();

	delete pFactory1;
	delete pProductA;
	delete pFactory2;
	delete pProductB;
	
	// Builder
	Builder* pBuilder1 = new ConcreteBuilder1;
	Director* pDirector1 = new Director(pBuilder1);
	pDirector1->Construct();

	Builder* pBuilder2 = new ConcreteBuilder2;
	Director* pDirector2 = new Director(pBuilder2);
	pDirector2->Construct();

	delete pDirector1;
	delete pDirector2;
	
	// Prototype
	Prototype* pPrototype1 = new ConcretePrototype1();
	Prototype* pPrototype2 = pPrototype1->Clone();
	Prototype* pPrototype3 = new ConcretePrototype2();
	Prototype* pPrototype4 = pPrototype3->Clone();

	delete pPrototype1;
	delete pPrototype2;
	delete pPrototype3;
	delete pPrototype4;
	
	// Singleton
	Singleton::Instance()->Test();
	
	// Adapter
	Adaptee *pAdaptee = new Adaptee;
	Target* pTarget = new Adapter(pAdaptee);
	pTarget->Request();
	delete pTarget;
	
	// Bridge
	ConcreteImplementorA *pImplA = new ConcreteImplementorA();
	Abstraction * pAbstraction1 = new Abstraction(pImplA);
	pAbstraction1->Operation();
	ConcreteImplementorB *pImplB = new ConcreteImplementorB();
	Abstraction *pAbstraction2 = new Abstraction(pImplB);
	pAbstraction2->Operation();
	delete pAbstraction1;
	delete pAbstraction2;
	
	// Composite
	Leaf *pLeaf1 = new Leaf();
	Leaf *pLeaf2 = new Leaf();
	Composite* pComposite = new Composite;
	pComposite->Add(pLeaf1);
	pComposite->Add(pLeaf2);
	pComposite->Operation();
	pComposite->GetChild(2)->Operation();
	delete pComposite;
	
	// Decorator
	// ��ʼ��һ��Component����
	Decorator::Component* pComponent = new Decorator::ConcreteComponent();
	// �������Component����ȥ��ʼ��һ��Decorator����,�����Ϳ���Ϊ���Component����̬���ְ��
	Decorator::Decorator* pDecorator = new Decorator::ConcreteDecorator(pComponent);
	pDecorator->Operation();
	delete pDecorator;

	// Proxy
	Subject* pProxy = new Proxy();
	pProxy->Request();
	delete pProxy;
	
	// TemplateMethod
	AbstractClass* pConcreteClass = new ConcreteClass;
	pConcreteClass->TemplateMethod();
	delete pConcreteClass;
	
	// ChainOfResponsibility
	Handler *p1 = new ConcreteHandler1();
	Handler *p2 = new ConcreteHandler2(p1);
	p2->HandleRequest();
	delete p2;
	
	// Flyweight
	FlyweightFactory flyweightfactory;
	flyweightfactory.GetFlyweight("hello");
	flyweightfactory.GetFlyweight("world");
	flyweightfactory.GetFlyweight("hello");

	// Command
	Receiver* pReceiver = new Receiver();
	Command* pCommand = new ConcreteCommand(pReceiver);
	Invoker* pInvoker = new Invoker(pCommand);
	pInvoker->Invoke();
	delete pInvoker;

	// Observer
	OBSERVER::Observer* pObserver1 = new OBSERVER::ConcreteObserver;
	OBSERVER::Observer* pObserver2 = new OBSERVER::ConcreteObserver;
	OBSERVER::Subject* pSubject = new OBSERVER::ConcreteSubject;
	pSubject->Attach(pObserver1);
	pSubject->Attach(pObserver2);
	pSubject->SetState(4);
	pSubject->Notify();
	pSubject->SetState(10);
	pSubject->Notify();
	delete pSubject;
	
	// Strategy
	Strategy* pStrategy = new ConcreteStrategyA();
	Context* pContext = new Context(pStrategy);
	pContext->ContextInterface();
	delete pContext;
	
	// State
	CSTATE::State* pState = new CSTATE::ConcreteStateA();
	CSTATE::Context* pStateContext = new CSTATE::Context(pState);
	pStateContext->Request();
	pStateContext->Request();
	pStateContext->Request();
	delete pStateContext;
	
	// Iterator
	Aggregate* pAggregate = new ConcreteAggregate(4);
	Iterator* pIterator = new ConcreteIterator(pAggregate);
	for(; false == pIterator->IsDone(); pIterator->Next())
	{
		std::cout << pIterator->CurrentItem() << std::endl;
	}
	
	// ����һ��ԭ����
	Originator* pOriginator = new Originator("old state");
	pOriginator->PrintState();
	// ����һ������¼������ԭ������״̬
	Memento* pMemento = pOriginator->CreatorMemento();
	// ����ԭ������״̬
	pOriginator->SetState("new state");
	pOriginator->PrintState();
	// ͨ������¼��ԭ������״̬��ԭ
	pOriginator->RestoreState(pMemento);
	pOriginator->PrintState();
	delete pOriginator;
	delete pMemento;
	
	// Visitor
	Visitor* pVisitorA = new ConcreteVisitorA();
	Element* pElement = new ConcreteElementA();
	pElement->Accept(*pVisitorA);
	delete pElement;
	delete pVisitorA;

	return 0;
}
