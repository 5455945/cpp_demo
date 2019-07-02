#include "Concurrency05.h" 
#include <atomic>
#include <thread>
#include <cassert>
// 5 ��ȡ-�ͷ�˳��
// ��ȡ�ͷ�˳������ɢ˳��Ľ�����������Ȼû���ܵ�˳�򣬵���ȷ������һЩͬ����
// ������ģ���£�ԭ�������ǻ�ȡ(aquire)����(memory_order_acquire)��ԭ�Ӵ洢
// ���ͷ�(release)����(memory_order_release)��ԭ�ӵĶ�-�޸�-д����(���磺
// fetch_add()/exehange())�ǻ�ȡ���ͷŻ����߼汸(memory_order_qcq_rel)��
// ͬ���ڽ����ͷŵ��̺߳ͻ�ȡ���߳�֮���Ƕ�ż�ġ��ͷŲ������ȡд��ֵ�Ļ�ȡ����ͬ����
// ����ζ�Ų�ͬ���߳���Ȼ���Կ�����ͬ�����򣬵���Щ˳�����յ����Ƶġ�
namespace {
    // ��ȡ-�ͷŲ�����ζ����������
    std::atomic<bool> x, y;
    std::atomic<int> z;
    void write_x()
    {
        x.store(true, std::memory_order_release);
    }
    void write_y()
    {
        y.store(true, std::memory_order_release);
    }
    void read_x_then_y()
    {
        while (!x.load(std::memory_order_acquire));
        if (y.load(std::memory_order_acquire)) // ��
            ++z;
    }
    void read_y_then_x()
    {
        while (!y.load(std::memory_order_acquire));
        if (x.load(std::memory_order_acquire)) // ��
            ++z;
    }
}
void Concurrency05_07() {
    for (int i = 0; i < 100; i++) {
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
}
// ��������ж��Ԣۿ��Դ�������Ϊ��x������ںͶ�y������ٶ���ȡfalse�ǿ��ܵġ�
// x��y�ɲ�ͬ���߳�д�룬����ÿ������´��ͷŵ���ȡ��˳���������һ���߳��е�
// ������û��Ӱ��ġ�
// ������Ϊ��ÿ���߳��ڲ�x/y��û��������ϵ(������cpuָ��������ŵ������)
