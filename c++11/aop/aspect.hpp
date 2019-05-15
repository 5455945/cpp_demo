#pragma once
#include "../pattern/NonCopyable.hpp"
#include <iostream>
using namespace std;

#define  HAS_MEMBER(member) \
template<typename T,typename...Args> struct has_member_##member\
{\
private:\
    template<typename U> static auto Check(int)->decltype(declval<U>().member(declval<Args>()...),true_type());\
    template<typename U> static false_type Check(...);\
public:\
    enum{value=is_same<decltype(Check<T>(0)),true_type>::value};\
};

HAS_MEMBER(Foo)
HAS_MEMBER(Before)
HAS_MEMBER(After)

template<typename Func, typename...Args>
struct Aspect :NonCopyable
{
    Aspect(Func&& f) :m_func(forward<Func>(f))
    {
    }
    template<typename T>
    typename enable_if<has_member_Before<T, Args...>::value && has_member_After<T, Args...>::value > ::type Invoke(Args&&...args, T&& aspect)
    {
        aspect.Before(forward<Args>(args)...);  //核心逻辑之前的切面逻辑
        m_func(forward<Args>(args)...);	        //核心逻辑
        aspect.After(forward<Args>(args)...);    //核心逻辑之后的切面逻辑
    }

    template<typename T>
    typename enable_if<has_member_Before<T, Args...>::value && !has_member_After<T, Args...>::value>::type Invoke(Args&&...args, T&& aspect)
    {
        aspect.Before(forward<Args>(args)...);  //核心逻辑之前的切面逻辑
        m_func(forward<Args>(args)...);         //核心逻辑
    }

    template<typename T>
    typename enable_if<!has_member_Before<T, Args...>::value && has_member_After<T, Args...>::value>::type Invoke(Args&&... args, T&& aspect)
    {
        m_func(forward<Args>(args)...);        //核心逻辑
        aspect.After(forward<Args>(args)...);  //核心逻辑之后的切面逻辑
    }

    template<typename Head, typename...Tail>
    void Invoke(Args&&... args, Head&&headAspect, Tail&&...tailAspect)
    {
        headAspect.Before(forward<Args>(args)...);
        Invoke(forward<Args>(args)..., forward<Tail>(tailAspect)...);
        headAspect.After(forward<Args>(args)...);
    }
private:
    Func m_func;
};

template<typename T> using identity_t = T;

// AOP的辅助函数，简化调用
template<typename... AP, typename... Args, typename Func>
void Invoke(Func&& f, Args&&... args)
{
    Aspect<Func, Args...>asp(forward<Func>(f));
    asp.Invoke(forward<Args>(args)..., identity_t<AP>()...);
}