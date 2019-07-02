#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
#include <iostream>
// 2 ��˳��һ�µ��ڴ�˳��
// �¼������ǵ�һ��ȫ��˳���̲߳��غ��¼���˳��һ�£��̲߳��غ��¼���˳��һ�£��̲߳��غ��¼���˳��һ�¡�
// CPU������ڲ�����������Ϊ��ͬ���ڴ汣���˲�ͬ��ֵ��
// ��ʹ�߳�����������ͬ�Ĵ��룬���������߳��еĲ���û����ȷ��˳��Լ�������ǿ������¼���˳��һ�¡�
// ��û��������˳��Լ��ʱ��Ψһ��Ҫ�������е��̶߳�ÿ�������������޸�˳����һ�¡�

// 3 ��ɢ˳��
// 
namespace {
    // ���ɲ����м�����������Ҫ��
    std::atomic<bool> x, y;
    std::atomic<int> z;
    std::atomic<bool> run_flag = false;
    void write_x_then_y()
    {
        if (!run_flag.load()) {
            std::this_thread::yield();
        }
        x.store(true, std::memory_order_relaxed); // ��
        y.store(true, std::memory_order_relaxed); // ��
    }
    void read_y_then_x()
    {
        if (!run_flag.load()) {
            std::this_thread::yield();
        }
        while (!y.load(std::memory_order_relaxed)); // ��
        if (x.load(std::memory_order_relaxed))      // ��
            ++z;
    }
}
void Concurrency05_05() {
    for (int i = 0; i < 10000; i++) {
        x = false;
        y = false;
        z = 0;
        std::thread a(write_x_then_y);
        std::thread b(read_y_then_x);
        run_flag.store(true);
        a.join();
        b.join();
        assert(z.load() != 0); // ��
        if (z.load() == 0) { // ��vs2017�����£�û�������������������˵���ʺܵ�
            std::cout << i << " z.load() =" << z.load() << std::endl;
        }
    }
}
// assert�ݿ��ܴ�������Ϊx��������ܹ�����false������y������۶�����
// true����x�Ĵ洢�ٷ�����y�洢��֮ǰ��x��y�ǲ�ͬ�ı��������Թ���ÿ
// ��������������ֵ�Ŀɼ���û��˳��֤��
