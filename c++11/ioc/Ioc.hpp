#pragma once
#include<string>
#include<unordered_map>
#include<memory>
#include<functional>
using namespace std;
#include "../ioc/Any.hpp"
#include <NonCopyable.hpp>

// 11.2 Ioc创建对象
// 可配置的对象工厂
#include <map>
template <class T>
class IocContainer1 {
public:
	IocContainer1(void) {}
	~IocContainer1() {}
	// 注册需要创建对象的构造函数，需要传入一个唯一的标识，以便在后面创建对象时方便查找
	template <class Drived>
	void RegisterType(std::string strKey) {
		std::function<T*()> function = [] {return new Drived(); };
		RegisterType(strKey, function);
	}
	// 根据唯一的标识去查找对应的构造器，并创建对象
	T* Resolve(std::string strKey) {
		if (m_creatorMap.find(strKey) == m_creatorMap.end()) {
			return nullptr;
		}
		std::function<T*()> function = m_creatorMap[strKey];
		return function();
	}
	// 创建智能指针
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

// 11.4 通过Any和闭包来察除类型
// 通过Any察除类型来改进对象工厂
class IocContainer2 {
public:
	IocContainer2(void) {}
	~IocContainer2() {}

	template<class T>
	void RegisterType(const std::string& strKey) {
		// 通过闭包察除参数类型
		std::function<T*()> function = [] {return new T(); };
		RegisterType(strKey, function);
	}

	//// 把这个修改下面两个enable_if,适用更广
	//template<class T, typename Depend>
	//void RegisterType(const std::string& strKey) {
	//	// 通过闭包察除参数类型
	//	// 这里通过闭包(lambda)表达式察除了参数类型Depend,闭包中保存了参数的类型信息
	//	std::function<T*()> function = [] {return new T(new Depend()); };
	//	RegisterType(strKey, function);
	//}
	template<class T, typename Depend>
	typename std::enable_if<std::is_base_of<T, Depend>::value>::type
	RegisterType(const std::string& strKey) {
		// 通过闭包察除参数类型
		std::function<T*()> function = [] {return new Depend(); };
		RegisterType(strKey, function);
	}

	template<class T, typename Depend>
	typename std::enable_if<!std::is_base_of<T, Depend>::value>::type
		RegisterType(const std::string& strKey) {
		// 通过闭包察除参数类型
		std::function<T*()> function = [] {return new T(new Depend()); };
		RegisterType(strKey, function);
	}

	template<class T, typename Depend>
	void RegisterType() {
		// 通过闭包察除参数类型
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
		// 查找到的Any转换为function
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
		// 通过Any察除不同类型构造器
		m_creatorMap.emplace(strKey, constructor);
	}

	std::unordered_map<std::string, Any> m_creatorMap;
};

// 11.6 完整的IoC容器
// 通过可变参数模板改进对象工厂
class IocContainer3 : NonCopyable {
public:
	IocContainer3(void) {}
	~IocContainer3() {}
	
	template<class T, typename Depend, typename... Args>
	void RegisterType(const std::string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) { return new T(new Depend(args...)); }; // 通过闭包察除参数类型
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
		// 通过Any删除不同类型的构造器
		m_creatorMap.emplace(strKey, constructor);
	}
	unordered_map<std::string, Any> m_creatorMap;
};

// 完整的IoC实现
class IocContainer : NonCopyable {
public:
	IocContainer(void) {}
	~IocContainer() {}

	template<class T, typename Depend, typename... Args>
	typename std::enable_if<std::is_base_of<T, Depend>::value>::type
	RegisterType(const std::string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) { return new Depend(args...); }; // 通过闭包察除参数类型
		RegisterType(strKey, function);
	}

	template<class T, typename Depend, typename... Args>
	typename std::enable_if<!std::is_base_of<T, Depend>::value>::type
	RegisterType(const std::string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) { return new T(new Depend(args...)); }; // 通过闭包察除参数类型
		RegisterType(strKey, function);
	}

	// 名称为RegisterType的话，将无法和上面的RegisterType函数区分
	template<class T, typename... Args>
	void RegisterTypeSimple(const std::string& strKey) {
		std::function<T*(Args...)> function = [](Args... args) { return new T(args...); }; // 通过闭包察除参数类型
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
		// 通过Any删除不同类型的构造器
		m_creatorMap.emplace(strKey, constructor);
	}
	unordered_map<std::string, Any> m_creatorMap;
};
