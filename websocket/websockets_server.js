
// npm install ws
// npm install -save ws uuid
const WebSocket = require('ws');
let port = 8888;
const server = new WebSocket.Server({ port: port });
server.on('connection', function(socket) {
   console.log("与客户端连接成功！");
   socket.on('message', function(data) {
      console.log("收到消息：" + data);
      socket.send("Hello, Client!");
   });
   socket.on('close', function(event) {
      console.log("连接已关闭：" + event.code);
   });
});
