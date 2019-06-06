#include "Concurrency08.h" 
#include <thread>
#include <atomic>
#include <iostream>
namespace {
    // 从任务线程中分离GUI线程
    std::thread task_thread;
    std::atomic<bool> task_cancelled(false);
    enum /*class */task_type {
        task_start,
        task_stop,
        task_complete,
        task_quit
    };
    struct event_data {
        task_type type;
    };
    void process(event_data const& event);
    event_data get_event() {
        event_data data;
        data.type = task_start;
        return data;
    }
    void post_gui_event(std::function<bool()> f) {
        std::cout << __FUNCTION__ << std::endl;
        f();
    }
    void perform_cleanup() {
        std::cout << __FUNCTION__ << std::endl;
    }
    void display_results() {
        std::cout << __FUNCTION__ << std::endl;
    }
    void do_next_operation() {
        std::cout << __FUNCTION__ << std::endl;
    }
    bool task_complete1() {
        return false;
    }

    void gui_thread()
    {
        while (true)
        {
            event_data event = get_event();
            if (event.type == task_quit)
                break;
            process(event);
        }
    }

    void task()
    {
        while (!task_complete1() && !task_cancelled)
        {
            do_next_operation();
        }
        if (task_cancelled)
        {
            perform_cleanup();
        }
        else
        {
            post_gui_event(task_complete1);
        }
    }

    void process(event_data const& event)
    {
        switch (event.type)
        {
        case task_start:
            task_cancelled = false;
            task_thread = std::thread(task);
            break;
        case task_stop:
            task_cancelled = true;
            if (task_thread.joinable()) {
                task_thread.join();
            }
            break;
        case task_complete:
            if (task_thread.joinable()) {
                task_cancelled = true;
                task_thread.join();
            }
            display_results();
            break;
        default:
            //...
            break;
        }
    }
}

void Concurrency08_06() {
    event_data data;
    data.type = task_start;
    process(data);
    data.type = task_stop;
    process(data);
    data.type = task_complete;
    process(data);
}