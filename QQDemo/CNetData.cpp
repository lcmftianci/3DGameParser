#include "stdafx.h"
#include "CNetData.h"
#include <iostream>

CNetData::CNetData()
{

}

//服务器绑定套接字函数
void CNetData::bind()
{
	WSADATA data;					//定义结构体变量
	CString name;					//定义主机名字符串
	DWORD   ss = MAKEWORD(2, 0);	//指定套接字版本
	::WSAStartup(ss, &data);		//初始化套接字库
	SOCKET t_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建套接字
	sockaddr_in addr;				//定义地址结构变量
	::gethostname((char*)&name, (int)sizeof(name));		//获取主机名
	hostent *p = ::gethostbyname((char*)&name);			//从主机名获取主机地址
	in_addr *a = (in_addr*)*p->h_addr_list;				//获得本机IP地址
	//USES_CONVERSION;				//字符串转换声明
	//CString str14 = A2W(::inet_ntoa(a[0]));		//转换字符串IP地址
	//CString str14;
	//str14.Format("%s", ::inet_ntoa(a[0]));
	std::string str14 = ::inet_ntoa(a[0]);
	addr.sin_family = AF_INET;			//填充地址结构
	addr.sin_port = htons(80);			//指定监听端口80
	addr.sin_addr.S_un.S_addr = inet_addr(str14.c_str());//指定主机IP地址
	::bind(t_socket, (sockaddr*)&addr, sizeof(addr));	//将本地信息绑定套接字
	::listen(t_socket, 5);			//监听
	WSAAsyncSelect(t_socket, this->m_hWnd, WM_SOCK, FD_ACCEPT | FD_READ);
}

void CNetData::sevsend(SOCKET&, char*, int, int)
{

}

void CNetData::sevrecv(SOCKET&, char*, int, int)
{

}

void CNetData::connect()
{

}

void CNetData::send(SOCKET&, char*, int, int)
{

}

void CNetData::recv(SOCKET&, char*, int, int)
{

}

