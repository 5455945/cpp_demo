#include "../asio_server/asio_server.hpp"
// ��Ӧ��Ractor(����libevent)
// 1) Ӧ�ó����ڷ�Ӧ����ע������¼����������������ṩ�ڲ��������Ӧ��
// 2) ��ע��֮��Ӧ�ó���ʼ������Ӧ���¼�ѭ������Ӧ����ͨ��select�ȴ������ھ�����ϵľ����¼�(����:FD_READ,FD_WRITE,FD_CONNECT,FD_CLOSE��)��
// 3) ��һ�����������ɾ���״̬ʱ(����:ĳ��socket�Ķ�������)����Ӧ����֪ͨע����¼���������
// 4) �¼���������������¼�������û�����

// ������Proactor(����:asio)
// 1) Ӧ�ó�����Ҫ����һ���첽ִ�еĲ��������磬socket���첽��/д(WSASend,WSARecv)��
// 2) ִ���첽�������첽�¼�������(stream_socket_service)���첽���󽻸�����ϵͳ�ͷ����ˣ�
// �ò���ϵͳȥ��ɾ���Ĳ���������ϵͳ����ɴ���������֮�󣬻Ὣ����¼�����һ������¼����С�
// 3) �첽�¼�������(win iocp��GetQueuedCompletionStatus)��������¼�������⵽����¼���
// �������¼�������ȡ������¼�����֪ͨӦ�ó���ע�������¼�������()ȥ����
// 4) ����¼������������첽�����Ľ����

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
