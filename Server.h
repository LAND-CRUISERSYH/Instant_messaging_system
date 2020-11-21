#ifndef __SERVER_H__
#define __SERVER_H__
#include"Common.h"

using namespace std;

//服务端类，用来处理客户端请求
class Server
{
public:
	Server();              //无参数构造函数
	
	void Init();           //初始化服务端设置

	void Close();         //关闭服务

	void Start();         //启动服务端
private:
	int SendBroadcastMessage(int clientfd);       //广播消息给所有客户端

	struct sockaddr_in serverAddr;              //服务器端serverAddr信息

	int listener;                              //创建监听的socket

	int epfd;                                //epoll_create创建后的返回值

	list<int> clients_list;                   //客户端列表
};
#endif
