#include <boost/asio.hpp>
#include <array>
#include <functional>
#include <iostream>
#include "Message.hpp"
using namespace std;

using namespace boost::asio;
using namespace boost::asio::ip;
//using namespace boost;

const int MAX_IP_PACK_SIZE = 65536;
const int HEAD_LEN = 4;
class RWHandler : public std::enable_shared_from_this<RWHandler>
{
public:

    RWHandler(io_service& ios) : m_sock(ios)
    {
    }

    ~RWHandler()
    {
    }

    void HandleRead()
    {
        auto self = shared_from_this();

        async_read(m_sock, buffer(m_readMsg.data(), HEAD_LEN), [this, self](const boost::system::error_code& ec, size_t size)
        {
            if (ec || !m_readMsg.decode_header())
            {
                HandleError(ec);
                return;
            }

            ReadBody();
        });
    }
    void ReadBody() {
        auto self = shared_from_this();
        async_read(m_sock, buffer(m_readMsg.body(), m_readMsg.body_length()), [this, self](const boost::system::error_code& ec, size_t size) {
            if (ec) {
                HandleError(ec);
                return;
            }

            CallBack(m_readMsg.data(), (int)m_readMsg.length());

            HandleRead();
        });
    }

    void HandleWrite(char* data, int len)
    {
        boost::system::error_code ec;
        write(m_sock, buffer(data, len), ec);
        if (ec)
            HandleError(ec);
    }

    tcp::socket& GetSocket()
    {
        return m_sock;
    }

    void CloseSocket()
    {
        boost::system::error_code ec;
        m_sock.shutdown(tcp::socket::shutdown_both, ec);
        m_sock.close(ec);
    }

    void SetConnId(int connId)
    {
        m_connId = connId;
    }

    int GetConnId() const
    {
        return m_connId;
    }

    template<typename F>
    void SetCallBackError(F f)
    {
        m_callbackError = f;
    }

    void CallBack(char* pData, int len) {
        std::cout << pData + HEAD_LEN  << std::endl;
    }

private:
    void HandleError(const boost::system::error_code& ec)
    {
        CloseSocket(); 
        cout << ec.message() << endl;
        if (m_callbackError)
            m_callbackError(m_connId);
    }

private:
    tcp::socket m_sock;
    std::array<char, MAX_IP_PACK_SIZE> m_buff; 
    int m_connId;
    std::function<void(int)> m_callbackError;
    Message m_readMsg;
};