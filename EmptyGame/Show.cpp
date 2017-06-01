#include "Show.h"

using namespace std;
HWND window;
HDC device;
bool gameover = false;
string strFilePath = "J:\\开发文档\\yuzhu\\image_12.bmp";

//绘制图片
void DrawBitmap(char * filemane, int x, int y)
{
	//load Image
	CString strFileName = filemane;
	HBITMAP image = (HBITMAP)LoadImage(0, strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bmp;
	GetObject(image, sizeof(BITMAP), &bmp);
	HDC hdcImage = CreateCompatibleDC(device);
	SelectObject(hdcImage, image);
	//draw image
	BitBlt(device, x, y, bmp.bmWidth, bmp.bmHeight, hdcImage, 0, 0, SRCCOPY);

	//delete device
	DeleteDC(hdcImage);
	DeleteObject((HBITMAP)image);
}

//init game
bool Game_Init()
{
	srand(time(NULL));
	return 1;
}

//update game loop
void Game_Run()
{
	if (gameover == true) return;
	
		RECT rect;
		GetClientRect(window, &rect);
		int x = rand() % (rect.right - rect.left);
		int y = rand() % (rect.bottom - rect.top);
		char * str = const_cast<char*>(strFilePath.c_str());
		DrawBitmap(str, x, y);
}

//game end
void Game_End()
{
	ReleaseDC(window, device);
}

//create proc function
LRESULT CALLBACK GameWinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT drawRect;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_DESTROY:
		gameover = true;
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

//create proc function
LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT drawRect;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 20; i++)
		{
			int x = i * 20;
			int y = i * 20;
			drawRect = { x, y, x + 100, y + 20 };
			CString strTitle = ProgramTitle.c_str();
			DrawText(hdc, strTitle, ProgramTitle.length(), &drawRect, DT_CENTER);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}


//registre window class
ATOM GameMyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)GameWinProc;
	wc.cbClsExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	CString strTitle = ProgramTitle.c_str();
	wc.lpszClassName = strTitle;
	wc.hIconSm = NULL;
	return RegisterClassEx(&wc);
}


//registre window class
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wc;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	CString strTitle = ProgramTitle.c_str();
	wc.lpszClassName = strTitle;
	wc.hIconSm = NULL;
	return RegisterClassEx(&wc);
}

//initinstance
bool GameInitInstance(HINSTANCE hInstance, int nCmdShow)
{
	CString strTile = ProgramTitle.c_str();
	window = CreateWindow(strTile, strTile, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
	if (window == 0)
		return 0;
	ShowWindow(window, nCmdShow);
	UpdateWindow(window);
	device = GetDC(window);
	return 1;
}

//create instance
bool InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	CString strTile = ProgramTitle.c_str();
	HWND hWnd = CreateWindow(strTile, strTile, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
	if (hWnd == 0)
		return 0;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//device = GetDC(hWnd);
	return 1;
}

//Find File
//void FindFile()
//{
//#define MAX_CFILEDLG_FILE_COUNT 99
//#define FILE_LIST_BUFFER_SIZE ((MAX_CFILEDLG_FILE_COUNT * (MAX_PATH + 1)) + 1)
//
//	CFileDialog dlg(TRUE);
//	wchar_t* p = strFilePath.GetBuffer(FILE_LIST_BUFFER_SIZE);
//	OPENFILENAME& ofn = dlg.GetOFN();
//	ofn.lpstrFile = p;
//	ofn.Flags |= OFN_ALLOWMULTISELECT;
//	ofn.nMaxFile = FILE_LIST_BUFFER_SIZE;
//	dlg.DoModal();
//#undef MAX_CFILEDLG_FILE_COUNT
//#undef FILE_LIST_BUFFER_SIZE
//}

