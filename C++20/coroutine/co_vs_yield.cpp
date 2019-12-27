// https://www.cnblogs.com/heishanlaoy/p/11760368.html
#include "co_vs_yield.h"
#include <iostream>
#include <experimental/coroutine>
using namespace std;

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

    int current_value() {
        return handle.promise().value;
    }

    bool move_next()
    {
        handle.resume();
        return !handle.done();
    }

    struct promise_type
    {
        promise_type() { cout << "@ promise_type created\n"; }
        ~promise_type() { cout << "@ promise_type died\n"; }

        auto get_return_object() //get return object
        {
            cout << "@ get_return_object called\n";
            return test{ handle_type::from_promise(*this) };// pass handle to create "return object"
        }

        auto initial_suspend() // called before run coroutine body
        {
            cout << "@ initial_suspend is called\n";
            return std::experimental::suspend_never{}; // dont suspend it
            //return std::experimental::suspend_always{};
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

        void unhandled_exception() // exception handler
        {
            std::exit(1);
        }

        // data
        int value;
    };

    // member variables
    handle_type handle;
};
test yield_coroutine(int count)
{
    std::cout << "start yield_coroutine\n";
    for (int i = 0; i < count; i++)
        co_yield i * 2;
}

void co_vs_yield()
{
    auto a = yield_coroutine(4);
    cout << "created a corutine, try to get a value\n";
    do
    {
        cout << "get value " << a.current_value() << endl;
    } while (a.move_next());
}
