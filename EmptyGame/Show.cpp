#include "Show.h"
#include "resource.h"

using namespace std;
HWND window;
HDC device;
HINSTANCE hInst;
bool gameover = false;
string strFilePath = "J:\\开发文档\\yuzhu\\image_12.bmp";

void OpenFile();
void OnChooseColor();

void OnChooseColor()
{
	CHOOSECOLOR cc;                 // common dialog box structure 
	static COLORREF acrCustClr[16]; // array of custom colors 
	HWND hwnd = NULL;                      // owner window
	HBRUSH hbrush;                  // brush handle
	static DWORD rgbCurrent;        // initial color selection

									// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;

	if (ChooseColor(&cc) == TRUE)
	{
		hbrush = CreateSolidBrush(cc.rgbResult);
		rgbCurrent = cc.rgbResult;
	}

}

//绘制图片
void DrawBitmap(char * filemane, int x, int y)
{
	//load Image
	CString strFileName = filemane;
	
	//bitmap句柄
	HBITMAP image = (HBITMAP)LoadImage(0, strFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	
	//bitmap对象
	BITMAP bmp;
	GetObject(image, sizeof(BITMAP), &bmp);
	
	//设备对象
	HDC hdcImage = CreateCompatibleDC(device);
	SelectObject(hdcImage, image);
	
	//draw image
	BitBlt(device, x, y, bmp.bmWidth, bmp.bmHeight, hdcImage, 0, 0, SRCCOPY);

	//delete device
	DeleteDC(hdcImage);
	DeleteObject((HBITMAP)image);
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
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
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DLG_ABOUT), hWnd, About);
			break;
		case ID_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_OPEN:
			OpenFile();
			break;
		case ID_COLOR:
			OnChooseColor();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
		
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
	wc.lpszMenuName = MAKEINTRESOURCEW(IDR_MAIN_MENU);
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
	hInst = hInstance;
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
	hInst = hInstance;
	HWND hWnd = CreateWindow(strTile, strTile, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL);
	if (hWnd == 0)
		return 0;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	//device = GetDC(hWnd);
	return 1;
}

//Find File
void OpenFile()
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	HWND hwnd = NULL;              // owner window
	HANDLE hf;              // file handle

							// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = (LPWSTR)szFile;
	// Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
	// use the contents of szFile to initialize itself.
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

// Display the Open dialog box. 
	CString strPath;
	if (GetOpenFileName(&ofn) == TRUE)
	{
		hf = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE)NULL);
		strPath = ofn.lpstrFile;
	}

}

