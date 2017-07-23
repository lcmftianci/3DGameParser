#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "ScreenUtil.h"



void logs(std::string strMes)
{
	MessageBox(NULL, _T(strMes.c_str()), _T("提示"), MB_OK);
}

HBITMAP Copybitmap(LPRECT lprect)
{
	HDC hscrdc, hmemdc;// 屏幕和内存设备描述表 
	HBITMAP hbitmap, holdbitmap;// 位图句柄 
	int nx, ny, nx2, ny2;// 选定区域坐标 
	int nwidth, nheight;// 位图宽度和高度 
	int xscrn, yscrn;// 屏幕分辨率 
					 // 确保选定区域不为空矩形 
	if (IsRectEmpty(lprect))
		return NULL;
	//为屏幕创建设备描述表 
	hscrdc = CreateDC("display", NULL, NULL, NULL);
	//为屏幕设备描述表创建兼容的内存设备描述表 
	hmemdc = CreateCompatibleDC(hscrdc);
	// 获得选定区域坐标 
	nx = lprect->left;
	ny = lprect->top;
	nx2 = lprect->right;
	ny2 = lprect->bottom;
	// 获得屏幕分辨率 
	xscrn = GetDeviceCaps(hscrdc, HORZRES);
	yscrn = GetDeviceCaps(hscrdc, VERTRES);
	//确保选定区域是可见的 
	if (nx < 0)
		nx = 0;
	if (ny < 0)
		ny = 0;
	if (nx2 > xscrn)
		nx2 = xscrn;
	if (ny2 > yscrn)
		ny2 = yscrn;
	nwidth = nx2 - nx;
	nheight = ny2 - ny;
	// 创建一个与屏幕设备描述表兼容的位图 
	hbitmap = CreateCompatibleBitmap(hscrdc, nwidth, nheight);
	// 把新位图选到内存设备描述表中 
	holdbitmap = (HBITMAP)SelectObject(hmemdc, hbitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中 
	BitBlt(hmemdc, 0, 0, nwidth, nheight, hscrdc, nx, ny, SRCCOPY);
	//得到屏幕位图的句柄 
	hbitmap = (HBITMAP)SelectObject(hmemdc, holdbitmap);
	//清除 
	DeleteDC(hscrdc);
	DeleteDC(hmemdc);
	// 返回位图句柄 
	return hbitmap;
}


//屏幕截图功能实现  
/*virtual */HBITMAP ScreenCapture(LPSTR filename, WORD bitCount, LPRECT lpRect)
{
	HBITMAP hBitmap;
	HDC hScreenDC = CreateDCA("DISPLAY", NULL, NULL, NULL);   //通过指定DISPLAY来获取一个显示设备上下文环境  
	HDC hmemDC = CreateCompatibleDC(hScreenDC);            //该函数创建一个与指定设备兼容的内存设备上下文环境（DC）  
	int ScreenWidth = GetDeviceCaps(hScreenDC, HORZRES);    //获取指定设备的性能参数（此处获取屏幕宽度）  
	int ScreenHeight = GetDeviceCaps(hScreenDC, VERTRES);   //获取指定设备的性能参数（此处获取屏幕高度）  
	HBITMAP hOldBM;
	PVOID lpData;   //内存分配成功返回的指向所分配内存块的首地址指针  
	int startX;     //截图x位置  
	int startY;     //截图y位置  
	int width;      //截图宽度  
	int height;     //截图高度  
	long BitmapSize;
	DWORD BitsOffset;
	DWORD ImageSize;
	DWORD FileSize;
	BITMAPINFOHEADER bmInfo; //BITMAPINFOHEADER结构所包含的成员表明了图像的尺寸、原始设备的颜色格式、以及数据压缩方案  
	BITMAPFILEHEADER bmFileHeader;
	HANDLE bmFile, hpal, holdpal = NULL;;
	DWORD dwWritten;
	if (lpRect == NULL)
	{
		startX = startY = 0;
		width = ScreenWidth;
		height = ScreenHeight;
	}
	else
	{
		startX = lpRect->left;
		startY = lpRect->top;
		width = lpRect->right - lpRect->left;
		height = lpRect->bottom - lpRect->top;
	}
	//创建一张长width，宽height的画布，用于后面绘制图形  
	hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
	//该函数选择一对象到指定的设备上下文环境中，该新对象替换先前的相同类型的对象。  
	hOldBM = (HBITMAP)SelectObject(hmemDC, hBitmap);
	//该函数对指定的源设备环境区域中的像素进行位块（bit_block）转换，以传送到目标设备环境。  
	BitBlt(hmemDC, 0, 0, width, height, hScreenDC, startX, startY, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hmemDC, hOldBM);
	if (filename == NULL)
	{
		DeleteDC(hScreenDC);
		DeleteDC(hmemDC);
		return hBitmap;
	}
	BitmapSize = ((((width * 32) + 32) / 32) * 4)*height;
	//用来在指定的堆上分配内存，并且分配后的内存不可移动(HEAP_NO_SERIALIZE 不使用连续存取)  
	lpData = HeapAlloc(GetProcessHeap(), HEAP_NO_SERIALIZE, BitmapSize);
	ZeroMemory(lpData, BitmapSize);
	ZeroMemory(&bmInfo, sizeof(BITMAPINFOHEADER));
	bmInfo.biSize = sizeof(BITMAPINFOHEADER); //位图信息结构长度 ,必须为40  
	bmInfo.biWidth = width;                   //图像宽度 单位是像素  
	bmInfo.biHeight = height;                 //图像高度 单位是像素  
	bmInfo.biPlanes = 1;                      //必须为1  
	bmInfo.biBitCount = bitCount;             //设置图像的位数。比如8位，16位，32位位数越高分辨率越高  
	bmInfo.biCompression = BI_RGB;            //位图是否压缩 BI_RGB为不压缩  
	ZeroMemory(&bmFileHeader, sizeof(BITMAPFILEHEADER));
	BitsOffset = sizeof(BITMAPFILEHEADER) + bmInfo.biSize;
	ImageSize = ((((bmInfo.biWidth*bmInfo.biBitCount) + 31) / 32) * 4)*bmInfo.biHeight;
	FileSize = BitsOffset + ImageSize;
	bmFileHeader.bfType = 0x4d42;//'B'+('M'<<8);  
	bmFileHeader.bfSize = FileSize;
	bmFileHeader.bfOffBits = BitsOffset;
	hpal = GetStockObject(DEFAULT_PALETTE);
	if (hpal)
	{
		holdpal = SelectPalette(hmemDC, (HPALETTE)hpal, false);
		RealizePalette(hmemDC);
	}
	GetDIBits(hmemDC, hBitmap, 0, bmInfo.biHeight, lpData, (BITMAPINFO *)&bmInfo, DIB_RGB_COLORS);
	if (holdpal)
	{
		SelectPalette(hmemDC, (HPALETTE)holdpal, true);
		RealizePalette(hmemDC);
	}
	bmFile = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (bmFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "Create File Error!", "提示", MB_OK | MB_ICONWARNING);
	}
	WriteFile(bmFile, &bmFileHeader, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(bmFile, &bmInfo, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	WriteFile(bmFile, lpData, ImageSize, &dwWritten, NULL);
	CloseHandle(bmFile);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, lpData);
	::ReleaseDC(0, hScreenDC);
	DeleteDC(hmemDC);
	//logs->WriteFormat("【截图保存成功】");
	logs("【截图保存成功】");
	//MessageBoxA(NULL,"玩家您好，你的本场游戏战绩已经通过截图保存在桌面","提示",MB_OK);  
	return hBitmap;
}

//把截图的文件保存到桌面  
/*virtual */BOOL CaptureLolToDesktop(HWND hWnd)
{
	Sleep(1 * 1000);
	LPRECT lprc = new RECT;
	GetWindowRect(hWnd, lprc);
	//std::string strTime;
	CString strTime;
	DWORD llocaltime = GetTickCount();
	char chDesktopPath[MAX_PATH] = { 0 };
	SHGetSpecialFolderPathA(NULL, chDesktopPath, CSIDL_DESKTOP, 0);//获取当前用户桌面路径
	strTime.Format("%s\\截图%ld.jpg", chDesktopPath, llocaltime);
	
	//CString - > string
	//char ch[2048] = "";
	//sprintf(ch, "%s", strFilePath.c_str());
	//int num = MultiByteToWideChar(0, 0, ch, -1, NULL, 0);
	//wchar_t *lpstr1 = new wchar_t[num];
	//MultiByteToWideChar(0, 0, ch, -1, lpstr1, num);
	char chStrTime[2048] = "";
	sprintf(chStrTime, "%s", strTime);
	std::string strTimeS = chStrTime;

	//logs->WriteFormat("截图保存路径为%s", strTime.c_str());
	CString strDirection;
	strDirection.Format("截图保存路径为%s", strTimeS.c_str());
	//char ch[2048] = "";
	//sprintf(ch, "%s", strFilePath.c_str());
	//int num = MultiByteToWideChar(0, 0, ch, -1, NULL, 0);
	//wchar_t *lpstr1 = new wchar_t[num];
	//MultiByteToWideChar(0, 0, ch, -1, lpstr1, num);

	//CString - > string
	char chStr[2048] = "";
	sprintf(chStr, "%s", strDirection);
	std::string strDir = chStr;
	logs(strDir);
	ScreenCapture(LPSTR(strTimeS.c_str()), 16, lprc);
	delete lprc;
	return TRUE;
}

static CString GetTempName(CString strPath)
{
	const int nMin = 0;
	const int nMax = 999;
	const CString strBase(_T("ScreenCap"));
	static int nLastKnown = nMin;

	// count up sequentially to make sure we take the next available
	// slot
	if (strPath.Right(1) != "\\")
		strPath += '\\';

	bool bFound = false;
	CString strPathName;
	while (!bFound) {
		if (nLastKnown > nMax)
			break;
		strPathName = strPath + strBase;
		strPathName.AppendFormat(_T("%03.3d.png"), nLastKnown++);
		HANDLE hFile = ::CreateFile(strPathName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE) {
			::CloseHandle(hFile);
			bFound = TRUE;
		}
	}
	if (!bFound)
		strPathName.Empty();
	return(strPathName);
}


void CaptureScreen(CaptureData* lpData)
{
	ASSERT(lpData);
	if (!lpData)
		return;

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL bStat;
	CImage image;
	CWnd *pWnd;
	CRect rect;
	if (lpData->bCaptureFullScreen) {
		pWnd = CWnd::GetDesktopWindow();
	}
	else {
		pWnd = CWnd::GetActiveWindow();
	}
	ASSERT(pWnd);
	if (pWnd == NULL)
		return;

	CWindowDC  winDC(pWnd);
	pWnd->GetWindowRect(rect);
	int nBPP = winDC.GetDeviceCaps(BITSPIXEL) * winDC.GetDeviceCaps(PLANES);
	if (nBPP < 24)
		nBPP = 24;
	bStat = image.Create(rect.Width(), rect.Height(), nBPP);
	ASSERT(bStat);
	if (!bStat)
		return;
	CImageDC imageDC(image);
	::BitBlt(imageDC, 0, 0, rect.Width(), rect.Height(), winDC, 0, 0, SRCCOPY);
	CString strTempName = GetTempName(CString(lpData->szCapturePath));
	HRESULT hr = image.Save(strTempName);
	if (FAILED(hr)) {
		TRACE("Couldn't Save File: %s, %x\n", (LPCTSTR)strTempName, hr);
		return;
	}
	strncpy_s(lpData->szCaptureFilename, MAX_PATH, CT2A(::PathFindFileName(strTempName)), _TRUNCATE);
}



BOOL ConfigureCapture(HWND hWndParent, CaptureData* lpData) 
{
	ASSERT(lpData);
	if (!lpData)
		return(FALSE);

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	BOOL bStat = FALSE;
	USES_CONVERSION;
	bStat = TRUE;
	lpData->bCaptureFullScreen = 1;
	strncpy_s(lpData->szCapturePath, MAX_PATH, CT2A("E:\\vsproj\\3DGameParser\\ScreenCap\\Vedio\\"), _TRUNCATE);
	*lpData->szCaptureFilename = '\0';
	return(bStat);
}