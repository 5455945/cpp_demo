// *********************************************************************************************
// Copyright (C) 2013-2014    Zhangfj    corporation
// All Rights Reserved
// 
// FileName      : DMSingleton.h
// FileTarget    : DMSingleton.h
// Description   : Singleton ģʽ
// ����
// ������Singleton��ģʽ��֤һ�������һ��ʵ�������ṩһ����������ȫ�ַ��ʵ㡣
// ���
// 1.Singletonģʽ����ȡ��ȫ�־�̬������C++ͨ����̬��Ա������ʵ����ʵ��ȫ��Ψһ�ԡ�
// 2.Instance()�����ǵ����ṩ��Ψһ������ڡ�
// Ҫ��
// 1.Ϊ�˷�ֹ�����ò������ʵ���������췽���������������������췽������ֵ���ط�������Ϊprotected��
// 2.instance()������������ʽ�����֣�ʹ�þֲ�static�������������״ν���ֲ������ڲ������ڳ������ʱ���٣�ͨ��new�����¶���������������delete����
// 3.��ȡ����ʵ�����÷�ʽ��Singleton::Instance()��ȡ����ָ�롣
// 4.������߳���Դ����������ʹ�������ġ�˫����������취���������������ǰ�������󶼼������Ƿ�������������ܱ�֤����Ч�����ܱ�֤����ʵ����Ψһ�ԡ�
// Ӧ��
// 1.���벿��ʹ����ģ�浥����CSingleton<T>�����ɲ�����ͬ����ĵ����ࡣ
// 2.һ����Ҫ��Ϊ�����࣬�ѵ�������Ϊ�Լ�����Ԫ��ʵ�֡���ΪCSingleton�Ĺ������������protected������Ҳ��ͨ���̳е�����ʵ�֡�
// 3.�������Ժܼ�ʵ�֣�Ҳ�����㹻���ӡ�Loki��ʵ����һ���Ƚϸ��ӵĵ����������ͺ͸��ֲ��ԣ��������ԡ������ڲ��ԡ��̲߳��Եȣ���Ϊģ���������װ����SingletonHolder��ģ�塣

// 
// version        date        Author        Description
// 0001-0001      2013-02-28  Zhangfj       �½�
// 
// *********************************************************************************************
#ifndef __DMSINGLETON__H__
#define __DMSINGLETON__H__
class Singleton
{
private:
	static Singleton* m_pSingleton;
	Singleton();
    Singleton(const Singleton&){};                // ��ֹ����������һ��ʵ��
    Singleton &operator =(const Singleton&){};    // ��ֹ��ֵ�������һ��ʵ��
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
//        //double check. ��ǰ�������⣬��֤Ч�ʺͶ��߳���ȷ��
//        if (!m_pInstance)
//        {
//            //TODO: ����. CMutexGuard guard(m_lock);
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
//    CSingleton(){}; //��ֹ����ʵ��
//    CSingleton(const CSingleton&){}; //��ֹ����������һ��ʵ��
//    CSingleton &operator =(const CSingleton&){}; //��ֹ��ֵ�������һ��ʵ��
//    virtual ~CSingleton()
//    {
//        if (m_pInstance)
//        {
//            delete m_pInstance;
//            m_pInstance = NULL;
//        }
//    };
//private:
//    static T* m_pInstance; //���Ψһʵ��
//    //TODO: ʡ���˻�������Աm_lock
//};
//
////////////////////Singletonʵ�ֲ���
//template<class T> T* CSingleton<T>::m_pInstance = NULL;
///////////////////SingletonӦ��ʵ��
//class CMyLog
//{
//friend class CSingleton<CMyLog>; //��Ϊ��Ԫ���Է���CSingleton�ı�����Ա
//public:
//    void Log(char* pszStr)
//    {
//        cout << "Log msg: " << pszStr << endl;
//    }
//private:
//    CMyLog(){}; //������ֱ��ʵ����
//};
//
//int main()
//{
//    CMyLog* pLog = CSingleton<CMyLog>::instance();
//    pLog->Log("hello word");
//    system("pause");
//    return 0;
//}
