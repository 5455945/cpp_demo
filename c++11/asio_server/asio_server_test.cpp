#include "../asio_server/asio_server.hpp"

void TestServer()
{
    io_service ios;
    //boost::asio::io_service::work work(ios);
    //std::thread thd([&ios]{ios.run(); }); 

    Server server(ios, 9900);
    server.Accept();
    ios.run();

    //thd.join();
}

int main() {
    TestServer();
    return 0;
}
