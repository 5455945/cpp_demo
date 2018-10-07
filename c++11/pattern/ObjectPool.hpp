#include <string>
#include <functional>
#include <memory>
#include <map>
#include "NonCopyable.hpp"
using namespace std;

const int MaxObjectNum = 10;

template<typename T>
class ObjectPool : NonCopyable
{
	template<typename... Args>
	using Constructor = std::function<std::shared_ptr<T>(Args...)>;
public:
	//Ĭ�ϴ������ٸ�����
	template<typename... Args>
	void Init(size_t num, Args&&... args)
	{
		if (num<= 0 || num> MaxObjectNum)
			throw std::logic_error("object num out of range.");

		auto constructName = typeid(Constructor<Args...>).name(); //����������
		for (size_t i = 0; i <num; i++)
		{
			m_object_map.emplace(constructName, shared_ptr<T>(new T(std::forward<Args>(args)...), [this, constructName](T* p) //ɾ�����в�ֱ��ɾ�����󣬶��ǻ��յ�������У��Թ��´�ʹ��
			{
				m_object_map.emplace(std::move(constructName), std::shared_ptr<T>(p));
			}));
		}
	}

	//�Ӷ�����л�ȡһ������
	template<typename... Args>
	std::shared_ptr<T> Get()
	{
		string constructName = typeid(Constructor<Args...>).name();

		auto range = m_object_map.equal_range(constructName);
		for (auto it = range.first; it != range.second; ++it)
		{
			auto ptr = it->second;
			m_object_map.erase(it);
			return ptr;
		}

		return nullptr;
	}

private:
	multimap<string, std::shared_ptr<T>> m_object_map;
};
