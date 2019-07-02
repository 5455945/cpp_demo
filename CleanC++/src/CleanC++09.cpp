// 9 设计模式和习惯用法
// 9.1 设计原则及设计模式
// 9.2 常见的设计模式及应用场景
// 9.2.1 依赖注入(Dependency Injection,DI)
// 依赖注入是敏捷架构的关键元素。将组件与其需要的服务分离，这样组件就不必知道这些服务的名称，也不必知道如何获取它们。
// 依赖倒置，控制反转
// 能够促进松耦合

// 单例反模式
// 代码9-1 以现代C++风格实现的Meyers的单例模式
#ifndef SINGLETON_H_
#define SINGLETON_H_

class Singleton final {
public:
    // C++11之后，这种静态变量的构造实例的过程，默认是线程安全的；
    // 构造过程线程安全，并不意味着其它成员函数是线程安全的。
    static Singleton& getInstance() {
        static Singleton theInstance;
        return theInstance;
    }

    int doSomething() {
        return 42;
    }

    // ...其它成员函数...

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
// 面向对象中单例的使用就像面向过程中全局变量的使用一样。
// 更多的时候，单例并不是一种好的模式。

//// 代码9-2 使用Singleton的任意类的实现摘要
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

// 9.2.2 Adapter模式
// 把一个类的接口转换为客户端期望的另一个接口。Adapter可以让因接口不兼容而无法一起工作的类一起工作。
// 9.2.3 Strategy模式
// 定义一组算法，然后封装每个算法，并使它们可以相互替换。策略模式允许算法独立于使用它的客户端而变化。
// 9.2.4 Command模式
// 将请求封装为对象，从而允许你使用不同的请求、队列或日志的请求参数化客户端或支持可撤销操作。
// 9.2.5 Command处理器模式
// 9.2.6 Composite模式
// 将对象组合称树结构来表示“部分-整体”的层次结构。组合允许客户端统一地处理单个对象和对象的组合。
// 9.2.7 Observer模式
// 定义对象之间一对多的依赖关系，以便在一个对象更改状态时，自动通知并更新其所有的依赖关系。
// 9.2.8 Factory模式
// 9.2.10 Facade模式
// 为子系统中的一组接口提供统一的接口。Facade定义了一个更高级的接口，使得子系统更容易使用。
// 9.2.10 Money Class模式
// 9.2.11 特例模式
// 9.3 什么是习惯用法
// Include Guard,Macro Guard, Header Guard
//#ifndef __FILENAME__H__
//#define __FILENAME__H__
////...
//#endif __FILENAME__H__
//#pragma once
// 一些习惯用法
// 不可变的类
// 匹配失败不是错误(SFINAE:Substitution Failure is not an Error)
// std::enable_if
// Copy-and-Swap习惯用法
// 指向实现的指针(Handle Body手法)：
// 通过将内部类的实现细节重新定位到隐藏的实现类中，消除对实现的编译依赖，从而提高编译时间。

void test09() {
    test09_01();
}