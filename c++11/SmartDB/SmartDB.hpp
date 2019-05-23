#pragma once
/*
*�ļ����ƣ�SweetDB.hpp
*�ļ���ʶ��
*ժҪ�����ݿ�����࣬�ṩ���ͳһ�Ĳ����ӿ�

*��ǰ�汾��1.0.0
*���ߣ�����
*������ڣ�2013��8��1��
*/

#include <sqlite3.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cctype>
#include <functional>
#include <unordered_map>
#include <memory>
#include <type_traits>
using namespace std;

#include "Define.h"
#include "detail\BindParams.hpp"
#include "detail\Json.hpp"
#include "detail\Tuple.hpp"
#include <NonCopyable.hpp>

class SmartDB : NonCopyable
{
public:
	SmartDB() : m_jsonHelper(m_buf, m_code){}

	/**
	* �������ݿ�
	* ������ݿⲻ���ڣ����ݿ⽫����������, �������ʧ��������ʧ�ܱ�־
	* @param[in] fileName�����ݿ��ļ���λ�á�
	*/
	explicit SmartDB(const string& fileName) : m_dbHandle(nullptr), m_statement(nullptr), m_isConned(false), m_code(0), m_jsonHelper(m_buf, m_code)
	{
		Open(fileName);
	}

	/**
	* �ͷ���Դ���ر����ݿ�
	*/
	~SmartDB()
	{
		Close();
	}

	/**
	* �����ݿ�
	*/
	void Open(const string& fileName)
	{
		m_code = sqlite3_open(fileName.data(), &m_dbHandle);
		if (SQLITE_OK == m_code)
		{
			m_isConned = true;
		}
	}

	/**
	* �ͷ���Դ���ر����ݿ�
	*/
	bool Close()
	{
		if (m_dbHandle == nullptr)
			return true;

		sqlite3_finalize(m_statement);
		m_code = CloseDBHandle();
		bool ret = (SQLITE_OK == m_code);
		m_statement = nullptr;
		m_dbHandle = nullptr;
		return ret;
	}

	/**
	* �Ƿ����������ݿ�
	*/
	bool IsConned() const
	{
		return m_isConned;
	}

	/**
	* ����ռλ����ִ��sql���������ؽ��, ��insert,update,delete��
	* @param[in] query: sql���, ����ռλ��
	* @return bool, �ɹ�����true�����򷵻�false
	*/
	bool Excecute(const string& sqlStr)
	{
		m_code = sqlite3_exec(m_dbHandle, sqlStr.data(), nullptr, nullptr, nullptr);
		return SQLITE_OK == m_code;
	}

	/**
	* ��ռλ����ִ��sql���������ؽ��, ��insert,update,delete��
	* @param[in] query: sql���, ���ܴ�ռλ��"?"
	* @param[in] args: �����б��������ռλ��
	* @return bool, �ɹ�����true�����򷵻�false
	*/
	template <typename... Args>
	bool Excecute(const string& sqlStr, Args && ... args)
	{
		if (!Prepare(sqlStr))
		{
			return false;
		}

		return ExcecuteArgs(std::forward<Args>(args)...);
	}

	/**
	* ��������֮ǰ׼��sql�ӿڣ������ExcecuteBulkһ����ã�׼������������sql�����ܴ�ռλ��
	* @param[in] query: sql���, ��ռλ��"?"
	* @return bool, �ɹ�����true�����򷵻�false
	*/
	bool Prepare(const string& sqlStr)
	{
		m_code = sqlite3_prepare_v2(m_dbHandle, sqlStr.data(), -1, &m_statement, nullptr);
		if (m_code != SQLITE_OK)
		{
			return false;
		}

		return true;
	}

	/**
	* ���������ӿڣ������ȵ���Prepare�ӿ�
	* @param[in] args: �����б�
	* @return bool, �ɹ�����true�����򷵻�false
	*/
	template <typename... Args>
	bool ExcecuteArgs(Args && ... args)
	{
		if (SQLITE_OK != detail::BindParams(m_statement, 1, std::forward<Args>(args)...))
		{
			return false;
		}

		m_code = sqlite3_step(m_statement);

		sqlite3_reset(m_statement);
		return m_code == SQLITE_DONE;
	}

	template<typename Tuple>
	bool ExcecuteTuple(const string& sqlStr, Tuple&& t)
	{
		if (!Prepare(sqlStr))
		{
			return false;
		}

		m_code = detail::ExcecuteTuple(m_statement, detail::MakeIndexes<std::tuple_size<Tuple>::value>::type(), std::forward<Tuple>(t));
		return m_code == SQLITE_DONE;
	}

	bool ExcecuteJson(const string& sqlStr, const char* json)
	{
		rapidjson::Document doc;
		doc.Parse<0>(json);
		if (doc.HasParseError())
		{
			cout << doc.GetParseError() << endl;
			return false;
		}

		if (!Prepare(sqlStr))
		{
			return false;
		}

		return JsonTransaction(doc);
	}

	/**
	* ִ��sql�����غ���ִ�е�һ��ֵ, ִ�м򵥵Ļ�ۺ�������select count(*), select max(*)��
	* ���ؽ�������ж������ͣ�����Value���ͣ�������ͨ��get����ȥȡ
	* @param[in] query: sql���, ���ܴ�ռλ��"?"
	* @param[in] args: �����б��������ռλ��
	* @return int: ���ؽ��ֵ��ʧ���򷵻�-1
	*/
	template < typename R = sqlite_int64, typename... Args>
	R ExecuteScalar(const string& sqlStr, Args&&... args)
	{
		if (!Prepare(sqlStr))
			return GetErrorVal<R>();

		if (SQLITE_OK != detail::BindParams(m_statement, 1, std::forward<Args>(args)...))
		{
			return false;
		}

		m_code = sqlite3_step(m_statement);

		if (m_code != SQLITE_ROW)
			return GetErrorVal<R>();

		SqliteValue val = GetValue(m_statement, 0);
		R result = val.Get<R>();// get<R>(val);
		sqlite3_reset(m_statement);
		return result;
	}

	template <typename... Args>
	std::shared_ptr<rapidjson::Document> Query(const string& query, Args&&... args)
	{
		if (!PrepareStatement(query, std::forward<Args>(args)...))
			nullptr;

		auto doc = std::make_shared<rapidjson::Document>();

		m_buf.Clear();
		m_jsonHelper.BuildJsonObject(m_statement);

		doc->Parse<0>(m_buf.GetString());

		return doc;
	}

	bool Begin()
	{
		return Excecute(BEGIN);
	}

	bool RollBack()
	{
		return Excecute(ROLLBACK);
	}

	bool Commit()
	{
		return Excecute(COMMIT);
	}

	int GetLastErrorCode()
	{
		return m_code;
	}

private:
	int CloseDBHandle()
	{
		int code = sqlite3_close(m_dbHandle);
		while (code == SQLITE_BUSY)
		{
			// set rc to something that will exit the while loop 
			code = SQLITE_OK;
			sqlite3_stmt * stmt = sqlite3_next_stmt(m_dbHandle, NULL);

			if (stmt == nullptr)
				break;

			code = sqlite3_finalize(stmt);
			if (code == SQLITE_OK)
			{
				code = sqlite3_close(m_dbHandle);
			}
		}

		return code;
	}

	template <typename... Args>
	bool PrepareStatement(const string& sqlStr, Args&&... args)
	{
		if (!Prepare(sqlStr))
		{
			return false;
		}

		if (SQLITE_OK != detail::BindParams(m_statement, 1, std::forward<Args>(args)...))
		{
			return false;
		}

		return true;
	}

	//ͨ��json��д�����ݿ���
	bool JsonTransaction(const rapidjson::Document& doc)
	{
		bool ret = true;
		Begin();
		if (doc.IsArray()) {
			for (auto& it : doc.GetArray()) {
				if (!m_jsonHelper.ExcecuteJson(m_statement, it))
				{
					ret = false;
					break;
				}
			}
		}
		else {
			RollBack();
			ret = false;
			throw std::logic_error("doc is not array!");
		}

		if (!(m_code == SQLITE_DONE || m_code == SQLITE_OK)) {
			ret = false;
		}
		Commit();
		return ret;
	}

private:

	/** ȡ�е�ֵ **/
	SqliteValue GetValue(sqlite3_stmt *stmt, const int& index)
	{
		int type = sqlite3_column_type(stmt, index);
		auto it = m_valmap.find(type);
		if (it == m_valmap.end())
			throw std::invalid_argument("can not find this type");

		return it->second(stmt, index);
	}

	template<typename T>
	typename std::enable_if <std::is_arithmetic<T>::value, T>::type
		GetErrorVal()
	{
			return T(-9999);
		}

	template<typename T>
	typename std::enable_if <!std::is_arithmetic<T>::value, T>::type
		GetErrorVal()
	{
			return "";
		}

private:
	sqlite3* m_dbHandle;
	sqlite3_stmt* m_statement;
	bool m_isConned;
	int m_code;//��¼���һ�εĴ�����

	//JsonBuilder m_jsonBuilder;  //дjson��
	detail::JsonHelper m_jsonHelper;
	rapidjson::StringBuffer m_buf; //json�ַ�����buf

	static std::unordered_map<int, std::function <SqliteValue(sqlite3_stmt*, int)>> m_valmap;
	
};
std::unordered_map<int, std::function <SqliteValue(sqlite3_stmt*, int)>> SmartDB::m_valmap =
{
	{ std::make_pair(SQLITE_INTEGER, [](sqlite3_stmt *stmt, int index){return sqlite3_column_int64(stmt, index); }) },
	{ std::make_pair(SQLITE_FLOAT, [](sqlite3_stmt *stmt, int index){return sqlite3_column_double(stmt, index); }) },
	{ std::make_pair(SQLITE_BLOB, [](sqlite3_stmt *stmt, int index){return string((const char*) sqlite3_column_blob(stmt, index));/* SmartDB::GetBlobVal(stmt, index);*/ }) },
	{ std::make_pair(SQLITE_TEXT, [](sqlite3_stmt *stmt, int index){return string((const char*) sqlite3_column_text(stmt, index)); }) },
	{ std::make_pair(SQLITE_NULL, [](sqlite3_stmt *stmt, int index){return nullptr; }) }
};


