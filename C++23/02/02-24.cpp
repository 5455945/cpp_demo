#include "02-24.h"

// 24�����Զ�ʮ�ģ�Literal suffixes for (signed) size_t��P0330R8��
// �������Ϊstd::size_t���ͼ����˺�׺uz��Ϊsigned std::size_t���ͼ����˺�׺z�� 
// ������Ե���������������ʹ��std::size_t����ʱ�����Ը���ȷ��ָ���������͡� ������һ�����ӣ�

#include <vector>

void test02_24_01() {
    std::vector<int> v{ 0, 1, 2, 3 };

    // ���� auto i = 0u, s = v.size, �� vs2022 �б����´���
    // C3538	���������б��У���auto������ʼ���Ƶ�Ϊͬһ����
    // E1594	���ڴ�ʵ�塰auto�������� "size_t"����֮ǰĬʾΪ "unsigned int"
    //for (auto i = 0u, s = v.size(); i < s; ++i) {
    //    /* use both i and v[i] */
    //}
}

// ��δ�����32λƽ̨�Ͽ��Ա���ͨ����������64λƽ̨�ϻ���ִ���
// <source>(5) : error C3538 : in a declarator - list 'auto' must always deduce to the same type
// <source>(5) : note : could be 'unsigned int'
// < source > (5) : note : or 'unsigned __int64'

// �е�˵����32λƽ̨�ϣ�std::vector::size_type���Ƶ�Ϊunsigned int����v.size()���ص�����Ϊsize_t��
// ��size_t��32λ��Ϊunsigned int������64λ��Ϊunsigned long long�� ��ˣ���������32λƽ̨�ϱ���˴���ʱ��
// i��v.size()����������ͬ�ģ�����unsigned int��

// ���ǣ���������64λƽ̨�ϱ���ʱ��i��v.size()�����Ͳ�ͬ����ͻᵼ�´��� ͨ��Ϊstd::size_t���Ӻ�׺uz��
// ���ǿ��Ա�֤���κ�ƽ̨�ϣ�std::size_t���Ͷ�����ȷ��ָ��Ϊunsigned�������ͣ��Ӷ������������⡣
// ͬ����ͨ��Ϊsigned std::size_t���Ӻ�׺z�����ǿ��Ա�֤���κ�ƽ̨�ϣ�
// signed std::size_t���Ͷ�����ȷ��ָ��Ϊ�������������͡�

// ĿǰGCC 11��Clang 13�Ѿ�֧����Ϊstd::size_t���Ӻ�׺uz��Ϊsigned std::size_t���Ӻ�׺z�����ԡ�
// ��ʹ�����ǿ��Ը�����ȷ��ָ��std::size_t���ͺ�signed std::size_t���ͣ�
// �Ӷ������ڲ�ͬƽ̨�ϳ������Ͳ�ƥ������⡣

void test02_24_02() {
    std::vector<int> v{ 0, 1, 2, 3 };
    //for (auto i = 0uz, s = v.size(); i < s; ++i) {
    //for (auto i = 0zu, s = v.size(); i < s; ++i) {
    //for (auto i = 0sz, s = v.size(); i < s; ++i) {
    for (auto i = 0ull, s = v.size(); i < s; ++i) {
        /* use both i and v[i] */
    }
}


void test02_24() {
    test02_24_01();
    test02_24_02();
}
