#include "02-12.h"

#include <utility>  // std::move


// 12������ʮ����forward_like��P2445��
// ͬ����������"Deducing this"һ����Ҳʹ�������������˵���������ǻع�һ��������ӣ�

//auto callback = [m = get_message(), &scheduler](this auto&& self) -> bool {
//    return scheduler.submit(std::forward_like<decltype(self)>(m));
//    };

void test02_12_01() {
    //callback();            // retry(callback)
    //std::move(callback)(); // try-or-fail(rvalue)
}

// C++�е��м�����std::forward_like�����������Ը���ģ�������ֵ�����ת�������� 
// ���closure typeΪ��ֵ����ôm��ת��Ϊ��ֵ�����Ϊ��ֵ����ת��Ϊ��ֵ�� 
// ��˵��Clang 16��MSVC v19.34��֧��������ԣ���Ŀǰ��û�з�����


void test02_12() {
    test02_12_01();
}
