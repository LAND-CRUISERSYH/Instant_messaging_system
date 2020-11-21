//公共头文件，包括所有需要的宏以及socket网络编程头文件，以及消息结构体(用来表示消息类别等)
#ifndef __COMMON_H__
#define __COMMON_H__
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/epoll.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<list>
#include<string.h>

//默认服务器端IP地址
#define SERVER_IP "127.0.0.1"

//服务器端口号
#define SERVER_PORT 8888

//epoll支持的最大句柄数(建议数)
#define EPOLL_SIZE 5000

//缓冲区大小(65535)
#define BUF_SIZE 0XFFFF

//新用户登录后的欢迎信息
#define SERVER_WELCOME "Welcome you join to the char room!Your chat ID is: Client %d"

//其他用户收到消息的前缀
#define SERVER_MESSAGE "ClientID %d say >> %s"
#define SERVER_PRIVATE_MESSAGE "Client %d say to you privately >> %s"
#define SERVER_PRIVATE_ERROR_MESSAGE "Client %d is not in the chat room yet~"

//退出系统
#define EXIT "EXIT"

//提醒你是聊天室中唯一的客户
#define CAUTION "There is only one in the chat room!"

//注册新的fd到epollfd中
//参数enable_et表示是否启用ET模式，如果为true则启用，否则使用LT模式
static void addfd(int epollfd,int fd,bool enable_et)
{
	struct epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	if(enable_et)
		ev.events = EPOLLIN|EPOLLET;
	epoll_ctl(epollfd,EPOLL_CTL_ADD,fd,&ev);
	
	//设置socket为非阻塞模式(套接字立即返回，不管I/O是否完成，该函数所在的线程会继续运行)
	fcntl(fd,F_SETFL,fcntl(fd,F_GETFD,0)|O_NONBLOCK);
	printf("fd added to epoll!\n\n");	
}

//定义信息结构，在服务端和客户端之间传送
struct Msg
{
	int type;             //消息类别
	int fromID;           //发送方FD
	int toID;           //接收方FD
	char content[BUF_SIZE];      //文字信息
};
#endif
