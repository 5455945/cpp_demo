#include <functional>
#include <type_traits>
template<typename Ret = void>
struct CommCommand
{
private:
	std::function < Ret()> m_f;

public:
	//���ܿɵ��ö���ĺ�����װ��
	template< class F, class... Args, class = typename std::enable_if<!std::is_member_function_pointer<F>::value>::type>
	void Wrap(F && f, Args && ... args)
	{
		m_f = [&]{return f(args...); };
	}

	//���ܳ�����Ա�����ĺ�����װ��
	template<class R, class C, class... DArgs, class P, class... Args>
	void Wrap(R(C::*f)(DArgs...) const, P && p, Args && ... args)
	{
		m_f = [&, f]{return (*p.*f)(args...); };
	}

	//���ܷǳ�����Ա�����ĺ�����װ�� 
	template<class R, class C, class... DArgs, class P, class... Args>
	void Wrap(R(C::*f)(DArgs...), P && p, Args && ... args)
	{
		m_f = [&, f]{return (*p.*f)(args...); };
	}

	Ret Excecute()
	{
		return m_f();
	}
};
