// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMSingleton.h
// FileTarget    : DMSingleton.h
// Description   : Singleton 模式
// 定义
// 单件（Singleton）模式保证一个类仅有一个实例，并提供一个访问它的全局访问点。
// 理解
// 1.Singleton模式用来取代全局静态变量。C++通过静态成员变量来实现类实例全局唯一性。
// 2.Instance()方法是单件提供的唯一调用入口。
// 要点
// 1.为了防止外界调用产生多个实例，将构造方法、析构方法、拷贝构造方法、赋值重载方法都作为protected。
// 2.instance()方法产生对象方式有两种：使用局部static对象，生命期在首次进入局部生命期产生，在程序结束时销毁；通过new产生新对象，在析构方法中delete对象。
// 3.获取单件实例调用方式：Singleton::Instance()获取对象指针。
// 4.解决多线程资源竞争条件。使用著名的“双检测锁定”办法来解决，即在锁定前和锁定后都检测对象是否产生，这样既能保证加锁效率又能保证单件实例的唯一性。
// 应用
// 1.代码部分使用类模版单件（CSingleton<T>），可产生不同种类的单件类。
// 2.一个类要成为单件类，把单件类作为自己的友元来实现。因为CSingleton的构造和析构都是protected。另外也有通过继承单件来实现。
// 3.单件可以很简单实现，也可以足够复杂。Loki库实现了一个比较复杂的单件，将类型和各种策略（创建策略、生命期策略、线程策略等）作为模板参数，封装成了SingletonHolder类模板。

// 
// version        date        Author        Description
// 0001-0001      2013-02-28  Zhangfj       新建
// 
// *********************************************************************************************
#ifndef __DMSINGLETON__H__
#define __DMSINGLETON__H__
class Singleton
{
private:
	static Singleton* m_pSingleton;
	Singleton();
    Singleton(const Singleton&){};                // 防止拷贝构造另一个实例
    Singleton &operator =(const Singleton&){};    // 防止赋值构造出另一个实例
	~Singleton();
public:
	static Singleton* Instance();
	void Test();
};
#endif //__DMSINGLETON__H__

//
//#include <iostream>
//using namespace std;
//
//template<class T>
//class CSingleton
//{
//public:
//    static T* instance()
//    {
//        //double check. 锁前和锁后检测，保证效率和多线程正确性
//        if (!m_pInstance)
//        {
//            //TODO: 加锁. CMutexGuard guard(m_lock);
//            if (!m_pInstance)
//            {
//                //static T t;
//                //m_pInstance = &t;
//                m_pInstance = new T;
//            }
//        }
//        return m_pInstance;
//    };
//protected:
//    CSingleton(){}; //防止产生实例
//    CSingleton(const CSingleton&){}; //防止拷贝构造另一个实例
//    CSingleton &operator =(const CSingleton&){}; //防止赋值构造出另一个实例
//    virtual ~CSingleton()
//    {
//        if (m_pInstance)
//        {
//            delete m_pInstance;
//            m_pInstance = NULL;
//        }
//    };
//private:
//    static T* m_pInstance; //类的唯一实例
//    //TODO: 省略了互斥锁成员m_lock
//};
//
////////////////////Singleton实现部分
//template<class T> T* CSingleton<T>::m_pInstance = NULL;
///////////////////Singleton应用实例
//class CMyLog
//{
//friend class CSingleton<CMyLog>; //作为友元可以访问CSingleton的保护成员
//public:
//    void Log(char* pszStr)
//    {
//        cout << "Log msg: " << pszStr << endl;
//    }
//private:
//    CMyLog(){}; //不允许直接实例化
//};
//
//int main()
//{
//    CMyLog* pLog = CSingleton<CMyLog>::instance();
//    pLog->Log("hello word");
//    system("pause");
//    return 0;
//}
