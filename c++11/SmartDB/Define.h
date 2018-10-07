#pragma once
#include <type_traits>
#include  <cstdint>
#include <Variant.hpp>

const string BEGIN = "BEGIN";
const string COMMIT = "COMMIT";
const string ROLLBACK = "ROLLBACK";

//���������ͣ�statement֧�ְ󶨶�����
struct blob
{
	const char *pBuf;
	int size;
};

/**
*���Ͷ��壬���ݿ����Ҫ�õ������ͣ�����С��ֶκ�ֵ������
*/
typedef Variant<double, int, uint32_t, sqlite3_int64, char*, const char*, blob, string, nullptr_t> SqliteValue;	//���ݱ��е�ֵ����


