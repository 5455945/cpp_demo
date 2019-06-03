#include "Concurrency02.h"
#include <thread>
#include <string>

// 2.1.4 在后台运行线程
// 只能对joinable()返回true的线程运行join或者deteach
namespace {
    void open_document_and_display_gui(std::string const& filename)
    {}

    bool done_editing()
    {
        return true;
    }

    enum command_type {
        open_new_document
    };


    struct user_command
    {
        command_type type;

        user_command() :
            type(open_new_document)
        {}
    };

    user_command get_user_input()
    {
        return user_command();
    }

    std::string get_filename_from_user()
    {
        return "foo.doc";
    }

    void process_user_input(user_command const& cmd)
    {}

    void edit_document(std::string const& filename)
    {
        open_document_and_display_gui(filename);
        while (!done_editing())
        {
            user_command cmd = get_user_input();
            if (cmd.type == open_new_document)
            {
                std::string const new_name = get_filename_from_user();
                std::thread t(edit_document, new_name);
                t.detach();
            }
            else
            {
                process_user_input(cmd);
            }
        }
    }
}
void Concurrency02_04() {
    edit_document("bar.doc");
}
