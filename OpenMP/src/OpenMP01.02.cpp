#include "OpenMP01.01.h"
#include "omp.h"
#include <iostream>

// [���м���] 2. OpenMP���
// https://blog.csdn.net/magicbean2/article/details/75530667

// [���м���] 1. ���м�����
// https://blog.csdn.net/magicbean2/article/details/75174859

// ������ָ� ������ָ�������Դ�����п��ܱ���ʾΪע�ͣ����ұ������������ԣ����������Եظ��߱���������ͨ��������������ʵ��ı�������ʶ��
// �⽫�� 5. OpenMP������� �н������ۡ�OpenMP�ı�����ָ���Ŀ����Ҫ�У�
// 1������һ����������
// 2�������߳��еĴ���飻
// 3�����߳�֮�����ѭ��������
// 4�����л�����Σ�
// 5��ͬ���̼߳�Ĺ�����

// ������ָ����﷨����
// sentinel directive-name [clause, ...]
// ��: #pragma omp parallel default(shared) private(beta,pi)

//����ʱ�⺯���� OpenMP API�е�����ʱ�⺯���ǲ��������ģ�����ҪĿ�������
// 1�����úͲ�ѯ�߳�����
// 2����ѯ�̵߳�Ψһ��ʶ����ID�����̵߳����ȱ�ʶ���������߳���Ĵ�С�ȣ�
// 3�����úͲ�ѯ��̬�̵߳����ԣ�
// 4����ѯ�Ƿ��ڲ��������Լ���ʲô����Ĳ��������У�
// 5�����úͲ�ѯǶ�ײ��У�
// 6�����á���ʼ���Լ���ֹ������Ƕ������
// 7����ѯ����ʱ��ͷֱ��ʡ�
// ���������� OpenMP�ṩ��һЩ��������������������ʱ�Բ��д����ִ�н��п��ơ�
// ��Щ�����������Կ��ƣ�
// 1�������߳�����
// 2��ָ��ѭ����λ��֣�
// 3�����̰߳󶨵���������
// 4������/����Ƕ�ײ��У���������Ƕ�ײ��м���
// 5������/���ö�̬�̣߳�
// 6�������̶߳�ջ��С��
// 7�������̵߳ȴ����ԡ�

// ָ����Ч��Χ
//��̬���ʻ㣩��Χ��
//�����Ա��ĵķ�ʽ������ָ��֮��Ľṹ�����У�
//ָ��ľ�̬��Χ����Խ������̻��ߴ����ļ���
//����ָ�
//��������һ����װָ���OpenMPָ���Ϊ��һ������ָ�����������һ��ָ��ľ�̬���ʷ�����Χ֮�⣻
//����ָ���Խ���̻��߿��ܵĴ����ļ���
//��̬��Χ��
//ָ��Ķ�̬��Χ�����侲̬���ʷ�����Χ�Լ�����ָ��ķ�Χ��

//��̬��չ��forָ���ڷ�ղ��п��ڷ�����
//����ָ�CRITICAL��SECTIONSָ���ڷ�ղ��п��ⷢ����
//��̬��չ��CRITICAL��SECTIONSָ����for��PARALLELָ��Ķ�̬�������з�����

//�������򹹽�
//#pragma omp parallel [clause ...]  newline 
//if (scalar_expression)
//private (list)
//shared(list)
//default (shared | none)
//firstprivate(list)
//reduction(operator: list)
//copyin(list)
//num_threads(integer - expression)

// do/forָ��
//#pragma omp for [clause ...]  newline 
//schedule(type[, chunk])
//ordered
//private (list)
//firstprivate(list)
//lastprivate(list)
//shared(list)
//reduction(operator: list)
//collapse(n)
//nowait
//for_loop

void test0102_01() {
    int nthreads, tid;
    // Fork a team of threads with each thread having a private tid variable
#pragma omp parallel private(tid)
    {
        // Obtain and print thread id
        tid = omp_get_thread_num();
        printf("Hello World from thread = %d\n", tid);

        // Only master thread does this
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Number of threads = %d\n", nthreads);
        }
    }  // All threads join master thread and terminate
}

void test0102_02() {
    const int N{ 1000 };
    const int CHUNKSIZE{ 100 };
    int i, chunk;
    double a[N], b[N], c[N];

    // Some initializations
    for (i = 0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    chunk = CHUNKSIZE;

#pragma omp parallel shared(a,b,c,chunk) private(i)
    {
#pragma omp for schedule(dynamic,chunk) nowait
        for (i = 0; i < N; i++)
            c[i] = a[i] + b[i];
    }   // end of parallel region
}

void test0102_03() {
    const int N{ 1000 };
    int i;
    double a[N], b[N], c[N], d[N];

    // Some initializations
    for (i = 0; i < N; i++) {
        a[i] = i * 1.5;
        b[i] = i + 22.35;
    }

#pragma omp parallel shared(a,b,c,d) private(i)
    {
#pragma omp sections nowait
        {
#pragma omp section
            for (i = 0; i < N; i++)
                c[i] = a[i] + b[i];

#pragma omp section
            for (i = 0; i < N; i++)
                d[i] = a[i] * b[i];
        }  // end of sections
    }  // end of parallel region
}

void test0102_04() {
    const int N{ 1000 };
    const int CHUNKSIZE{ 100 };
    int i, chunk;
    double a[N], b[N], c[N];

    // Some initializations
    for (i = 0; i < N; i++)
        a[i] = b[i] = i * 1.0;
    chunk = CHUNKSIZE;

#pragma omp parallel for shared(a,b,c,chunk) private(i) schedule(static,chunk)
    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];
}

void test0102_05() {
    int x = 0;
#pragma omp parallel shared(x) 
    {
#pragma omp critical 
        x = x + 1;
    }  // end of parallel region
}

void test0102_06() {
    int b, tid;
    static int a;
    static double x;
#pragma omp threadprivate(a, x)
    // Explicitly turn off dynamic threads
    omp_set_dynamic(0);
    printf("1st Parallel Region:\n");
#pragma omp parallel private(b,tid)
    {
        tid = omp_get_thread_num();
        a = tid;
        b = tid;
        x = 1.1 * tid + 1.0;
        printf("Thread %d:   a,b,x= %d %d %f\n", tid, a, b, x);
    }  // end of parallel region

    printf("************************************\n");
    printf("Master thread doing serial work here\n");
    printf("************************************\n");

    printf("2nd Parallel Region:\n");
#pragma omp parallel private(tid)
    {
        tid = omp_get_thread_num();
        printf("Thread %d:   a,b,x= %d %d %f\n", tid, a, b, x);
    }  // end of parallel region
}

void test0102_07() {
    int i, n, chunk;
    double a[100], b[100], result;

    // Some initializations
    n = 100;
    chunk = 10;
    result = 0.0;
    for (i = 0; i < n; i++) {
        a[i] = i * 1.0;
        b[i] = i * 2.0;
    }

#pragma omp parallel for default(shared) private(i) \
    schedule(static, chunk) reduction(+:result)
    for (i = 0; i < n; i++) {
        result = result + (a[i] * b[i]);
    }
    printf("Final result= %f\n", result);
}

void test0102() {
    test0102_01();
    test0102_02();
    test0102_03();
    test0102_04();
    test0102_05();
    test0102_06();
    test0102_07();
}