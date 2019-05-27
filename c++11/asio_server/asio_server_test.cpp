#include "../asio_server/asio_server.hpp"
// 反应器Ractor(比如libevent)
// 1) 应用程序在反应器上注册具体事件处理器，处理器提供内部句柄给反应器
// 2) 在注册之后，应用程序开始启动反应器事件循环。反应器将通过select等待发生在句柄集上的就绪事件(比如:FD_READ,FD_WRITE,FD_CONNECT,FD_CLOSE等)。
// 3) 当一个或多个句柄变成就绪状态时(比如:某个socket的读就绪了)，反应器将通知注册的事件处理器。
// 4) 事件处理器处理就绪事件，完成用户请求。

// 主动器Proactor(比如:asio)
// 1) 应用程序需要定义一个异步执行的操作，例如，socket的异步读/写(WSASend,WSARecv)。
// 2) 执行异步操作，异步事件处理器(stream_socket_service)将异步请求交给操作系统就返回了，
// 让操作系统去完成具体的操作，操作系统在完成处理器操作之后，会将完成事件放入一个完成事件队列。
// 3) 异步事件分离器(win iocp：GetQueuedCompletionStatus)会检测完成事件，若检测到完成事件，
// 则从完成事件队列中取出完成事件，并通知应用程序注册的完成事件处理函数()去处理。
// 4) 完成事件处理函数处理异步操作的结果。

// asio的async_write，对于同一个socket，必须收到上一个async_write的完成事件后，在调用async_write;
// 也就是对于同一个socket的async_write,必须顺序执行；调用async_write后，要收到在这个socket上的回调完成事件，
// 才能在这个socket上进行下一次async_write调用。
// async_write(sock1, buffer1, ....),async_write(sock2, buffer2, ...)是没问题的

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
