// 9 ���ģʽ��ϰ���÷�
// 9.1 ���ԭ�����ģʽ
// 9.2 ���������ģʽ��Ӧ�ó���
// 9.2.1 ����ע��(Dependency Injection,DI)
// ����ע�������ݼܹ��Ĺؼ�Ԫ�ء������������Ҫ�ķ�����룬��������Ͳ���֪����Щ��������ƣ�Ҳ����֪����λ�ȡ���ǡ�
// �������ã����Ʒ�ת
// �ܹ��ٽ������

// ������ģʽ
// ����9-1 ���ִ�C++���ʵ�ֵ�Meyers�ĵ���ģʽ
#ifndef SINGLETON_H_
#define SINGLETON_H_

class Singleton final {
public:
    // C++11֮�����־�̬�����Ĺ���ʵ���Ĺ��̣�Ĭ�����̰߳�ȫ�ģ�
    // ��������̰߳�ȫ��������ζ��������Ա�������̰߳�ȫ�ġ�
    static Singleton& getInstance() {
        static Singleton theInstance;
        return theInstance;
    }

    int doSomething() {
        return 42;
    }

    // ...������Ա����...

private:
    Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton& operator=(Singleton&&) = delete;
    // ...
};
#endif
#include <iostream>
void test09_01() {
    std::cout << Singleton::getInstance().doSomething() << std::endl;
}
// ��������е�����ʹ�þ������������ȫ�ֱ�����ʹ��һ����
// �����ʱ�򣬵���������һ�ֺõ�ģʽ��

//// ����9-2 ʹ��Singleton���������ʵ��ժҪ
//#include "AnySingletonUser.h"
//#include "Singleton.h"
//#include <string>
//// ...
//void AnySingletonUser::aMemberFunction() {
//    // ...
//    std::string result = Singleton::getInstance().doThis();
//    // ...
//}
//// ...
//void AnySingletonUser::anotherMemberFunction() {
//    // ...
//    int result = Singleton::getInstance().doThat();
//    // ...
//    double value = Singleton::getInstance().doSomethongMore();
//    // ...
//}

// 9.2.2 Adapterģʽ
// ��һ����Ľӿ�ת��Ϊ�ͻ�����������һ���ӿڡ�Adapter��������ӿڲ����ݶ��޷�һ��������һ������
// 9.2.3 Strategyģʽ
// ����һ���㷨��Ȼ���װÿ���㷨����ʹ���ǿ����໥�滻������ģʽ�����㷨������ʹ�����Ŀͻ��˶��仯��
// 9.2.4 Commandģʽ
// �������װΪ���󣬴Ӷ�������ʹ�ò�ͬ�����󡢶��л���־������������ͻ��˻�֧�ֿɳ���������
// 9.2.5 Command������ģʽ
// 9.2.6 Compositeģʽ
// ��������ϳ����ṹ����ʾ������-���塱�Ĳ�νṹ���������ͻ���ͳһ�ش���������Ͷ������ϡ�
// 9.2.7 Observerģʽ
// �������֮��һ�Զ��������ϵ���Ա���һ���������״̬ʱ���Զ�֪ͨ�����������е�������ϵ��
// 9.2.8 Factoryģʽ
// 9.2.10 Facadeģʽ
// Ϊ��ϵͳ�е�һ��ӿ��ṩͳһ�Ľӿڡ�Facade������һ�����߼��Ľӿڣ�ʹ����ϵͳ������ʹ�á�
// 9.2.10 Money Classģʽ
// 9.2.11 ����ģʽ
// 9.3 ʲô��ϰ���÷�
// Include Guard,Macro Guard, Header Guard
//#ifndef __FILENAME__H__
//#define __FILENAME__H__
////...
//#endif __FILENAME__H__
//#pragma once
// һЩϰ���÷�
// ���ɱ����
// ƥ��ʧ�ܲ��Ǵ���(SFINAE:Substitution Failure is not an Error)
// std::enable_if
// Copy-and-Swapϰ���÷�
// ָ��ʵ�ֵ�ָ��(Handle Body�ַ�)��
// ͨ�����ڲ����ʵ��ϸ�����¶�λ�����ص�ʵ�����У�������ʵ�ֵı����������Ӷ���߱���ʱ�䡣

void test09() {
    test09_01();
}