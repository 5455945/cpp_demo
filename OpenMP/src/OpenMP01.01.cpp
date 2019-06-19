#include "OpenMP01.01.h"
#include "omp.h"
#include <iostream>
#include <array>
#include <numeric>

// https://blog.csdn.net/ArrowYL/article/details/81094837

// һ��Ҫ���� /openmp��mp�����������
void test01_01() {
    // ����Ƿ�֧��openmp
#ifndef _OPENMP
    fprintf(stderr, "OpenMP not supported");
    return;
#endif
    // ������omp�겢������/openmpѡ�����Ч
#pragma omp parallel for
    for (char i = 'a'; i <= 'z'; i++)
        std::cout << i << " ";
    std::cout << std::endl;
    // ear iolbx   jy  ms  ku nt     v c   pdf   wq  z g h
    // ���û������/openmpѡ���Ȼ��˳�����

    //// �������������;���
    //// ��������о�̬�����������������л�
    ////#pragma omp parallel for
    //for (int i = 2; i < 10; i++) {
    //    factorial[i] = i * factorial[i - 1];
    //}
}

void test01_02() {
    // �����к�˽������
    //// ������������Ǵ����
    //int temp; // ��ѭ��֮������,�������ݣ����л���ÿ���̶߳��ܷ��ʣ���������
    //#pragma omp parallel for
    //for (int i = 0; i < 100; i++) {
    //    temp = array[i];
    //    array[i] = doSomething(temp);
    //}

    //// 1. ��ѭ���ڲ�����������˽�����ݣ���ȫ
    //#pragma omp parallel for
    //for (int i = 0; i < 100; i++) {
    //    int temp = array[i];
    //    array[i] = doSomething(temp);
    //}

    //// 2. ͨ��OpenMPָ��˵��˽�б�������ȫ
    //int temp;
    //#pragma omp parallel for private(temp)
    //for (int i = 0; i < 100; i++) {
    //    temp = array[i];
    //    array[i] = doSomething(temp);
    //}
}

void test01_03() {
    //int sum = 0;
    //for (int i = 0; i < 100; i++) {
    //    sum += array[i]; // sum��Ҫ˽�в���ʵ�ֲ��л��������ֱ����ǹ��еĲ��ܲ�����ȷ���
    //}
    const size_t size = 100;
    std::array<int, size> a;
    std::iota(std::begin(a), std::end(a), 1);
    int sum = 0;
    // �ڲ�ʵ���У�OpenMP Ϊÿ���߳��ṩ��˽�е�sum���������߳��˳�ʱ��OpenMP �ٰ�ÿ���̵߳Ĳ��ֺͼ���һ��õ����ս����
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; i++) {
        sum += a[i];
    }
    std::cout << sum << std::endl;

    // ���ؾ�������﷨
    // #pragma omp parallel for schedule(kind [, chunk size])
}

void test01_04() {
    // OpenMP�﷨��ʽ
    // #pragma omp ָ��[�Ӿ�],[�Ӿ�] ��]
    // ���õĹ���ָ�����£�
    //parallel ������һ���ṹ��֮ǰ����ʾ��δ��뽫������̲߳���ִ�У�
    //for������forѭ�����֮ǰ����ʾ��ѭ������������䵽����߳��в���ִ�У���ʵ������ֵ��������ɱ����Ա�Լ���֤ÿ��ѭ��֮������������ԣ�
    //parallel?for ��parallel��forָ��Ľ�ϣ�Ҳ������forѭ�����֮ǰ����ʾforѭ����Ĵ��뽫������̲߳���ִ�У���ͬʱ���в�����Ĳ���������ֵ��������ܣ�
    //sections �����ڿɱ�����ִ�еĴ����֮ǰ������ʵ�ֶ���ṹ����������ֵ����ɲ���ִ�еĴ���θ�����sectionָ������ע������sections��section����
    //parallel?sections��parallel��sections�������Ľ�ϣ�������parallel?for��
    //single�����ڲ������ڣ���ʾһ��ֻ�������߳�ִ�еĴ��룻
    //critical������һ�δ����ٽ���֮ǰ����֤ÿ��ֻ��һ��OpenMP�߳̽��룻
    //flush����֤����OpenMP�̵߳�����Ӱ���һ���ԣ�
    //barrier�����ڲ������ڴ�����߳�ͬ�����߳�ִ�е�barrierʱҪͣ�µȴ���ֱ�������̶߳�ִ�е�barrierʱ�ż�������ִ�У�
    //atomic������ָ��һ�����ݲ�����Ҫԭ���Ե���ɣ�
    //master������ָ��һ�δ��������߳�ִ�У�
    //threadprivate������ָ��һ�������������߳�ר�ã����������߳�ר�к�˽�е�����

    //��Ӧ��OpenMP�Ӿ�Ϊ��
    //private��ָ��һ������������ÿ���߳��ж������Լ���˽�и�����
    //firstprivate��ָ��һ������������ÿ���̶߳������Լ���˽�и���������˽�б���Ҫ�ڽ��벢���������ֵ���ʱ���̳����߳��е�ͬ��������ֵ��Ϊ��ֵ��
    //lastprivate��������ָ�����߳��е�һ������˽�б�����ֵ�ڲ��д���������Ƶ����߳��е�ͬ�������У����𿽱����߳���for��sections����ֵ��е����һ���̣߳�?
    //reduction������ָ��һ������������˽�еģ������ڲ��д����������Щ����Ҫִ��ָ���Ĺ�Լ���㣬����������ظ����߳�ͬ��������
    //nowait��ָ�������߳̿��Ժ��������Ƶ�ָ�����·��ͬ����
    //num_threads��ָ���������ڵ��̵߳���Ŀ��?
    //schedule��ָ��for����ֵ��е��������������ͣ�
    //shared��ָ��һ����������Ϊ����̼߳�Ĺ��������
    //ordered������ָ��for����ֵ�����ָ���������Ҫ���մ���ѭ������ִ�У�
    //copyprivate�����singleָ���ָ���̵߳�ר�б����㲥���������������̵߳�ͬ�������У�
    //copyin n������ָ��һ��threadprivate���͵ı�����Ҫ�����߳�ͬ���������г�ʼ����
    //default������ָ���������ڵı�����ʹ�÷�ʽ��ȱʡ��shared��

    // API����
    // OpenMP���ṩһ��API�������ڿ��Ʋ����̵߳�ĳЩ��Ϊ��������һЩ���õ�OpenMP API�����Լ�˵���� 
    // ��������:��������
    //omp_in_parallel:�жϵ�ǰ�Ƿ��ڲ�������
    //omp_get_thread_num:�����̺߳�
    //omp_set_num_threads:���ú����������е��̸߳�ʽ
    //omp_get_num_threads:���ص�ǰ���������е��߳���
    //omp_get_max_threads:��ȡ��������õ�����߳���Ŀ
    //omp_get_num_procs:����ϵͳ�д������ĸ���
    //omp_get_dynamic:�ж��Ƿ�֧�ֶ�̬�ı��߳�����
    //omp_set_dynamic:���û��ϵ�߳����ݵ�̬ͬ�ı�
    //omp_get_nested:�ж�ϵͳ�Ƿ�֧�ֲ���Ƕ��
    //omp_set_nested:���û�رղ���Ƕ��

    // ��������
    // OpenMP�ṩ��һЩ��������������������ʱ�Բ��д����ִ�н��п��ơ���Щ�����������Կ��ƣ�
    // 1)�����߳���;
    // 2)ָ��ѭ����λ���;
    // 3)���̰߳󶨵�������;
    // 4)����/����Ƕ�ײ��У���������Ƕ�ײ��м���;
    // 5)����/���ö�̬�߳�;
    // 6)�����̶߳�ջ��С;
    // 7)�����̵߳ȴ����ԡ�
    // ���õĻ�������:
    //OMP_SCHEDULE������forѭ�����л���ĵ��ȣ�����ֵ����ѭ�����ȵ����ͣ�
    //OMP_NUM_THREADS���������ò������е��߳�����
    //OMP_DYNAMIC��ͨ���趨����ֵ����ȷ���Ƿ�����̬�趨�������ڵ��߳�����
    //OMP_NESTED��ָ���Ƿ���Բ���Ƕ�ס�

    // OpenMPָ��Ӿ��÷�
    // parallel ����������һ�����п�ģ�Ҳ����ʹ������ָ����for��sections�Ⱥ������ʹ�á�
    // parallelָ��������Ϊһ�δ��봴������߳���ִ�����ġ�parallel���е�ÿ�д��붼������߳��ظ�ִ�С�
    // �ʹ�ͳ�Ĵ����̺߳������������൱��Ϊһ���߳���ں����ظ����ô����̺߳����������̲߳��ȴ��߳�ִ���ꡣ
    #pragma omp parallel num_threads(6)  //����6���̣߳�ÿ���̶߳�������{}�ڴ��룬���н�������6��Test
    {
        std::cout << "Test" << std::endl;
    }

    // forָ������������һ��forѭ�����䵽����߳���ִ�С�forָ��һ����Ժ�parallelָ��������γ�parallel forָ��ʹ�ã�
    // Ҳ���Ե�������parallel���Ĳ��п��С�parallel for��������һ�������򣬲������������ڶ���߳�֮����䣬���ڷֵ�����
    #pragma omp parallel for num_threads(6)
    for (int i = 0; i < 12; i++) {
        printf("OpenMP Test, �̱߳��Ϊ: %d\n", omp_get_thread_num());
    }//ָ����6���̣߳�������Ϊ12��ÿ���̶߳��ֵ���12/6=2�εĵ�������

    // sections & section
    //section���������sections�����������sections�����Ĵ��뻮�ֳɼ�����ͬ�ĶΣ�ÿ�ζ�����ִ�С��﷨��ʽ���£�
    //#pragma omp [parallel] sections [�Ӿ�]
    //    {
    //#pragma omp section
    //        {
    //            �����
    //        }
    //#pragma omp section
    //        {
    //            �����
    //        }
    //    }
    // ˵������section��Ĵ��붼�ǲ���ִ�еģ����Ҹ���section�����䵽��ͬ���߳�ִ�С�
    // ʹ��section���ʱ����Ҫע��������ַ�ʽ��Ҫ��֤����section��Ĵ���ִ��ʱ������
    // ����ĳ��sectionִ��ʱ�������section�����ʹﲻ������ִ�е�Ч���ˡ�
    // ��for�������̯����ϵͳ�Զ����У�ֻҪÿ��ѭ����û��ʱ���ϵĲ�࣬��ô��̯�Ǻܾ��ȵģ�ʹ��section�������߳���һ���ֹ������̵߳ķ�ʽ��

    // private
    // private�Ӿ����ڽ�һ�����������������߳�˽�еı���������������˽�б�����ָ��ÿ���̶߳������Լ��ı���˽�и�����
    // �����߳��޷�����˽�и�������ʹ�ڲ�����������ͬ���Ĺ����������������ڲ��������ڲ����κ����ã����Ҳ��������ڲ������������Ĺ��������
    // ����ʾ�����£�
    int k = 100;
    #pragma omp parallel for private(k)
    for (k = 0; k < 3; k++) {
        printf("k = %d \n", k);
    }
    printf("last k = %d\n", k);
    // �������ִ�к��ӡ�Ľ�����£�
    //k = 2
    //k = 1
    //k = 0
    //last k = 100
    //�Ӵ�ӡ������Կ�����forѭ��ǰ�ı���k��ѭ�������ڵı���k��ʵ��������ͬ�ı�����
    //��private�Ӿ�������˽�б����ĳ�ʼֵ�ڲ����������ڴ���δ����ģ���������̳�ͬ�����������ֵ��
    //private������˽�б������ܼ̳�ͬ��������ֵ����ʵ���������ʱ��Ҫ�̳�ԭ�й��������ֵ��
    //OpenMP�ṩ��firstprivate�Ӿ���ʵ��������ܡ�����������ʹ��firstprivate(k)��
    //���������ڵ�˽�б���k�̳������湲�����k��ֵ100��Ϊ��ʼֵ���������˳���������󣬹������k��ֵ����Ϊ100δ�䡣
    //��ʱ�ڲ��������ڵ�˽�б�����ֵ������������˳���������ʱ����Ҫ������ֵ����ͬ���Ĺ��������
    //ǰ���private��firstprivate�Ӿ����˳���������ʱ��û�н�˽�б��������ȡֵ������Ӧ�Ĺ��������
    //lastprivate�Ӿ��������ʵ�����˳���������ʱ��˽�б�����ֵ�����������������ʾ�����£�
    int k1 = 100;
    #pragma omp parallel for firstprivate(k), lastprivate(k)
    for (int i = 0; i < 3; i++) {
        k1 += i;
        printf("k1 = %d\n", k1);
    }
    printf("last k1 = %d\n", k1);
    //k1 = 100
    //k1 = 101
    //k1 = 103
    //last k1 = 103
    // �Ӵ�ӡ������Կ������˳�forѭ���Ĳ�������󣬹������k��ֵ�����103�������Ǳ���ԭ����100���䡣
    // OpenMP�淶��ָ���������ѭ����������ô�ǽ����һ��ѭ�������е�ֵ������Ӧ�Ĺ�������������section���죬
    // ��ô�����һ��section����е�ֵ������Ӧ�Ĺ��������ע������˵�����һ��section��ָ�����﷨�ϵ����һ����
    // ������ʵ������ʱ�����һ��������ġ�������ࣨclass�����͵ı���ʹ����lastprivate�����У���ôʹ��ʱ��Щ���ƣ�
    // ��Ҫһ���ɷ��ʵģ���ȷ��ȱʡ���캯�������Ǳ���Ҳ��ʹ����Ϊfirstprivate�Ӿ�Ĳ���������Ҫһ��������ֵ��������
    // �������������ֵ���������ڲ�ͬ����Ĳ���˳����δָ���ģ������ڱ������Ķ��塣

    // threadprivate
    // threadprivateָ������ָ��ȫ�ֵĶ��󱻸����̸߳��Ը�����һ��˽�еĿ������������߳̾��и���˽�е�ȫ�ֶ���
    // threadprivate��private����������threadprivate�����ı���ͨ����ȫ�ַ�Χ����Ч�ģ���private�����ı���ֻ���������Ĳ��й�������Ч��
    // ����threadprivate�ı����ĵ�ַ�����ǳ���������C++���ࣨclass�����ͱ���������threadprivate�Ĳ���ʱ��Щ���ƣ�������ʱ�����ⲿ��ʼ��ʱ��
    // ���������ȷ�Ŀ������캯��������ʾ�����£�

    static int g;
#pragma omp threadprivate(g) // һ��Ҫ������
    omp_set_dynamic(0); // ��ʹ��threadprivateʱ��һ��Ҫ�ȵ���omp_set_dynamic(0)�رն�̬�̵߳����ԣ����ܱ�֤�����ȷ��
#pragma omp parallel
    {
        g = omp_get_thread_num();
        printf("tid: %d\n", g); // ���һ�����0~3
    } // End of parallel region
#pragma omp parallel
    {
        int temp = g * g;
        printf("tid: %d, tid*tid: %d\n", g, temp); // ��ͬ�߳���ȫ�ֱ���ֵ��ͬ
    } // End of parallel region
    // ע�⣺��ʹ��threadprivate��ʱ��Ҫ��omp_set_dynamic(0)�رն�̬�̵߳����ԣ����ܱ�֤�����ȷ��

    // Share
    // shared�Ӿ������������һ����������Ϊ�����������ν�Ĺ����������ָ��һ�����������team�ڵ������߳�ֻӵ�б�����һ���ڴ��ַ��
    // �����̷߳���ͬһ��ַ�����ԣ����ڲ��������ڵĹ����������Ҫ�������ݾ���������Ҫ��ֹ��������Ҫ���Ӷ�Ӧ�ı���������ʾ�����£�
#define COUNT 10000
    int sum = 0;
#pragma omp parallel for shared(sum)
    for (int i = 0; i < COUNT; i++) {
        sum = sum + i;
    }
    printf("%d\n", sum);

    // ������У�������ܲ�һ������Ҫע����ǣ�ѭ������������ѭ��������������˽�еģ�������ѭ�����������ڵ��Զ���������˽�еġ�
    // ���ѭ����������Ҳ�ǹ��еģ�OpenMP�����ȥִ�У�����Ҳֻ����˽�е��ˡ���ʹʹ��shared������ѭ������������
    // Ҳ����ı�ѭ������������ѭ��������������˽�е���һ�ص㡣����ʾ�����£�
    int sum2 = 0;
    int i2 = 0;
#pragma omp parallel for shared(sum2, i2)
    for (i2 = 0; i2 < COUNT; i2++) {
        sum2 = sum2 + i2;
    }
    printf("%d\n", i2);
    printf("%d\n", sum2);
    // ���������У�ѭ����������i�����ֵΪ0����������ʹ��shared���α���i��ע�⣬����Ĺ���ֻ�����ѭ���������򣬶��������Ĳ�������û��������Ҫ��
    // ͬʱ��ѭ�����������ڣ�ѭ�����������ǲ����޸ĵġ��������������У�������forѭ�����ڶ�ѭ����������i�����޸ġ�

    // Default
    // defaultָ�����������ڱ��������ԣ�C++��OpenMP��default�Ĳ���ֻ��Ϊshared��none��default(shared)����ʾ���������ڵĹ�������ڲ�ָ��������¶���shared����
    // default(none)����ʾ������ʽָ�����й���������������ԣ�����ᱨ�����Ǳ�������ȷ�����Զ��壨����ѭ�����������ѭ����������ֻ����˽�еģ�
    // ���һ����������û��ʹ��default�Ӿ䣬��ô��Ĭ����ΪΪdefault(shared)��

    // Copyin
    // copyin�Ӿ����ڽ����߳���threadprivate������ֵ������ִ�в�������ĸ����̵߳�threadprivate�����У�
    // �Ӷ�ʹ��team�ڵ����̶߳�ӵ�к����߳�ͬ���ĳ�ʼֵ������ʾ�����£�
    static int A = 100;
#pragma omp threadprivate(A)
#pragma omp parallel for
    for (int i = 0; i < 10; i++) {
        A++;
        printf("Thread ID: %d, %d: %d\n", omp_get_thread_num(), i, A);  // #1
    }
    printf("Global A: %d\n", A); // ����������Ĵ�ӡ�ġ�Globa A����ֵ���Ǻ�ǰ���thread 0�Ľ����ȣ���Ϊ�˳����������ֻ��master�̼߳�0���߳����С�
#pragma omp parallel for copyin(A)
    for (int i = 0; i < 10; i++) {
        A++;
        printf("Thread ID: %d, %d: %d\n", omp_get_thread_num(), i, A);  // #1
    }
    printf("Global A: %d\n", A); // #2
    // ��ʹ��copyin������£�����ڶ������������ʱ�򣬲�ͬ�̵߳�˽�и���A�ĳ�ʼֵ�ǲ�һ���ģ�����ʹ����copyin֮��
    // �������е��̵߳ĳ�ʼֵ��ʹ�����̵߳�ֵ��ʼ����Ȼ��������㣬�����ֵ��Ϊ����thread 0�Ľ��������⣬��ʹ����copyin��
    // ���е��̵߳�threadprivate���͵ĸ����������������̵߳ĸ�����������һ�Ρ�ͬ������ ����copyin�еĲ������뱻������threadprivate�ģ�
    // ���������͵ı��������������ȷ�Ŀ�����ֵ��������

    //Copyprivate
    // copyprivate�Ӿ����ڽ��߳�˽�и���������ֵ��һ���̹߳㲥��ִ��ͬһ��������������̵߳�ͬһ������copyprivateֻ������singleָ�singleָ�� : 
    // ����һ��ֻ�������߳�ִ�еĴ����֮ǰ, ��ʾ����Ĵ���ν������߳�ִ�У����Ӿ��У���һ��single��Ľ�β����ɹ㲥������
    // copyprivateֻ������private / firstprivate��threadprivate���εı���������ʾ�����£�
    static int counter = 0; // ��������static ���ܻᵼ�²���
    #pragma omp threadprivate(counter)
    auto f001 = []() {
        counter++;
        return counter;
    };
    #pragma omp parallel 
    {
        int count;
#pragma omp single copyprivate(counter)
        {
            counter = 50;
        }
        count = f001();
        printf("ThreadId: %ld, count = %ld\n", omp_get_thread_num(), count);
    }
    //��ӡ���Ϊ��
    //ThreadId: 2, count = 51
    //ThreadId : 3, count = 51
    //ThreadId : 0, count = 51
    //ThreadId : 1, count = 51
    // ���û��ʹ��copyprivate�Ӿ䣬���ܴ�ӡ���Ϊ
    //ThreadId: 2, count = 1
    //ThreadId : 1, count = 1
    //ThreadId : 0, count = 51
    //ThreadId : 3, count = 1
    //���Կ�����ʹ��copyprivate�Ӿ��single�����ڸ�counter����ֵ���㲥���������߳����û��ʹ��copyprivate�Ӿ�ʱ��
    //ֻ��һ���̻߳����single�����ڵĸ�ֵ�������߳�û�л�ȡsingle�����ڵĸ�ֵ��

    // OpenMP�е��������
    // OpenMP�У����������Ҫ���ڲ��е�forѭ���У���ѭ����ÿ�ε����ļ����������ʱ������򵥵ظ������̷߳�����ͬ�����ĵ����Ļ���
    // ����ɸ����̼߳��㸺�ز����⣬���ʹ����Щ�߳���ִ���꣬��Щ��ִ���꣬���ĳЩCPU�˿��У�Ӱ��������ܡ�
    // OpenMP�ṩ��schedule�Ӿ���ʵ������ĵ��ȡ�schedule�Ӿ��ʽ��schedule(type, [size])��
    // ����type��ָ���ȵ����ͣ�����ȡֵΪstatic��dynamic��guided��runtime����ֵ������runtime����������ʱȷ���������ͣ����ʵ�ʵ��Ȳ���ֻ��ǰ�����֡�
    // ����size��ʾÿ�ε��ȵĵ����������������������ò����ǿ�ѡ�ġ���type��ֵ��runtimeʱ�����ܹ�ʹ�øò�����

    // ��̬����static
    // �󲿷ֱ�������û��ʹ��schedule�Ӿ��ʱ��Ĭ����static���ȡ�static�ڱ����ʱ����Ѿ�ȷ���ˣ���Щѭ������Щ�߳�ִ�С�
    // ������n��ѭ��������t���̣߳���ô��ÿ���߳̾�̬�����Լn / t�ε������㡣n / t��һ�������������ʵ�ʷ���ĵ����������ܴ��ڲ�1�������
    // �ڲ�ʹ��size����ʱ�������ÿ���̵߳���n / t�������ĵ�������ѭ������Ϊ10���߳���Ϊ2�����߳�0�õ���0��4�������������߳�1�õ�5��9������������
    // ��ʹ��sizeʱ����ÿ�θ��̷߳���size�ε�������ѭ������Ϊ10���߳���Ϊ2��ָ��sizeΪ2��0��1�ε���������߳�0��2��3�ε���������߳�1���Դ����ơ�

    // ��̬����dynamic
    // ��̬��������������ʱ��״̬��̬ȷ���߳���ִ�еĵ�����Ҳ�����߳�ִ�����Ѿ����������󣬻�ȥ��ȡ���е������뾲̬�������Ĳ�ͬ��
    // ÿ���߳���ɵ������������ܲ�һ�����������߳�������ִ�����ʱ�䲻ȷ�������Ե��������䵽�ĸ��߳����޷�����֪���ġ�
    // ����ʹ��size ʱ���ǽ���������ط��䵽�����̡߳���ʹ��size ʱ���������size�������������̣߳�����÷����ƾ�̬���ȡ�

    // ����ʽ����guided
    // ��������ʽ���ȷ������е��ȣ�ÿ�η�����̵߳���������ͬ����ʼ�Ƚϴ��Ժ��𽥼�С����ʼʱÿ���̻߳���䵽�ϴ�ĵ����飬
    // ֮����䵽�ĵ�������𽥵ݼ���������Ĵ�С�ᰴָ�����½���ָ����size��С�����û��ָ��size��������ô�������С��С�ή��1��
    // size��ʾÿ�η���ĵ�����������Сֵ������ÿ�η���ĵ����������𽥼��٣��ٵ�sizeʱ�������ټ��١�
    // ���������һ������ʽ�㷨����Ҫ�ο�����ı�����������ֲ����Ϣ��

    // ���ȷ�ʽ�ܽ�
    // ��̬����static��ÿ����Щѭ�����Ǹ��߳�ִ���ǹ̶��ģ�������ԡ�����ÿ���̵߳������ǹ̶��ģ����ǿ����е�ѭ������ִ�п죬�е��������ܴﵽ���š�
    // ��̬����dynamic�������̵߳�ִ�п������Ѿ����������̻߳��Զ������µ������������飬ÿ����ȡ��������ǹ̶��ġ�
    // ����ʽ����guided��ÿ�����������������ȴ��С��ָ���½������д���������Ҫѭ��ʱ���տ�ʼΪ�̷߳����������
    // ������񲻶�ʱ����ÿ���߳��������񣬿��Դﵽ�߳�������⡣

    // OpenMP������Ƽ����ܽ�
    // 1.��ѭ����������ʱ������ֳɹ�����߳���ִ�еĻ������ܻ�ʹ���ܵ�����ʱ����ڽ����̻߳�һ���̵߳�ִ����������һ������ܺģ�
    // 2.������õ��߳�����Զ����CPU�ĺ����Ļ�����ô�����Ŵ����������л��͵��ȵĿ�����Ҳ�ή�������Ч�ʡ�
    // 3.��Ƕ��ѭ���У�������ѭ��������������ʱ���������CPU�������ӵ�һ���̶�ʱ���������߳���������С��CPU������
    // ��������ڲ�ѭ�����ڸ���ƽ�������£����ѵ������ѭ��ʹ֮�ﵽ����ƽ�⡣
}

void test01_05() {
    // Ĭ�ϲ���,һ����Ĭ�ϵĺ���
#pragma omp parallel
    {
        printf("Hello, World!\n");
    }

    // ָ�������߳�����
#pragma omp parallel num_threads(4)
    {
        printf("Hello, World!, ThreadId = %d\n", omp_get_thread_num());
    }

//    // ����for���
//#pragma omp for // ����ʹ��forû��Ч����Ҫ��parallel������ò���
//    for (int i = 0; i < 20; i++) {
//        printf("i = %d, ThreadId = %d\n", i, omp_get_thread_num());
//    }

#pragma omp parallel for // ����ʹ��forû��Ч����Ҫ��parallel������ò���
    for (int i = 0; i < 20; i++) {
        printf("i = %d, ThreadId = %d\n", i, omp_get_thread_num());
    }

#pragma omp parallel // ����������д��
    {
#pragma omp for
        for (int i = 0; i < 20; i++) {
            printf("i = %d, ThreadId = %d\n", i, omp_get_thread_num());
        }
    }

    int j = 0;
#pragma omp parallel // ����������д��
    {
#pragma omp for
        for (j = 0; j < 20; j++) {
            printf("j = %d, ThreadId = %d\n", j, omp_get_thread_num());
        }
#pragma omp for
        for (j = 0; j < 20; j++) {
            printf("j = %d, ThreadId = %d\n", j, omp_get_thread_num());
        }
    }

#pragma omp parallel sections
    {
#pragma omp section
    printf("section 1 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
    printf("section 2 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
    printf("section 3 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
    printf("section 4 ThreadId = %d\n", omp_get_thread_num());
    }

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            printf("section 1 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
            printf("section 2 ThreadId = %d\n", omp_get_thread_num());
        }
#pragma omp sections
        {
#pragma omp section
            printf("section 3 ThreadId = %d\n", omp_get_thread_num());
#pragma omp section
            printf("section 4 ThreadId = %d\n", omp_get_thread_num());
        }
    }
}
// https://blog.csdn.net/ArrowYL/article/details/81094837
void test0101() {
    test01_01();
    test01_02();
    test01_03();
    test01_04();
    test01_05();
}
