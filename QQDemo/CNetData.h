#pragma once
#include <WinSock2.h>


//套接字处理类
class CNetData
{
public:
	CNetData();							//构造函数
	void bind();						//服务器绑定套接字函数
	void sevsend(SOCKET&, char*, int, int);	//服务器发送函数	
	void sevrecv(SOCKET&, char*, int, int);   	//服务器接收函数
	void connect();						//客户端连接函数
	void send(SOCKET&, char*, int, int);		//客户端发送函数	
	void recv(SOCKET&, char*, int, int);	   	//客户端接收函数
	~CNetData();
};