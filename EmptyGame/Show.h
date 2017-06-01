#pragma once
#include <string.h>
#include <iostream>
#include <windows.h>
#include <iostream>
#include <string.h>
#include <atlstr.h>
#include <time.h>
using namespace std;

extern bool gameover;
extern string strFilePath;

const string ProgramTitle = "Draw Bitmap";
//string strFilePath = "J:\\开发文档\\yuzhu\\image_12.bmp";

//绘制图片
void DrawBitmap(char * filemane, int x, int y);

//init game
bool Game_Init();

//update game loop
void Game_Run();


//game end
void Game_End();

//create proc function
LRESULT CALLBACK GameWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


//create proc function
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//registre window class
ATOM GameMyRegisterClass(HINSTANCE hInstance);

//registre window class
ATOM MyRegisterClass(HINSTANCE hInstance);

//initinstance
bool GameInitInstance(HINSTANCE hInstance, int nCmdShow);

//create instance
bool InitInstance(HINSTANCE hInstance, int nCmdShow);


