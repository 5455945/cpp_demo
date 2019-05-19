// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : VirtualTableHook.h
// FileTarget    : VirtualTableHook.h
// Description   : 虚表hook方式
// 
// version        date        Author        Description
// 0001-0001      2014-04-21  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __VIRTUALTABLEHOOK__H__
#define __VIRTUALTABLEHOOK__H__
#include <iostream>

#pragma comment(linker,"/SECTION:.rdata,RW")
class CClassA1
{
public:
    CClassA1():m_nValue1(2), m_nValue2(3){};
    CClassA1(int nValue1, int nValue2)
    {
        m_nValue1 = nValue1;
        m_nValue2 = nValue2;
    }

    virtual void Print1()
    {
        std::cout << "CClassA1::m_nValue1 = " << m_nValue1 << std::endl;
    }
    virtual void Print2()
    {
        std::cout << "CClassA1::m_nValue2 = " << m_nValue2 << std::endl;
    }
    virtual void PrintAll()
    {
        std::cout << "CClassA1::m_nValue1 = "<< m_nValue1 << "\t\t" << "CClassA1::m_nValue2 = " << m_nValue2 << std::endl;
    }
    virtual void PrintExtern(int nExtern)
    {
        std::cout << "CClassA1::PrintExtern(" << nExtern << "） = " << (nExtern + 5) << std::endl;
    }

private:
    int m_nValue1;
    int m_nValue2;
};


class CClassB1
{
public:
    CClassB1():m_nValue1(6), m_nValue2(8){};
    CClassB1(int nValue1, int nValue2)
    {
        m_nValue1 = nValue1;
        m_nValue2 = nValue2;
    }
    virtual void Print1()
    {
        std::cout << "CClassB1::m_nValue1 = " << m_nValue1 << std::endl;
    }
    virtual void Print2()
    {
        std::cout << "CClassB1::m_nValue2 = " << m_nValue2 << std::endl;
    }
    virtual void PrintAll()
    {
        std::cout << "CClassB1::m_nValue1 = "<< m_nValue1 << "\t\t" << "CClassB1::m_nValue2 = " << m_nValue2 << std::endl;
    }
    virtual void PrintExtern(int nExtern)
    {
        std::cout << "CClassB1::PrintExtern(" << nExtern << "） = " << (nExtern + 4) << std::endl;
    }

private:
    int m_nValue1;
    int m_nValue2;
};

void TestHook1(void);
void TestHook2(void);
void TestHook3(void);
void TestHook4(void);

#endif// __VIRTUALTABLEHOOK__H__