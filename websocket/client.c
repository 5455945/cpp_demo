
// https://libwebsockets.org/
// libwebsockets是一款轻量级用来开发服务器和客户端的C库。按照官方(https://libwebsockets.org/)给出的介绍来看，
// 它不仅支持ws，wss还同时支持http与https，可以轻轻松松结合openssl等库来实现ssl加密。

// sudo apt-get install libwebsockets-dev
// #!/bin/bash
// libdir=libwebsockets
// g++ -g -o client client.c -I$libdir/include -L$libdir/lib -lwebsockets
// cmake -DLWS_WITH_SSL=0 -DLWS_WITH_ZIP_FOPS=0 ./ -G "Visual Studio 16 2019"
// cmake -DLWS_WITH_SSL=1 -DLWS_WITH_ZIP_FOPS=0 ./ -G "Visual Studio 16 2019"

// pacman -S mingw-w64-x86_64-libwebsockets
//g++ -g -o client client.cc -lwebsockets

// gcc 参数
//-E  预处理指定的源文件，不进行编译
//-S  编译指定的文件，但不进行汇编
//-c  编译、汇编指定的源文件，但是不进行链接

#include "libwebsockets.h"
#ifdef __cplusplus
#include <csignal> // g++
#else
#include <signal.h> // gcc
#endif
 
static volatile int exit_sig = 0;
#define MAX_PAYLOAD_SIZE  10 * 1024
 
void sighdl( int sig ) {
    lwsl_notice( "%d traped", sig );
    exit_sig = 1;
}

// 会话上下文对象，结构根据需要自定义
struct session_data {
    int msg_count;
    unsigned char buf[LWS_PRE + MAX_PAYLOAD_SIZE];
    int len;
};
 
// 某个协议下的连接发生事件时，执行的回调函数
//
// wsi：指向WebSocket实例的指针
// reason：导致回调的事件
// user 库为每个WebSocket会话分配的内存空间
// in 某些事件使用此参数，作为传入数据的指针
// len 某些事件使用此参数，说明传入数据的长度
int callback( struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len ) {
    struct session_data *data = (struct session_data *) user;
    switch ( reason ) {
        case LWS_CALLBACK_CLIENT_ESTABLISHED:   // 连接到服务器后的回调
            lwsl_notice( "Connected to server ok!\n" );
            break;
 
        case LWS_CALLBACK_CLIENT_RECEIVE:       // 接收到服务器数据后的回调，数据为in，其长度为len
            lwsl_notice( "Rx: %s\n", (char *) in );
            break;
        case LWS_CALLBACK_CLIENT_WRITEABLE:     // 当此客户端可以发送数据时的回调
		    //printf("writeable %d\n", data->msg_count);
            if ( data->msg_count < 3 ) {
                // 前面LWS_PRE个字节必须留给LWS
                memset( data->buf, 0, sizeof( data->buf ));
                char *msg = (char *) &data->buf[ LWS_PRE ];
                data->len = sprintf( msg, "hello %d", ++data->msg_count );
                lwsl_notice( "Tx: %s\n", msg );
                // 通过WebSocket发送文本消息
                lws_write( wsi, &data->buf[ LWS_PRE ], data->len, LWS_WRITE_TEXT );
            }
            break;
    }
    return 0;
}
 
// 支持的WebSocket子协议数组
// 子协议即JavaScript客户端WebSocket(url, protocols)第2参数数组的元素
// 你需要为每种协议提供回调函数
struct lws_protocols protocols[] = {
    {
        //协议名称，协议回调，接收缓冲区大小
        "ws", callback, sizeof( struct session_data ), MAX_PAYLOAD_SIZE,
    },
    {
        NULL, NULL,   0 // 最后一个元素固定为此格式
    }
};
 
int main() {
    // 信号处理函数
    signal( SIGTERM, sighdl );
 
    // 用于创建vhost或者context的参数
    struct lws_context_creation_info ctx_info = { 0 };
    ctx_info.port = CONTEXT_PORT_NO_LISTEN;
    ctx_info.iface = NULL;
    ctx_info.protocols = protocols;
    ctx_info.gid = -1;
    ctx_info.uid = -1;
    
    ////ssl支持（指定CA证书、客户端证书及私钥路径，打开ssl支持）
    //ctx_info.ssl_ca_filepath = "../ca/ca-cert.pem";
    //ctx_info.ssl_cert_filepath = "./client-cert.pem";
    //ctx_info.ssl_private_key_filepath = "./client-key.pem";
    ctx_info.options |= LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
 
    // 创建一个WebSocket处理器
    struct lws_context *context = lws_create_context( &ctx_info );
 
    char address[] = "127.0.0.1";
    int port = 8000;
    char addr_port[256] = { 0 };
    sprintf(addr_port, "%s:%u", address, port & 65535 );
 
    // 客户端连接参数
    struct lws_client_connect_info conn_info = { 0 };
    conn_info.context = context;
    conn_info.address = address;
    conn_info.port = port;
	// 启用ssl
    //conn_info.ssl_connection = 1;
	// 禁用ssl
	conn_info.ssl_connection = 0;
    conn_info.path = "./";
    conn_info.host = addr_port;
    conn_info.origin = addr_port;
    conn_info.protocol = protocols[ 0 ].name;
 
    // 下面的调用触发LWS_CALLBACK_PROTOCOL_INIT事件
    // 创建一个客户端连接
    struct lws *wsi = lws_client_connect_via_info( &conn_info );
    while ( !exit_sig ) {
        // 执行一次事件循环（Poll），最长等待1000毫秒
        lws_service( context, 1000 );

        // 下面的调用的意义是：当连接可以接受新数据时，触发一次WRITEABLE事件回调
        // 当连接正在后台发送数据时，它不能接受新的数据写入请求，所有WRITEABLE事件回调不会执行
        lws_callback_on_writable( wsi );
    }
    // 销毁上下文对象
    lws_context_destroy( context );
 
    return 0;
}
