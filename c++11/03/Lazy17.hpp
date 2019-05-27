#pragma once
#include <optional>
template<typename T>
struct Lazy17 {
    Lazy17() {}

    //template <typename Func>
    //Lazy17(Func& f) {
    //    m_func = [&f]{
    //        return f();
    //    };
    //}

    // ������Ҫ�ӳ�ִ�еĺ���
    template <typename Func, typename... Args>
    Lazy17(Func& f, Args&& ... args) {
        m_func = [&f, &args...]{
            return f(args...);
        };
    }
    // �ӳ�ִ�У�������ŵ�Optional�л����������´β������¼������ֱ�ӷ��ؽ��
    T& Value() {
        if (!m_value.has_value()) {
            m_value = m_func();
        }
        return *m_value;
    }

    bool IsValueCreated() const {
        return m_value.has_value();
    }

private:
    std::function<T()> m_func;
    std::optional<T> m_value;
};

//// C++11 д��
//template<class Func, typename... Args>
//Lazy17<typename std::result_of<Func(Args...)>::type>
//lazy17(Func&& fun, Args&& ... args) {
//    return Lazy17<typename std::result_of<Func(Args...)>::type>(std::forward<Func>(fun), std::forward<Args>(args)...);
//}

//// ʹ�������Ƶ�auto
//template<class Func, typename... Args>
//auto lazy17(Func&& fun, Args&& ... args) {
//    return Lazy17<typename std::result_of<Func(Args...)>::type>(std::forward<Func>(fun), std::forward<Args>(args)...);
//}

//// C++17д��,ʹ��auto��invoke_result
//template<class Func, typename... Args>
//auto lazy17(Func&& fun, Args&& ... args) {
//    return Lazy17<typename std::invoke_result<Func, Args...>::type>(std::forward<Func>(fun), std::forward<Args>(args)...);
//}

// C++17д����ʹ��auto��invoke_result_t
template<class Func, typename... Args>
auto lazy17(Func&& fun, Args&& ... args) {
    return Lazy17<typename std::invoke_result_t<Func, Args...>>(std::forward<Func>(fun), std::forward<Args>(args)...);
}
