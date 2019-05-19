// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : VirtualTableHook.cpp
// FileTarget    : VirtualTableHook.cpp
// Description   : ���hook��ʽ
// 
// version        date        Author        Description
// 0001-0001      2014-04-21  Zhangfj       �½�
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
        mov eax, dword ptr [pA1];         // ��ȡ����ָ��
        mov eax, dword ptr [eax];        // ��ȡ����ַ
        add eax, 8;                      // ��ȡ�������CClassA1����������ָ��ĵ�ַ
        mov ecx, dword ptr [eax];        // ȡ����CClassA1����������ָ��
        mov dword ptr [g_pAddr], ecx;    // ���浽g_pAddr������
        mov ecx, offset hook_proc;       // �滻Ϊhook_procָ��
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
    std::cout<< g_count << " time(s) to invoke A::print_all()" << std::endl;    //CClassA1::PrintAll�ļ���
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
        mov eax, dword ptr [pA1];        // ��ȡ����ָ��
        mov eax, dword ptr [eax];        // ��ȡ����ַ
        add eax, 8;                      // ��ȡ�������CClassA1����������ָ��ĵ�ַ
        mov ecx, dword ptr [g_pAddr];    // ȡ�����ȱ����CClassA1::PrintAll()��ַ
        mov dword ptr [eax], ecx;
        pop ecx;
        pop eax;
    }
    g_count = 0;
    std::cout << "A::print_all() unhooked!" << std::endl;
}

// ����A1ȥ������B�ĺ��� �������Ĵ���ecx�з������A1�ĵ�ַ��Ȼ���ҵ���B1��Ӧ�ĺ���ָ�룬���á�
void TestHook1(void)
{
    CClassA1 a1(0, 1);
    CClassB1 b1(5, 6);
    CClassA1* pA1 = &a1;
    CClassB1* pB1 = &b1;

    _asm
    {
        push eax;                     // �ݴ�eax�Ĵ�������ջ��
        push ecx;                     // �ݴ�ecx�Ĵ�������ջ��
        mov eax, dword ptr [pB1];     // ����b1����ĵ�ַ
        mov ecx, dword ptr [pA1];     // ����a1����ĵ�ַ��ecx�У�ʵ���Ͼ�������a����ı���
        mov eax, dword ptr [eax];     // ȡ��b1���������ַ��b1����ĵ�һ��Ԫ�أ�
        add eax, 8;                   // ����ַ + 8����b1����ĵ���������CClassB1::PrintAll()�ĵ�ַ
        call dword ptr [eax];         // ������CClassB1�ĺ���CClassB1::PrintAll()������ʵ���ϴ���a1����ı���
        pop ecx;                      // �Ӷ�ջ�е���ecx
        pop eax;                      // �Ӷ�ջ�е���eax
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

// ��������a�Ͷ���b�������麯�� ���ǽ���������������ָ�롣
void TestHook2(void)
{
    CClassA1 a1(0, 1);
    CClassB1 b1(5, 6);
    CClassA1* pA1 = &a1;
    CClassB1* pB1 = &b1;

    // ����a1��b1�������������ַ
    _asm
    {
        push eax;                    // ���ĸ���Ҫʹ�õļĴ���ѹ���ջ
        push ecx;
        push esi;
        push edi;
        mov esi, dword ptr [pA1];    // ȡ��a1�����ַ
        mov edi, dword ptr [pB1];    // ȡ��b1�����ַ
        mov eax, dword ptr [esi];    // ��ȡa1��������ַ��eax��
        mov ecx, dword ptr [edi];    // ��ȡb1��������ַ��ecx��
        mov dword ptr [edi], eax;    // ��a1��������ַд��b��
        mov dword ptr [esi], ecx;    // ��b1��������ַд��a��
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

// ������CClassA1����CClassB1�ĵڶ����͵��ĸ�����
// ��������Ҫ�޸����������A����B�ĵڶ����ĸ�������
void TestHook3(void)
{
    CClassA1 a1(0,1);
    CClassB1 b1(5,6);
    CClassA1* pA1 = &a1;
    CClassB1* pB1 = &b1;

    _asm
    {
        push eax;                    // ѹ����Ҫʹ�õļĴ�������ջ��
        push ecx;
        push esi;
        push edi;
        mov esi, dword ptr [pA1];    // a1����ָ��
        mov edi, dword ptr [pB1];    // b1����ָ��
        mov esi, dword ptr [esi];    // a1��������ַ
        mov edi, dword ptr [edi];    // b1��������ַ
        add esi, 4;
        add edi, 4;
        mov eax, dword ptr [esi];    // �����ڶ���������ַ��Print2
        mov ecx, dword ptr [edi];
        mov dword ptr [edi], eax;
        mov dword ptr [esi], ecx;
        add esi, 8;
        add edi, 8;
        mov eax, dword ptr [esi];    // �������ĸ�������ַ��PrintExtern
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

// hook��CClassA1�ĵ��������� �������Ƚ��鷳������Ҳ�ǲ���Ū�ġ�����ClassA1�ĵ������麯��ָ���滻�������Լ�����ĵ�ַ��
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
    pA1->PrintAll();    // ����ʧ��
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
