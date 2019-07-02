#include "Concurrency08.h"
#include <algorithm>
#include <numeric>
// 8.2 Ӱ�첢���������ܵ�����
// 8.2.1 �ж��ٴ�����
// 8.2.2 ���ݾ�����ƹ�һ���
// �߾���(high contention)
// �;���(low contention)
// ƹ�һ���(cache ping-pong)
// ���һ��ԭ�ӱ�������ͬ�߳�Ƶ������-�޸�-д��(ÿ���߳������������ǳ���)���ͻᵼ�´������������л����Ӷ�����ping-pong���档
// 8.2.3 �ٹ���(false sharing)
// ������(cache line):���������ػ���ʱ����һ����С������(����飬cache line)��
// �����ͬ�̵߳ı�����ͬһ��cache line �б�����-�޸�-д�����������������cache line��Ƶ���������л���
// ����ȥ���cache line�����ڱ���ͬ�̹߳���һ��������Ϊ�ٹ���
// 8.2.4 ����Ӧ�ö����
// �����л�(task switching)
//�����л������ڴ����̴߳��ھ��������ǵȴ�״̬ʱ�ر�ͻ����
// 8.2.5 ���ȶ��ĺ͹���������л�
// 8.3 Ϊ���߳�����������ݽṹ
// ��Ϊ���߳��������������ݽṹʱ��Ҫ���ǵĹؼ����������ݾ������ٹ�������ݽӽ���
// 8.3.1 Ϊ���Ӳ�����������Ԫ��
// 8.3.2 �������ݽṹ�е����ݷ��ʷ�ʽ
// 8.4 Ϊ�������ʱ�Ķ��⿼��
// 8.4.1 �����㷨�е��쳣��ȫ
// a. �����쳣��ȫ��
// b. std::async���쳣��ȫ
// 8.4.2 ����չ�ԺͰ�ķ�������(Amdahl's law)
// p = \dfrac{1}{f_s + \dfrac{1-f_s}{N}}
// 8.4.3 ���߳������ӳ�
// 8.4.4 �ò����ṩ��Ӧ��
// 8.5 ��ʵ������Ʋ�������
// 8.5.1 std::for_each�Ĳ���ʵ��
// 8.5.2 std::find�Ĳ���ʵ��
// 8.5.3 std::partial_sum�Ĳ���ʵ��
// ʹ������(barrier)
namespace {
    // std::accumulate�Ĳ��а汾(����02.08)
    template<typename Iterator, typename T>
    struct accumulate_block
    {
        void operator()(Iterator first, Iterator last, T& result)
        {
            result = std::accumulate(first, last, result);
        }
    };

    template<typename Iterator, typename T>
    T parallel_accumulate(Iterator first, Iterator last, T init)
    {
        unsigned long const length = std::distance(first, last);

        if (!length)
            return init;

        unsigned long const min_per_thread = 25;
        unsigned long const max_threads =
            (length + min_per_thread - 1) / min_per_thread;

        unsigned long const hardware_threads =
            std::thread::hardware_concurrency();

        unsigned long const num_threads =
            std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

        unsigned long const block_size = length / num_threads;

        std::vector<T> results(num_threads);
        std::vector<std::thread> threads(num_threads - 1);

        Iterator block_start = first;
        for (unsigned long i = 0; i < (num_threads - 1); ++i)
        {
            Iterator block_end = block_start;
            std::advance(block_end, block_size);
            threads[i] = std::thread(
                accumulate_block<Iterator, T>(),
                block_start, block_end, std::ref(results[i]));
            block_start = block_end;
        }
        accumulate_block<Iterator, T>()(block_start, last, results[num_threads - 1]);

        std::for_each(threads.begin(), threads.end(),
            std::mem_fn(&std::thread::join));

        return std::accumulate(results.begin(), results.end(), init);
    }
}
#include <list>
#include <iostream>
#include <vector>
void Concurrency08_02() {
    std::cout << __FUNCTION__ << std::endl;
    std::list<int> l = { 1, 2, 5, 3, 4, 9, 6, 7, 8, 0 };
    int result = parallel_accumulate<std::list<int>::iterator, int>(l.begin(), l.end(), 0);
    std::cout << "result = " << result << std::endl;
    std::vector<int> vi;
    for (int i = 0; i < 10; ++i)
    {
        vi.push_back(i);
    }
    int sum = parallel_accumulate(vi.begin(), vi.end(), 0);
    std::cout << "sum=" << sum << std::endl;
}
