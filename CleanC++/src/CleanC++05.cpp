// 5 现代C++的高级概念
// 5.1 资源管理
// 5.1.1 资源申请积初始化(RAII:Resource Acquisition is Initialization)std::
// 构造时获得，析构时释放；基于范围的资源管理。
// 5.1.2 智能指针:std::unique_ptr,std::shared_ptr, std::weak_ptr
// 具有独占所有权的std::unique_ptr<T>
// 具有共享所有权的std::shared_ptr<T>
// 无所有权但是能够安全访问的std::weak_ptr<T>
// 5.1.3 避免显示的new和delete
//   尽可能使用栈内存
//   用make_functions(make_unique<T>,make_shared<T>)在堆上分配内存
//   尽量使用容器(标准库、Boost、或者其它)
//   利用特定的第三方库封装资源
// 5.1.4 管理特定资源
// windows的HANDLE typedef void *HANDLE;
#include <memory>
#include "windows.h"
const DWORD processId = 4711;
class Win32HandleCloser {
public:
    void operator()(HANDLE handle) const {
        if (handle != INVALID_HANDLE_VALUE) {
            CloseHandle(handle);
        }
    }
};
//using WinewSharedHandle = std::shared_ptr<HANDLE>; // 注意!
using Win32SharedHandle = std::shared_ptr<void>;
using Win32WeakHandle = std::weak_ptr<void>;
Win32SharedHandle processHandle{ OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId),
    Win32HandleCloser() };

//using Win32UniqueHandle = std::unique_ptr<void>; // 注意
// 在C++中不允许定义std::unique_ptr<void>类型!这是因为std::shared_ptr<T>实现了类型删除，
// 但是std::unique_ptr<T>没有。如果一个类支持类型删除，也就意味着它可以存储任意类型的对
// 象，而且会正确地释放对象占用的内存。

// 5.2 Move语义
// 5.2.1 什么是Move语义
// 5.2.2 左值和右值的关系
// 5.2.3 右值引用
// 5.2.4 不要滥用Move
// 5.2.5 零原则、三大规则、五大规则
// 零原则：在实现你的类的时候，应该不需要声明/定义析构函数，也不需要声明/定义copy/move构造器
// 和copy/move赋值运算符。用C++智能指针和标准库类来管理资源。
// 5.3 编译器是你的搭档
// 5.3.1 自动类型推导
// 5.3.2 编译时计算
// 5.3.3 模板变量
// 5.4 不允许未定义行为
// 避免未定义行为!未定义行为是一个严重的错误，并且最终会导致程序悄无声息地出错。
// 5.4 Type-Rich编程
//  用户自定义字面值，SI units, Boost.Units
// 5.6 了解你使用的库
// 5.6.1 熟练使用<algorithm>
//  C++17中简单的并行算法
// 5.6.2 熟练使用Boost库
// 5.6.3 应该了解的一些库
// chrono，regex，filesystem
// Range-v3
// 并发数据结构：libcds
// 5.7 恰当的异常和错误处理机制
// 5.7.1 防患于未然
// 前置条件、不变值、后置条件
// 无异常安全、基本异常安全、强异常安全、保证不抛出异常
// 在下列情况下，保证不抛出异常要么是绝对强制的，要么至少是明确建议的：
// 在任何情况下类的析构必须保证不抛出异常
// Move操作应该保证不抛出异常
// 默认构造函数最好不抛出异常
// 在任何情况下，swap函数必须保证不抛出异常!
// noexcept声明和运算符(C++11)
// 5.7.2 异常即异常--字面上的意思
// 5.7.3 如果不能恢复则尽快退出
// 5.7.4 用户自定义异常
// 5.7.5 值类型抛出，常量引用类型捕获
// 5.7.6 注意catch的正确顺序
