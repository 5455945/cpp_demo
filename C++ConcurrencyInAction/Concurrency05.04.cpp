#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
// �����Ǻ�cpu��صģ������������ڴ��еģ�cpu���ڴ�֮�仹��cpu�Ļ���(һ������/���������)
// ==================================================================================================
// ���������Ȳ�һ��ǡ����
// ����ǵ����ĵ�ģ�Ⲣ�����ڴ�˳��Ӧ�þ���˳��ģ�����Ӧ�ÿ��ǵ��Ƕ�˺Ͷ�cpu�����Ρ�
// �����ڴ�����data0��
// cpu�ĺ�c1���data0������m1;
// cpu�ĺ�c2��ȡdata0������m2;
// c1�޸���m1��ֵ��δд���ڴ�data0,
// c2�����m2��ֵ��д���ڴ�data0������m2��data0һ�£���m1��ͬ
// cpu�ĺ�c3��ȡdata0������m3;��m2һ�£���m1��ͬ��
// ==================================================================================================
// ��ͬcpu���ͬһ�ڴ������ʱ�����ܲ�ͬ�������޸ĵ�ʱ���Ƿ�ȷ�ϲ�ͬ������ڴ��ͬһ�����Ƿ�һ�¡�
// 5.3.3 ԭ�Ӳ������ڴ�˳��
// �������ڴ�˳��ѡ�����Ӧ����ԭ�������ϵĲ���:
// memory_order_relaxed
// memory_order_consume
// memory_order_acquire
// memory_order_release
// memory_order_acq_rel
// memory_order_seq_cst
// ������Ϊĳ���ض��Ĳ�������ָ����ԭ�������ϵ����в������ڴ�˳��Ԥѡ���:memory_order_seq_cst,�������ϸ��ѡ�
// �ڴ�˳���Ϊ����:
// ˳��һ��(sequentially consistent)˳��:memory_order_seq_cst
// ���-�ͷ�(acquire-release)˳��:memory_order_consume��memory_order_acquire��memory_order_release��memory_order_acq_rel
// ��ɢ(relaxed)˳��:memory_order_relaxed

// 1 ˳��һ��˳��
namespace {
    // ˳��һ������������˳��
    std::atomic<bool> x, y;
    std::atomic<int> z;
    void write_x()
    {
        x.store(true, std::memory_order_seq_cst); // ��
    }
    void write_y()
    {
        y.store(true, std::memory_order_seq_cst); // ��
    }
    void read_x_then_y()
    {
        while (!x.load(std::memory_order_seq_cst));
        if (y.load(std::memory_order_seq_cst)) // ��
            ++z;
    }
    void read_y_then_x()
    {
        while (!y.load(std::memory_order_seq_cst));
        if (x.load(std::memory_order_seq_cst)) // ��
            ++z;
    }
}
void Concurrency05_04() {
    x = false;
    y = false;
    z = 0;
    std::thread a(write_x);
    std::thread b(write_y);
    std::thread c(read_x_then_y);
    std::thread d(read_y_then_x);
    a.join();
    b.join();
    c.join();
    d.join();
    assert(z.load() != 0); // ��
}