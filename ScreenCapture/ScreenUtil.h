#pragma once
#include <windef.h>
#include <ShlObj.h>
#include <iostream>
#include <afxstr.h>
#include <tchar.h>

/*
	程序目的
	截取屏幕上，然后显示在对话框上，可以前端显示这样就可以肆无忌惮的超代码了
*/

void logs(std::string strMes);

//图片保存到桌面
/*virtual */BOOL CaptureLolToDesktop(HWND hWnd);

//屏幕截图功能实现  
/*virtual */HBITMAP ScreenCapture(LPSTR filename, WORD bitCount, LPRECT lpRect);


