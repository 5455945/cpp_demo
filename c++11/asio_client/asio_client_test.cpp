#include "../asio_client/asio_client.hpp"
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <iostream>
#include <string>

int main()
{
    io_service ios;
    boost::asio::io_service::work work(ios);
    boost::thread thd([&ios]{ios.run(); });

    Connector conn(ios, "127.0.0.1", 9900);
    conn.Start();

    std::string str;

    if (!conn.IsConnected())
    {
        //Pause();
        return -1;
    }
    
    const int len = 512;
    char line[len] = "";
    
    while (std::cin >> str)
    {
        char header [HEAD_LEN] = {};
        int totalLen = str.length() + 1 + HEAD_LEN;
        std::sprintf(header, "%d", totalLen);
        memcpy(line, header, HEAD_LEN);
        memcpy(line + HEAD_LEN, str.c_str(), str.length() + 1);
        conn.Send(line, totalLen);
    }    

    return 0;
}
