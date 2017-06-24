#pragma once
#include <windows.h>


//游戏初始化
bool Game_Init(HWND hwnd);

//游戏运行程序
void Game_Run(HWND hwnd);

//游戏结束
void Game_End(HWND hwnd);

//消息响应函数
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);




