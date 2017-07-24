#pragma once
#include <windef.h>
#include <ShlObj.h>
#include <iostream>
#include <afxstr.h>
#include <windows.h>
#include <iostream>
#include <tchar.h>

struct CaptureData
{
	BOOL    bCaptureFullScreen;
	char	szCapturePath[MAX_PATH]; // no unicode path support
	char	szCaptureFilename[MAX_PATH];
};

/*
	程序目的
	截取屏幕上，然后显示在对话框上，可以前端显示这样就可以肆无忌惮的超代码了


	截取屏幕图片的方法
	有根据让上说法有三种
	一种是基于GDI，一种是基于DX，另一种是用Windows Media API抓屏

	首先我们来用GDI函数来截取屏幕
	截屏的具体方法，网上都有，这是直接在网上吵到
	第一、首先用CreateDC函数建设备上下文环境（创建设备描述表），名为display。
	第二、用CreateCompatibleDC函数创建display设备兼容的内存设备上下文环境（DC）（创建兼容的内存设备描述表）。
	第三、获得屏幕分辨率和要截图的区域坐标。GetDeviceCaps获取屏幕分辨率。
	第四、用CreateCompatibleBitmap函数创建与display设备兼容的位图（创建一个与屏幕设备描述表兼容的位图）。
	第五、SelectObject函数把新位图选到内存设备描述表中。
	第六、BitBlt函数把屏幕设备描述表拷贝到内存设备描述表中。
	第七、最后SelectObject得到屏幕位图的句柄。
	第八、显示位图。

	//为了实现代码的通用性这里我们把函数封装在Common公共类里面

*/

/*一、GDI截屏*/
//1.1
HBITMAP Copybitmap(LPRECT lprect);

void logs(std::string strMes);

//图片保存到桌面
/*virtual */BOOL CaptureLolToDesktop(HWND hWnd);

//屏幕截图功能实现  
/*virtual */HBITMAP ScreenCapture(LPSTR filename, WORD bitCount, LPRECT lpRect);

//截屏函数
void CaptureScreen(CaptureData* lpData);

//显示配置
BOOL ConfigureCapture(HWND hWndParent, CaptureData* lpData);

//将图片显示到窗口上




