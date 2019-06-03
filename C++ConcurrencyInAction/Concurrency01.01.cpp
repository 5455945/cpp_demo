#include "Concurrency01.h"

// C++并发编程实战 [美] Anthony Williams 著; 周全 梁娟娟 宋真真 许敏 译
// 随书源码下载页面: www.manning.com/CPlusPlusConcurrencyInAction
// 随书源码下载页面: https://www.manning.com/books/c-plus-plus-concurrency-in-action
// 压缩包链接地址:https://www.manning.com/downloads/355

// 1.1 什么是并发(Concurrency)
// 并发有两种含义：
// A:硬件并发(hardware concurrency):多核同时运行不同的任务(这些任务可能是一个进程的，也可能是不同进程的)
// B:任务切换(task swithing):一个处理器处理轮流执行不同进程的任务，每个任务较小，切换较快，看上去像同时在运行.
// 并发一般会牵涉到上下文切换(context switch),频繁的上下文切换会导致效率损失;
// 有些cpu支持绑定功能，会适当的避免上下文切换
// 硬件线程(hardware threads):一般是只处理器个数*每处理器核心数
// 因为cpu的速度远远大于外设，所以系统可运行的线程数量一般远远大于处理器数量*每处理器核心数
// 多进程并发和多线程并发

// 1.2 为什么使用并发:关注点分离和性能
// 1.2.1 为了划分关注点使用并发
// 1.2.2 为了性能使用并发
// 任务并行(task parallelism)
// 数据并行(data parallelism)

// 1.2.3 什么时候不使用并行
// 收益比不上成本
// 线程是有限的资源，太多线程同时运行，会消耗操作系统的资源
// 多线程会产生上下文切换，频繁的上下文切换，会降低性能。

// 1.3 在C++中使用并发和多线程
// 1.3.1 C++多线程历程
// 借鉴POSIX C/WINDOWS API/Boost/ACE
// 资源获得即初始化(RAII:Resource Acquisition Is Initialization):在构造函数中申请分配资源，在析构函数中释放资源。
// 将资源和对象的生命周期绑定。
// RAII的核心思想是将资源或者状态与对象的生命周期绑定，通过C++的语言机制，实现资源和状态的安全管理。
// 1.3.2 新标准中并发支持
// 线程管理、保护共享数据、线程间同步操作、低级原子操作
// 1.3.3 C++线程库的效率
// 抽象惩罚(abstraction penalty):在提供相同工具时，通过直接使用低级API几乎或完全得不到任何好处。
// 1.3.4 平台相关的工具
// C++线程库提供了一个native_handle()成员函数，允许通过使用平台相关的API直接操作底层实现。

// 1.4 开始入门
#include <iostream>
#include <thread>
void hello()
{
    std::cout << "Hello Concurrent World\n";
}

void Concurrency01_01()
{
    std::thread t(hello);
    t.join();
}
