#include <windows.h>
#include <d3d9.h>
#include <time.h>
#include <iostream>
#include <atlstr.h>


//namespace
using namespace std;

//import library
#pragma comment(lib, "d3d9.lib")

//define some string
CString ProgramTitle = "Hello";
CString ProgramCaption = "China";
CString APPTITLE = "Direct3D_Windowed";
const int SCREENH = 1024;
const int SCREENW = 768;

//Direct3D objects
LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;
bool gameover = false;
HWND window;
HDC device;

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


#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

//GameInitfunc
bool Game_Init(HWND hwnd)
{
	//1.init d3d
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		MessageBox(hwnd, _T("Error initializing Direct3D"), _T("Error"), MB_OK);
		return false;
	}

	//2.set Direct3D presentation parameters
	D3DDISPLAYMODE dm;
	d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	/*d3dpp.BackBufferHeight = SCREENH;
	d3dpp.BackBufferWidth = SCREENW;
	d3dpp.hDeviceWindow = hwnd;
	*/

	d3dpp.BackBufferHeight = dm.Height;
	d3dpp.BackBufferWidth = dm.Width;
	d3dpp.Windowed = FALSE;

	//3.create d3d device
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);
	if(d3ddev == NULL)
	{ 
		MessageBox(hwnd, _T("Error createing Direct3d device"), _T("Error"), MB_OK);
		return false;
	}
	return true;
}

//game run
void Game_Run(HWND hwnd)
{
	//1.judge d3ddev is valid
	if (!d3ddev)
		return;
	
	//2.clear back buffer to bright green
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	//3.start rendering
	if (d3ddev->BeginScene())
	{
		d3ddev->EndScene();
		d3ddev->Present(NULL, NULL, NULL, NULL);
	}

	//char * str = const_cast<char*>(strFilePath.c_str());
	//DrawBitmap(str, 0, 0);

	//4.check for escape key(to exit program)
	if (KEY_DOWN(VK_ESCAPE))
	{
		PostMessage(hwnd, WM_DESTROY, 0, 0);
	}
}

//game end
void Game_End(HWND hwnd)
{
	//1.release d3ddev
	if (d3ddev)
	{
		d3ddev->Release();
		d3ddev = NULL;
	}

	//2.release d3d
	if (d3d)
	{
		d3d->Release();
		d3d = NULL;
	}
}

//windows event handing function
LRESULT WINAPI WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//1.switch
	switch (message)
	{
	case WM_DESTROY:
		gameover = true;
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

//main windows entry function
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//MessageBox(NULL, ProgramTitle, ProgramCaption, MB_OKCANCEL);
	//1.WNDCLASSEX
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.style = 0;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.lpszMenuName = NULL;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	//wc.hbrBackground = (HBITMAP)LoadImage(0, strFilePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	wc.lpszClassName = _T("MainWindowClass");
	if (!RegisterClassEx(&wc))
		return FALSE;

	//2.MSG
	MSG msg;

	//3.Create Window
	//HWND hwnd = CreateWindow(_T("MainWindowClass"), APPTITLE, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, SCREENW, SCREENH, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)NULL);
	HWND hwnd = CreateWindow(_T("MainWindowClass"), APPTITLE, WS_EX_TOPMOST|WS_POPUP, CW_USEDEFAULT, CW_USEDEFAULT, SCREENW, SCREENH, (HWND)NULL, (HMENU)NULL, hInstance, (LPVOID)NULL);

	//4.was there an error creating the window
	if (hwnd == 0)
	{
		return 0;
	}
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);
	device = GetDC(hwnd);

	//5.init Game
	if (!Game_Init(hwnd))
		return 0;

	//6.main message loop
	while (!gameover)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Game_Run(hwnd);
	}

	Game_End(hwnd);
	return msg.wParam;
}