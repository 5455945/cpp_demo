// https://www.cnblogs.com/heishanlaoy/p/11760368.html
#include "co_vs_await.h"
#include <iostream>
#include <experimental/coroutine>
using namespace std;

template<class T>
struct test {
    // inner types
    struct promise_type;
    using handle_type = std::experimental::coroutine_handle<promise_type>; //type alias

                                                                           // functions
    test(handle_type h) :handle(h) { cout << "# Created a Test object\n"; }
    test(const test& s) = delete;
    test& operator=(const test&) = delete;
    test(test&& s) :handle(s.handle) { s.handle = nullptr; }
    test& operator=(test&& s) { handle = s.handle; s.handle = nullptr; return *this; }
    ~test() { cout << "#Test gone\n"; if (handle) handle.destroy(); }

    T get()
    {
        cout << "# Got return value\n";
        if (!(this->handle.done()))
        {
            handle.resume();  //resume
            return handle.promise().value;
        }
    }

    struct promise_type
    {
        promise_type() { cout << "@ promise_type created\n"; }
        ~promise_type() { cout << "@ promise_type died\n"; }

        auto get_return_object() //get return object
        {
            cout << "@ get_return_object called\n";
            return test<T>{handle_type::from_promise(*this)};// pass handle to create "return object"
        }

        auto initial_suspend() // called before run coroutine body
        {
            cout << "@ initial_suspend is called\n";
            // return std::experimental::suspend_never{}; // dont suspend it
            return std::experimental::suspend_always{};
        }

        auto return_void() // called when just before final_suspend, conflict with return_value
        {
            cout << "@ return_void is called\n";
            return std::experimental::suspend_never{}; // dont suspend it
                                                       //return std::experimental::suspend_always{};
        }

        auto yield_value(int t) // called by co_yield()
        {
            std::cout << "yield_value called\n";
            value = t;
            return std::experimental::suspend_always{};
        }

        auto final_suspend() // called at the end of coroutine body
        {
            cout << "@ final_suspend is called\n";
            return std::experimental::suspend_always{};
        }

        void unhandled_exception() //exception handler
        {
            std::exit(1);
        }

        //T await_transform() {}

        // data
        T value;
    };

    // member variables
    handle_type handle;
};

struct AwaiableObj
{
    int a;
    AwaiableObj() :a(0) {}
    bool await_ready()
    {
        cout << "@@ await_ready called\n";
        return true;
    }

    auto await_suspend(std::experimental::coroutine_handle<> awaiting_handle)
    {
        cout << "@@ await_suspend called\n";
        // return ;
        // return true;
        return false;
        // return awaiting_handle;
    }

    auto await_resume()
    {
        cout << "@@ await_resume called\n";
        return a++;
    }
};

test<int> await_routine()
{
    auto a = AwaiableObj{};
    for (int i = 0; i < 5; i++)
    {
        auto v = co_await a;
        co_yield v;
    }
}

void co_vs_await()
{
    auto a = await_routine();
    auto b = a.get();
    cout << "value is " << b << endl;
    b = a.get();
    cout << "value is " << b << endl;
    b = a.get();
    cout << "value is " << b << endl;
    b = a.get();
    cout << "value is " << b << endl;
    b = a.get();
    cout << "value is " << b << endl;
}
