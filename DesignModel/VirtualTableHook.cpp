// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : VirtualTableHook.cpp
// FileTarget    : VirtualTableHook.cpp
// Description   : 虚表hook方式
// 
// version        date        Author        Description
// 0001-0001      2014-04-21  Zhangfj       新建
// 
// *********************************************************************************************
#include "VirtualTableHook.h"


void* g_pAddr = 0;
int g_count = 0;
void LoadHook(CClassA1* pA1)
{
    _asm
    {
        push eax;
        push ecx;
        mov eax, dword ptr [pA1];         // 获取对象指针
        mov eax, dword ptr [eax];        // 获取虚表地址
        add eax, 8;                      // 获取虚表中类CClassA1第三个函数指针的地址
        mov ecx, dword ptr [eax];        // 取出类CClassA1第三个函数指针
        mov dword ptr [g_pAddr], ecx;    // 保存到g_pAddr变量中
        mov ecx, offset hook_proc;       // 替换为hook_proc指针
        mov dword ptr [eax], ecx;
        pop ecx;
        pop eax;
        jmp hook_end;
    }

hook_proc:
    _asm
    {
        push ecx
        push esi
    }

    g_count++;
    std::cout<< g_count << " time(s) to invoke A::print_all()" << std::endl;    //CClassA1::PrintAll的计数
    _asm
    {
        pop esi
        pop ecx
        jmp dword ptr [g_pAddr]
    }

hook_end:
    std::cout << "A::print_all() hooked!" << std::endl;
}

void UnloadHook(CClassA1* pA1)
{
    _asm
    {
        push eax;
        push ecx;
        mov eax, dword ptr [pA1];        // 获取对象指针
        mov eax, dword ptr [eax];        // 获取虚表地址
        add eax, 8;                      // 获取虚表中类CClassA1第三个函数指针的地址
        mov ecx, dword ptr [g_pAddr];    // 取出事先保存的CClassA1::PrintAll()地址
        mov dword ptr [eax], ecx;
        pop ecx;
        pop eax;
    }
    g_count = 0;
    std::cout << "A::print_all() unhooked!" << std::endl;
}

// 对象A1去调用类B的函数 方法：寄存器ecx中放入对象A1的地址，然后找到类B1相应的函数指针，调用。
void TestHook1(void)
{
    CClassA1 a1(0, 1);
    CClassB1 b1(5, 6);
    CClassA1* pA1 = &a1;
    CClassB1* pB1 = &b1;

    _asm
    {
        push eax;                     // 暂存eax寄存器到堆栈中
        push ecx;                     // 暂存ecx寄存器到堆栈中
        mov eax, dword ptr [pB1];     // 调入b1对象的地址
        mov ecx, dword ptr [pA1];     // 调入a1对象的地址到ecx中，实际上就是引用a对象的变量
        mov eax, dword ptr [eax];     // 取得b1对象的虚表地址（b1对象的第一个元素）
        add eax, 8;                   // 虚表地址 + 8，即b1对象的第三个函数CClassB1::PrintAll()的地址
        call dword ptr [eax];         // 调用类CClassB1的函数CClassB1::PrintAll()，但是实际上传入a1对象的变量
        pop ecx;                      // 从堆栈中弹回ecx
        pop eax;                      // 从堆栈中弹回eax
    }

    std::cout << std::endl;
    pA1->Print1();
    pA1->Print2();
    pA1->PrintAll();
    pA1->PrintExtern(-200);

    std::cout << std::endl;
    pB1->Print1();
    pB1->Print2();
    pB1->PrintAll();
    pB1->PrintExtern(-200);
}

// 交换对象a和对象b的所有虚函数 就是交换两个对象的虚表指针。
void TestHook2(void)
{
    CClassA1 a1(0, 1);
    CClassB1 b1(5, 6);
    CClassA1* pA1 = &a1;
    CClassB1* pB1 = &b1;

    // 交换a1，b1两个对象的虚表地址
    _asm
    {
        push eax;                    // 将四个需要使用的寄存器压入堆栈
        push ecx;
        push esi;
        push edi;
        mov esi, dword ptr [pA1];    // 取得a1对象地址
        mov edi, dword ptr [pB1];    // 取得b1对象地址
        mov eax, dword ptr [esi];    // 读取a1对象虚表地址到eax中
        mov ecx, dword ptr [edi];    // 读取b1对象虚表地址到ecx中
        mov dword ptr [edi], eax;    // 将a1对象虚表地址写到b中
        mov dword ptr [esi], ecx;    // 将b1对象虚表地址写到a中
        pop edi;
        pop esi;
        pop ecx;
        pop eax;
    }

    std::cout << std::endl;
    pA1->Print1();
    pA1->Print2();
    pA1->PrintAll();
    pA1->PrintExtern(-200);

    std::cout << std::endl;
    pB1->Print1();
    pB1->Print2();
    pB1->PrintAll();
    pB1->PrintExtern(-200);
}

// 交换类CClassA1和类CClassB1的第二个和第四个函数
// 方法：需要修改虚表，交换类A和类B的第二、四个函数。
void TestHook3(void)
{
    CClassA1 a1(0,1);
    CClassB1 b1(5,6);
    CClassA1* pA1 = &a1;
    CClassB1* pB1 = &b1;

    _asm
    {
        push eax;                    // 压入需要使用的寄存器到堆栈中
        push ecx;
        push esi;
        push edi;
        mov esi, dword ptr [pA1];    // a1对象指针
        mov edi, dword ptr [pB1];    // b1对象指针
        mov esi, dword ptr [esi];    // a1对象虚表地址
        mov edi, dword ptr [edi];    // b1对象虚表地址
        add esi, 4;
        add edi, 4;
        mov eax, dword ptr [esi];    // 交换第二个函数地址：Print2
        mov ecx, dword ptr [edi];
        mov dword ptr [edi], eax;
        mov dword ptr [esi], ecx;
        add esi, 8;
        add edi, 8;
        mov eax, dword ptr [esi];    // 交换第四个函数地址：PrintExtern
        mov ecx, dword ptr [edi];
        mov dword ptr [edi], eax;
        mov dword ptr [esi], ecx;
        pop edi;
        pop esi;
        pop ecx;
        pop eax;
    }

    std::cout << std::endl;
    pA1->Print1();
    pA1->Print2();
    pA1->PrintAll();
    pA1->PrintExtern(-200);

    std::cout << std::endl;
    pB1->Print1();
    pB1->Print2();
    pB1->PrintAll();
    pB1->PrintExtern(-200);
}

// hook类CClassA1的第三个函数 方法：比较麻烦，但是也是不难弄的。将类ClassA1的第三个虚函数指针替换成我们自己定义的地址。
void TestHook4(void)
{
    CClassA1 a1(2, 3);
    CClassB1 b1(7, 8);
    CClassA1* pA1 = &a1;
    CClassB1* pB1 = &b1;
    LoadHook(pA1);
    std::cout << std::endl;
    pA1->Print1();
    pA1->Print2();
    pA1->PrintAll();    // 调用失败
    UnloadHook(pA1);

    pA1->PrintExtern(500);

    std::cout << std::endl;
    pA1->Print1();
    pA1->Print2();
    pA1->PrintAll();
    pA1->PrintExtern(500);

    std::cout << std::endl;
    pA1->PrintAll();
    pA1->PrintAll();
    pA1->PrintAll();
}
