#include "02-17.h"

// 17������ʮ�ߣ�static operator()��P1169R4��
// ע��һ�£�maxsize�����Ŀ��ܴ�С����op���ز���ʵ�ʴ�С������߼���������һ��erase()������
// ����ɾ������Ĵ�С�����������GCC 12��Clang 14��MSVC v19.31�Ѿ�ʵ�֡�

// ��������P2251����������std::span��std::string_view��Լ������C++23��ʼ�����Ǳ�������TriviallyCopyable Concept��
// ������������֧�ָ����ԡ��������P0448����������һ���µ�ͷ�ļ�����Ҷ�֪����stringstream���ڱ��㷺ʹ�ã�
// ���Խ����ݴ洢��string��vector���У�����Щ��������������ʱ�ᷢ����Ų�ѡ�����Ϊ�����ǲ��������������أ�
// �ṩ��һ��ѡ�������ָ���̶���С��buffer�����������·����ڴ棬��ҪС�����ݳ���buffer��С��
// ��ʱ�ڴ������Ȩ�ڳ���Ա��ߡ�һ��С���ӣ�

void test02_17() {

}