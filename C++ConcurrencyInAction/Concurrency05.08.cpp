#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
namespace {
    // ��ȡ-�ͷŲ�����������ɢ������ʩ��˳��
    std::atomic<bool> x, y;
    std::atomic<int> z;

    void write_x_then_y()
    {
        x.store(true, std::memory_order_relaxed); // ����ת���ȴ�y����Ϊtrue
        y.store(true, std::memory_order_release); // ��
    }

    void read_y_then_x()
    {
        while (!y.load(std::memory_order_acquire)); // ��
        if (x.load(std::memory_order_relaxed))      // ��
            ++z;
    }
}
void Concurrency05_08() {
    for (int i = 0; i < 100; i++) {
        x = false;
        y = false;
        z = 0;
        std::thread a(write_x_then_y);
        std::thread b(read_y_then_x);
        a.join();
        b.join();
        assert(z.load() != 0); // ��
    }
}
// �����y�Ĵ洢����Ϊʹ��memory_order_release,�����ö�y������ʹ
// ��memory_order_qcquire,ʵ���Ͼ��൱�ڶ�x�ϵĲ���ʩ����һ��˳��
// ���գ���y�ļ��آ۽��ῴ���ɴ洢д�µ�true�ڡ���Ϊ�洢ʹ��memory_
// order_release��������ʹ��memory_order_acquire���洢������ͬ������x��
// �洢�ٷ����ڶ�y�Ĵ洢��֮ǰ����Ϊ������ͬһ���߳����Ϊ��y�Ĵ洢���y��
// ����ͬ������x�Ĵ洢ͬ�������ڴ�y������֮ǰ�������ƶ���֮�����ڴ�x�������
// ֮ǰ�����ǣ���x�������Ȼ����true�����Ҷ��Ԣݲ��ᴥ���������y�����벻��
// whileѭ����Ͳ�һ��������������y��������ܶ���false������������£�
// �Դ�x��ȡ����ֵ��û��Ҫ���ˡ�Ϊ���ṩͬ������ȡ���ͷŲ���������ԡ����ͷŲ�
// ���洢��ֵ���뱻��ȡ�����������Ա������е�����һ����Ч������ڴ��Ĵ洢��۴�
// ��������һ����ɢ��������x�ķ��ʾ�û��˳����˾Ͳ���ȷ���ܴ��������ȡtrue��
// ��assert�ᱻ������
