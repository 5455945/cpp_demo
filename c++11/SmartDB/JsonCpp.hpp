#pragma once
/*
*�ļ����ƣ�JsonCpp.hpp
*�ļ���ʶ��
*ժҪ��json���л��࣬���ṹ�����л����ַ�����
 �ṹ������ṩ�ֶ������ֶ�ֵ��Ϣ��
 �ṹ���в�����ָ�����ͣ�������char�������飻
 �ṹ���п���Ƕ�׽ṹ�壬����Ƕ�׵Ľṹ���в�����ָ��

*��ǰ�汾��1.0.0
*���ߣ�����
*������ڣ�2013��10��31��
*/
#include <string>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
using namespace rapidjson;

class JsonCpp
{
	typedef Writer<StringBuffer> JsonWriter;
public:

	JsonCpp() : m_writer(m_buf)
	{
	}

	~JsonCpp()
	{
	}

	/**
	* ���л��ṹ������֮ǰ����ô˽ӿڣ�Ȼ����ѭ��ȥSerialize
	*/
	void StartArray()
	{
		m_writer.StartArray();
	}

	/**
	* ���л��ṹ������֮������ô˽ӿڣ�ѭ��Serialize���֮�����
	*/
	void EndArray()
	{
		m_writer.EndArray();
	}

	void StartObject()
	{
		m_writer.StartObject();
	}

	void EndObject()
	{
		m_writer.EndObject();
	}

	template<typename T>
	void WriteJson(string& key, T&& value)
	{
		m_writer.String(key.c_str());
		WriteValue(std::forward<T>(value));
	}

	template<typename T>
	void WriteJson(const char* key, T&& value)
	{
		m_writer.String(key);
		WriteValue(std::forward<T>(value));	
	}
	

	///**
	//* ���ض������л����json�ַ���
	//*/
	const char* GetString() const
	{
		return m_buf.GetString();
	}

private:
	template<typename V>
	typename std::enable_if<std::is_same<V, int>::value>::type WriteValue(V value)
	{
		m_writer.Int(value);
	}

	template<typename V>
	typename std::enable_if<std::is_same<V, unsigned int>::value>::type WriteValue(V value)
	{
		m_writer.Uint(value);
	}

    template<typename V>
    typename std::enable_if<std::is_same<V, size_t>::value>::type WriteValue(V value)
    {
        m_writer.Uint64(value);
    }

	template<typename V>
	typename std::enable_if<std::is_same<V, int64_t>::value>::type WriteValue(V value)
	{
		m_writer.Int64(value);
	}

	template<typename V>
	typename std::enable_if<std::is_floating_point<V>::value>::type WriteValue(V value)
	{
		m_writer.Double(value);
	}

	template<typename V>
	typename std::enable_if<std::is_same<V, bool>::value>::type WriteValue(V value)
	{
		m_writer.Bool(value);
	}

	template<typename V>
	typename std::enable_if<std::is_pointer<V>::value>::type WriteValue(V value)
	{
		m_writer.String(value);
	}

	template<typename V>
	typename std::enable_if<std::is_array<V>::value>::type WriteValue(V value)
	{
		m_writer.String(value);
	}

	template<typename V>
	typename std::enable_if<std::is_same<V, std::nullptr_t>::value>::type WriteValue(V value)
	{
		m_writer.Null();
	}

private:
	StringBuffer m_buf; //json�ַ�����buf
	JsonWriter m_writer; //jsonд����

	Document m_doc;
};

