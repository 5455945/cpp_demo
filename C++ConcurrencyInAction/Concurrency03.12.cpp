#include "Concurrency03.h"
#include <mutex>
namespace {
    // 使用std::call_once的线程安全的类成员延迟初始化
    struct connection_info {};
    struct data_packet {};
    struct connection_handle
    {
        void send_data(data_packet const&)
        {}
        data_packet receive_data()
        {
            return data_packet();
        }
    };
    struct remote_connection_manager
    {
        connection_handle open(connection_info const&)
        {
            return connection_handle();
        }
    } connection_manager;

    class X
    {
    private:
        connection_info connection_details;
        connection_handle connection;
        std::once_flag connection_init_flag;
        void open_connection()
        {
            connection = connection_manager.open(connection_details);
        }
    public:
        X(connection_info const& connection_details_) :
            connection_details(connection_details_)
        {}
        void send_data(data_packet const& data)
        {
            // 注意这里的&X::open_connection成员函数和this的绑定
            std::call_once(connection_init_flag, &X::open_connection, this);
            connection.send_data(data);
        }
        data_packet receive_data()
        {
            std::call_once(connection_init_flag, &X::open_connection, this);
            return connection.receive_data();
        }
    };
}
void Concurrency03_12() {
    data_packet dp;
    connection_info ci;
    X x(ci);
    x.send_data(dp);
    x.receive_data();
}
