#pragma once
#include<string>
#include<unordered_map>
#include<memory>
#include<functional>
using namespace std;
#include "../ioc/Any.hpp"
#include <NonCopyable.hpp>

// 11.2 Ioc��������
// �����õĶ��󹤳�
#include <map>
template <class T>
class IocContainer1 {
public:
	IocContainer1(void) {}
	~IocContainer1() {}
	// ע����Ҫ��������Ĺ��캯������Ҫ����һ��Ψһ�ı�ʶ���Ա��ں��洴������ʱ�������
	template <class Drived>
	void RegisterType(std::string strKey) {
		std::function<T*()> function = [] {return new Drived(); };
		RegisterType(strKey, function);
	}
	// ����Ψһ�ı�ʶȥ���Ҷ�Ӧ�Ĺ�����������������
	T* Resolve(std::string strKey) {
		if (m_creatorMap.find(strKey) == m_creatorMap.end()) {
			return nullptr;
		}
		std::function<T*()> function = m_creatorMap[strKey];
		return function();
	}
	// ��������ָ��
	std::shared_ptr<T> ResolveShared(std::string strKey) {
		T* ptr = Resolve(strKey);
		return std::shared_ptr<T>(ptr);
	}
private:
	void RegisterType(std::string strKey, std::function<T*()> creator) {
		if (m_creatorMap.find(strKey) != m_creatorMap.end()) {
			throw std::invalid_argument("this key has already exist!");
		}
		m_creatorMap.emplace(strKey, creator);
	}

	std::map<std::string, std::function<T*()>> m_creatorMap;
};

// 11.4 ͨ��Any�ͱհ����������
// ͨ��Any����������Ľ����󹤳�
class IocContainer2 {
public:
	IocContainer2(void) {}
	~IocContainer2() {}

	template<class T>
	void RegisterType(const std::string& strKey) {
		// ͨ���հ������������
		std::function<T*()> function = [] {return new T(); };
		RegisterType(strKey, function);
	}

	//// ������޸���������enable_if,���ø���
	//template<class T, typename Depend>
	//void RegisterType(const std::string& strKey) {
	//	// ͨ���հ������������
	//	// ����ͨ���հ�(lambda)���ʽ����˲�������Depend,�հ��б����˲�����������Ϣ
	//	std::function<T*()> function = [] {return new T(new Depend()); };
	//	RegisterType(strKey, function);
	//}
	template<class T, typename Depend>
	typename std::enable_if<std::is_base_of<T, Depend>::value>::type
	RegisterType(const std::string& strKey) {
		// ͨ���հ������������
		std::function<T*()> function = [] {return new Depend(); };
		RegisterType(strKey, function);
	}

	template<class T, typename Depend>
	typename std::enable_if<!std::is_base_of<T, Depend>::value>::type
		RegisterType(const std::string& strKey) {
		// ͨ���հ������������
		std::function<T*()> function = [] {return new T(new Depend()); };
		RegisterType(strKey, function);
	}

	template<class T, typename Depend>
	void RegisterType() {
		// ͨ���հ������������
		std::function<T*()> function = [] {return new T(new Depend()); };
		RegisterType("", function);
	}

	template<class T>
	T* Resolve(const std::string& strKey) {
		if (m_creatorMap.find(strKey) == m_creatorMap.end()) {
			return nullptr;
		}
		Any resolver = m_creatorMap[strKey];
		std::function<T*()> function = resolver.AnyCast<std::function<T*()>>();
		// ���ҵ���Anyת��Ϊfunction
		return function();
	}

	template<class T>
	std::shared_ptr<T> ResolveShared(const std::string& strKey) {
		T* t = Resolve<T>(strKey);
		return std::shared_ptr<T>(t);
	}

	template<class T>
	std::shared_ptr<T> ResolveShared() {
		T* t = Resolve<T>("");
		return std::shared_ptr<T>(t);
	}
private:
	void RegisterType(const std::string& strKey, Any constructor) {
		if (m_creatorMap.find(strKey) != m_creatorMap.end()) {
			throw::invalid_argument("this key has already exists!");
		}
		// ͨ��Any�����ͬ���͹�����
		m_creatorMap.emplace(strKey, constructor);
	}

	std::unordered_map<std::string, Any> m_creatorMap;
};

// 11.6 ������IoC����
// ͨ���ɱ����ģ��Ľ����󹤳�
class IocContainer3 : NonCopyable {
public:
	IocContainer3(void) {}
	~IocContainer3() {}
	
	template<class T, typename Depend, typename... Args>
	void RegisterType(const std::string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) { return new T(new Depend(args...)); }; // ͨ���հ������������
		RegisterType(strKey, function);
	}

	template<class T, typename... Args>
	T* Resolve(const std::string& strKey, Args... args) {
		if (m_creatorMap.find(strKey) == m_creatorMap.end()) {
			return nullptr;
		}
		Any resolver = m_creatorMap[strKey];
		std::function<T*(Args...)> function = resolver.AnyCast<std::function<T*(Args...)>>();
		return function(args...);
	}
	template<class T, typename... Args>
	std::shared_ptr<T> ResolveShared(const std::string& strKey, Args... args) {
		T* t = Resolve<T>(strKey, args...);
		return std::shared_ptr<T>(t);
	}
private:
	void RegisterType(const std::string& strKey, Any constructor) {
		if (m_creatorMap.find(strKey) != m_creatorMap.end()) {
			throw std::invalid_argument("this key has already exists!");
		}
		// ͨ��Anyɾ����ͬ���͵Ĺ�����
		m_creatorMap.emplace(strKey, constructor);
	}
	unordered_map<std::string, Any> m_creatorMap;
};

// ������IoCʵ��
class IocContainer : NonCopyable {
public:
	IocContainer(void) {}
	~IocContainer() {}

	template<class T, typename Depend, typename... Args>
	typename std::enable_if<std::is_base_of<T, Depend>::value>::type
	RegisterType(const std::string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) { return new Depend(args...); }; // ͨ���հ������������
		RegisterType(strKey, function);
	}

	template<class T, typename Depend, typename... Args>
	typename std::enable_if<!std::is_base_of<T, Depend>::value>::type
	RegisterType(const std::string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) { return new T(new Depend(args...)); }; // ͨ���հ������������
		RegisterType(strKey, function);
	}

	// ����ΪRegisterType�Ļ������޷��������RegisterType��������
	template<class T, typename... Args>
	void RegisterTypeSimple(const std::string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) { return new T(args...); }; // ͨ���հ������������
		RegisterType(strKey, function);
	}

	template<class T, typename... Args>
	T* Resolve(const std::string& strKey, Args... args) {
		if (m_creatorMap.find(strKey) == m_creatorMap.end()) {
			return nullptr;
		}
		Any resolver = m_creatorMap[strKey];
		std::function<T*(Args...)> function = resolver.AnyCast<std::function<T*(Args...)>>();
		return function(args...);
	}

	template<class T, typename... Args>
	std::shared_ptr<T> ResolveShared(const std::string& strKey, Args... args) {
		T* t = Resolve<T>(strKey, args...);
		return std::shared_ptr<T>(t);
	}
private:
	void RegisterType(const std::string& strKey, Any constructor) {
		if (m_creatorMap.find(strKey) != m_creatorMap.end()) {
			throw std::invalid_argument("this key has already exists!");
		}
		// ͨ��Anyɾ����ͬ���͵Ĺ�����
		m_creatorMap.emplace(strKey, constructor);
	}
	unordered_map<std::string, Any> m_creatorMap;
};
