
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Panel.h"
#include "ChildView.h"
#include "PenWidth.h"
#include <gdiplusgraphics.h>
#include <gdiplusimaging.h>

using namespace Gdiplus;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_strFilePath = "";
	m_nNum = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_TOOLS_COLOR, &CChildView::OnToolsColor)
	ON_COMMAND(ID_TOOLS_SIZE, &CChildView::OnToolsSize)
	ON_COMMAND(ID_FILE_SAVEWND, &CChildView::OnFileSaveWnd)
	ON_COMMAND(ID_FILE_SAVEVIEW, &CChildView::OnFileSaveview)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	//CPaintDC dc(this); // device context for painting
	CClientDC dc(this);
	// TODO: Add your message handler code here
	/*CPanelDoc* pDc = GetDocument();*/

	///*处理移动窗口曲线消失*/
	//CPen pen(PS_SOLID, 3, m_Color);
	//CPen *OldPen = dc.SelectObject(&pen);
	//CPoint OldPoint;
	///*处理多次划线，曲线连接*/
	//std::map<int, std::vector<CPoint>>::iterator iterPos = m_mapArrPoint.begin();
	//for (; iterPos != m_mapArrPoint.end(); iterPos++)
	//{
	//	std::vector<CPoint>::iterator iterInnerPos = iterPos->second.begin();
	//	for (int i = 0; iterInnerPos != iterPos->second.end(); iterInnerPos++, i++)
	//	{
	//		if (i == 0)
	//			OldPoint = *iterInnerPos;
	//		dc.MoveTo(OldPoint);
	//		dc.LineTo(*iterInnerPos);
	//		OldPoint = *iterInnerPos;
	//	}
	//}
	//dc.SelectObject(OldPen);

	/*处理多次划线，曲线连接*/
	std::map<int, std::map<COLORREF, std::vector<CPoint>>>::iterator iterPos = m_mapColorArrPoint.begin();
	for (; iterPos != m_mapColorArrPoint.end(); iterPos++)
	{
		std::map<COLORREF, std::vector<CPoint>>::iterator iterColor = iterPos->second.begin();
		for (; iterColor != iterPos->second.end(); iterColor++)
		{
			/*进阶处理每次绘制画笔颜色不同的问题*/
			CPen pen(PS_SOLID, 3, iterColor->first);
			CPen *OldPen = dc.SelectObject(&pen);
			CPoint OldPoint;
			std::vector<CPoint>::iterator iterInnerPos = iterColor->second.begin();
			for (int i = 0; iterInnerPos != iterColor->second.end(); iterInnerPos++, i++)
			{
				if (i == 0)
					OldPoint = *iterInnerPos;
				dc.MoveTo(OldPoint);
				dc.LineTo(*iterInnerPos);
				OldPoint = *iterInnerPos;
			}
			dc.SelectObject(OldPen);
		}

	}
	// Do not call CWnd::OnPaint() for painting messages
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_OldPoint = point;
	m_Point = point;
	m_bDraw = TRUE;
	m_arrPoint.clear();
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDraw = FALSE;
	//m_mapArrPoint[m_nNum] = m_arrPoint;
	m_mapColorArrPoint[m_nNum][m_Color] = m_arrPoint;
	m_nNum++;
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	/*HDC hdc;
	hdc = ::GetDC(m_hWnd);*/
	CClientDC dc(this);
	if (m_Color == NULL)
	{
		m_Color = RGB(255, 0, 23);
	}
	CPen pen(PS_SOLID, 3, m_Color);
	CPen *OldPen = dc.SelectObject(&pen);
	if (m_bDraw == TRUE)
	{
		dc.MoveTo(m_OldPoint);
		dc.LineTo(point);
		m_OldPoint = point;
		m_arrPoint.push_back(point);
	}
	dc.SelectObject(OldPen);

	//CDC * dc = CWnd::GetDC();
	//if (m_Color == NULL)
	//{
	//	m_Color = RGB(255, 0, 23);
	//}
	//CPen pen(PS_SOLID, 3, m_Color);
	//CPen *OldPen = dc->SelectObject(&pen);
	//if (m_bDraw == TRUE)
	//{
	//	dc->MoveTo(m_OldPoint);
	//	dc->LineTo(point);
	//	m_OldPoint = point;
	//}
	//dc->SelectObject(OldPen);
}


/*选择画笔颜色*/
void CChildView::OnToolsColor()
{
	// TODO: Add your command handler code here
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
		m_Color = cc.rgbResult;
	}
}

//保存窗口内容到图片
void SaveHwndToBmpFile(HWND hWnd, LPCTSTR lpszPath)  
{
	HDC hDC = ::GetWindowDC(hWnd);
	ASSERT(hDC);

	HDC hMemDC = ::CreateCompatibleDC(hDC);
	ASSERT(hMemDC);

	RECT rc;
	::GetWindowRect(hWnd, &rc);

	HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, rc.right - rc.left, rc.bottom - rc.top);
	ASSERT(hBitmap);

	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC, hBitmap);
	::PrintWindow(hWnd, hMemDC, 0);

	BITMAP bitmap = { 0 };
	::GetObject(hBitmap, sizeof(BITMAP), &bitmap);
	BITMAPINFOHEADER bi = { 0 };
	BITMAPFILEHEADER bf = { 0 };

	CONST int nBitCount = 24;
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bitmap.bmWidth;
	bi.biHeight = bitmap.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = nBitCount;
	bi.biCompression = BI_RGB;
	DWORD dwSize = ((bitmap.bmWidth * nBitCount + 31) / 32) * 4 * bitmap.bmHeight;

	HANDLE hDib = GlobalAlloc(GHND, dwSize + sizeof(BITMAPINFOHEADER));
	LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);
	*lpbi = bi;

	::GetDIBits(hMemDC, hBitmap, 0, bitmap.bmHeight, (BYTE*)lpbi + sizeof(BITMAPINFOHEADER), (BITMAPINFO*)lpbi, DIB_RGB_COLORS);

	try
	{
		CFile file;
		file.Open(lpszPath, CFile::modeCreate | CFile::modeWrite);
		bf.bfType = 0x4d42;
		dwSize += sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
		bf.bfSize = dwSize;
		bf.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		file.Write((BYTE*)&bf, sizeof(BITMAPFILEHEADER));
		file.Write((BYTE*)lpbi, dwSize);
		file.Close();
	}
	catch (CFileException* e)
	{
		e->ReportError();
		e->Delete();
	}

	GlobalUnlock(hDib);
	GlobalFree(hDib);

	::SelectObject(hMemDC, hOldBmp);
	::DeleteObject(hBitmap);
	::DeleteObject(hMemDC);
	::ReleaseDC(hWnd, hDC);
}

void CChildView::OnToolsSize()
{
	// TODO: Add your command handler code here
	CPenWidth dlg;
	if (dlg.DoModal() == IDOK)
	{

	}
}

void CChildView::GetSavePath()
{
	//View ColorizedCopy to Clipboard
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
	ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0Bmp\0*.bmp\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetSaveFileName(&ofn) == TRUE)
	{
		hf = CreateFile(ofn.lpstrFile, GENERIC_READ, 0,	(LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING,	FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL);
		char arrPath[220] = "";
		CString strPath = ofn.lpstrFile;
		USES_CONVERSION;
		m_strFilePath = W2A(strPath.GetBuffer());
	}
}


void CChildView::OnFileSaveWnd()
{
	// TODO: Add your command handler code here

	// 调用方法  
	HWND hWnd = ::FindWindow(NULL, _T("Panel"));
	if (hWnd)
	{
		if (m_strFilePath == "")
			GetSavePath();
		wchar_t *lpstr1 = new wchar_t[2048];
		m_strFilePath += ".bmp";
		MultiByteToWideChar(0, 0, m_strFilePath.c_str(), -1, lpstr1, 2048);
		SaveHwndToBmpFile(hWnd, lpstr1);
	}
}
//下面重要的就是获取不同图片格式的CLSID，看下面代码：
int GetEncoderClsid(const TCHAR* format, CLSID* pClsid)
{
	UINT num = 0;
	UINT size = 0;
	ImageCodecInfo* pImageCodecInfo = NULL;

	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	GetImageEncodersSize(&num, &size);
	if (size == 0)
	{
		return -1;
	}

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
	{
		return -1;
	}

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (_tcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);

			return j;
		}
	}
	free(pImageCodecInfo);
	GdiplusShutdown(gdiplusToken);
	return -1;
}

// 创建位图文件  
BOOL SaveBitmap(BYTE *pBuffer, long lBufferLen)
{
	//第一个帖子
	//HANDLE hf = CreateFile(m_szFileName, GENERIC_WRITE,
	//	FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	//if (hf == INVALID_HANDLE_VALUE) return 0;
	//// 写文件头  
	//BITMAPFILEHEADER fileheader;
	//ZeroMemory(&fileheader, sizeof(BITMAPFILEHEADER));
	//fileheader.bfType = 'MB';
	//fileheader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + lBufferLen;
	//fileheader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	//DWORD dwWritter = 0;
	//WriteFile(hf, &fileheader, sizeof(BITMAPFILEHEADER), &dwWritter, NULL);
	//// 写文图格式  
	//BITMAPINFOHEADER infoHeader;
	//ZeroMemory(&infoHeader, sizeof(BITMAPINFOHEADER));
	//infoHeader.biSize = sizeof(BITMAPINFOHEADER);
	//infoHeader.biSizeImage = lBufferLen;
	//infoHeader.biWidth = lWidth;
	//infoHeader.biHeight = lHeight;
	//infoHeader.biBitCount = 24;
	//WriteFile(hf, &infoHeader, sizeof(BITMAPINFOHEADER), &dwWritter, NULL);
	//// 写位图数据  
	//WriteFile(hf, pBuffer, lBufferLen, &dwWritter, NULL);
	//CloseHandle(hf);
	//MessageBox(NULL, _T("Save bmp file succeed!"), _T("warn"), MB_OK | MB_ICONINFORMATION);

	//第二个帖子
	//////////////////////////////////////////////////////////////////
	//Function Name : BOOL WndToBmpFile(CDC *pDC, CString szFile)
	//	Parameters :
	//	CDC *pDC : is pointer to window DC whose image should be
	//	captured.
	//	CString szFile : is null terminated string with that name Bmp
	//	file should be saved.
	//	//////////////////////////////////////////////////////////////////

	//	//it will capture a wnd image and save it into a bmp file

	//	BOOL WndToBmpFile(CDC *pDC, CString szFile)
	//{
	//	//it will capture a wnd image and save it into a bmp file

	//	CString fname = szFile;
	//	CBitmap bmp, *pOldBmp;
	//	CRect rect;
	//	CWnd *pWnd;
	//	BOOL flg = 0;
	//	CPalette pal;
	//	LOGPALETTE *pLp;

	//	if (pDC == NULL)               //if pDC is NULL return
	//	{
	//		return FALSE;
	//	}

	//	pWnd = pDC->GetWindow();      //Get Window of PDC

	//	pWnd->GetClientRect(&rect); //Get dimension of Window

	//	if (fname.IsEmpty())
	//		return FALSE;

	//	CDC memdc;

	//	memdc.CreateCompatibleDC(pDC);  //Make Compatible DC for memdc
	//	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	//	//Create Compatible DDB
	//	pOldBmp = memdc.SelectObject(&bmp);
	//	memdc.BitBlt(0, 0, rect.Width(), rect.Height(), pDC, 0, 0, SRCCOPY);

	//	//The following code will detect whether the BMP uses a Raster
	//	//palette or not.

	//	if (pDC->GetDeviceCaps(RASTERCAPS) & RC_PALETTE)
	//	{
	//		int nSize;
	//		nSize = sizeof(LOGPALETTE) + sizeof(PALETTEENTRY) * 256;
	//		pLp = (LOGPALETTE*) new BYTE[nSize];
	//		pLp->palVersion = 0x300;
	//		pLp->palNumEntries = GetSystemPaletteEntries(
	//			pDC->m_hDC, 0, 255, pLp->palPalEntry);
	//		pal.CreatePalette(pLp);

	//		delete[] pLp;
	//	}
	//	memdc.SelectObject(pOldBmp);

	//	//will convert bitmap from DDB to DIB see DDBToDIB()
	//	// See DDBToDIB function for more..

	//	HANDLE hDIB = DDBToDIB(bmp, BI_RGB, &pal);
	//	if (hDIB == NULL)
	//		return FALSE;

	//	//*************************************
	//	//This code writes the BMP file

	//	CFile m_file;
	//	if (!m_file.Open(fname, CFile::modeWrite |
	//		CFile::modeCreate, NULL))
	//		return FALSE;
	//	BITMAPFILEHEADER hdr;
	//	LPBITMAPINFOHEADER lpbi;
	//	lpbi = (LPBITMAPINFOHEADER)hDIB;
	//	int nColors = 1 << lpbi->biBitCount;
	//	hdr.bfType = ((WORD)('M' << 8) | 'B');
	//	hdr.bfSize = sizeof(hdr) + GlobalSize(hDIB);
	//	hdr.bfReserved1 = 0;
	//	hdr.bfReserved2 = 0;
	//	hdr.bfOffBits = (DWORD) sizeof(hdr) + nColors * sizeof(RGBQUAD);
	//	m_file.Write(&hdr, sizeof(hdr));
	//	m_file.Write(lpbi, GlobalSize(hDIB));
	//	m_file.Close();
	//	//**************************************

	//	//This is the tricky part of the code. It will open the BMP file
	//	//again, but in Binary Mode. Then, it will read the first 14
	//	//bytes from the bitmap file.
	//	//It will change the 11th byte from 11 to 36.
	//	//It will change the 14th byte from 4 to 0 because this is the
	//	//basic requirement for the bitmap format.
	//	//So, it will support all PaintBrush Tools and thumbnail views
	//	//of Windows Explorer.

	//	CBinFile  m_tempFile;    //CBinFile is derived from CFile
	//	BYTE dummy = 0;//14        //14
	//	BYTE pBuf[14];           //11

	//	BOOL fres = m_tempFile.Open(fname, CFile::modeReadWrite |
	//		CFile::typeBinary);

	//	if (fres == 0)
	//		return FALSE;

	//	UINT tt = m_tempFile.Read(pBuf, 14);
	//	pBuf[13] = dummy;//will replace from 04 to 00
	//	m_tempFile.SeekToBegin();
	//	m_tempFile.Write(pBuf, 14);

	//	m_tempFile.Close();


	//	return flg;

	//	//it will capture wnd and save into a bmp file
	//	//End of the code

	//}

	////////////////////////////////////////////////////////////////////
	//Function Name : HANDLE DDBToDIB(CBitmap &bitmap,
	//	DWORD dwCompression,
	//	CPalette *pPal)
	//	Parameters :
	//	CBitmap &bitmap : Compatible Device Dependent Bitmap
	//	DWORD dwCompression : Compression format for Bitmap must not be
	//	BI_BITFIELDS in this case.
	//	CPalette *pPal: Pointer to Palette.If this is NULL, the
	//	default system palette will be used.

	//	//////////////////////////////////////////////////////////////////
	//	HANDLE DDBToDIB(CBitmap &bitmap, DWORD dwCompression,
	//		CPalette *pPal)
	//{

	//	BITMAP              bm;
	//	BITMAPINFOHEADER    bi;
	//	LPBITMAPINFOHEADER  lpbi;
	//	DWORD               dwLen;
	//	HANDLE              hDIB;
	//	HANDLE              handle;
	//	HDC                 hDC;
	//	HPALETTE            hPal;


	//	ASSERT(bitmap.GetSafeHandle());

	//	// The function has no arg for bitfields
	//	if (dwCompression == BI_BITFIELDS)
	//		return NULL;

	//	// If a palette has not been supplied, use default palette
	//	hPal = (HPALETTE)pPal->GetSafeHandle();
	//	if (hPal == NULL)
	//		hPal = (HPALETTE)GetStockObject(DEFAULT_PALETTE);

	//	// Get bitmap information
	//	bitmap.GetObject(sizeof(bm), (LPSTR)&bm);

	//	// Initialize the bitmap infoheader
	//	bi.biSize = sizeof(BITMAPINFOHEADER);
	//	bi.biWidth = bm.bmWidth;
	//	bi.biHeight = bm.bmHeight;
	//	bi.biPlanes = 1;
	//	bi.biBitCount = bm.bmPlanes * bm.bmBitsPixel;
	//	//bm.bmPlanes    * bm.bmBitsPixel;
	//	bi.biCompression = dwCompression;
	//	bi.biSizeImage = 0;
	//	bi.biXPelsPerMeter = 0;
	//	bi.biYPelsPerMeter = 0;
	//	bi.biClrUsed = 0;
	//	bi.biClrImportant = 0;

	//	// Compute the size of the infoheader and the color table
	//	int nColors = (1 << bi.biBitCount);
	//	if (nColors > 256)
	//		nColors = 0;
	//	dwLen = bi.biSize + nColors * sizeof(RGBQUAD);

	//	// We need a device context to get the DIB from
	//	hDC = ::GetDC(NULL);
	//	hPal = SelectPalette(hDC, hPal, FALSE);
	//	RealizePalette(hDC);

	//	// Allocate enough memory to hold bitmap infoheader and
	//	// color table
	//	hDIB = GlobalAlloc(GMEM_FIXED, dwLen);

	//	if (!hDIB) {
	//		SelectPalette(hDC, hPal, FALSE);
	//		::ReleaseDC(NULL, hDC);
	//		return NULL;
	//	}

	//	lpbi = (LPBITMAPINFOHEADER)hDIB;

	//	*lpbi = bi;

	//	// Call GetDIBits with a NULL lpBits param, so the device
	//	// driver will calculate the biSizeImage field
	//	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L,
	//		(DWORD)bi.biHeight,
	//		(LPBYTE)NULL, (LPBITMAPINFO)lpbi,
	//		(DWORD)DIB_RGB_COLORS);

	//	bi = *lpbi;

	//	// If the driver did not fill in the biSizeImage field, then
	//	// compute it
	//	// Each scan line of the image is aligned on a DWORD (32bit)
	//	// boundary
	//	if (bi.biSizeImage == 0) {
	//		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31)
	//			& ~31) / 8) * bi.biHeight;

	//		// If a compression scheme is used, the result may in fact
	//		// be larger
	//		// Increase the size to account for this.
	//		if (dwCompression != BI_RGB)
	//			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	//	}

	//	// Realloc the buffer so that it can hold all the bits
	//	dwLen += bi.biSizeImage;
	//	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
	//		hDIB = handle;
	//	else {
	//		GlobalFree(hDIB);

	//		// Reselect the original palette
	//		SelectPalette(hDC, hPal, FALSE);
	//		::ReleaseDC(NULL, hDC);
	//		return NULL;
	//	}

	//	// Get the bitmap bits
	//	lpbi = (LPBITMAPINFOHEADER)hDIB;

	//	// FINALLY get the DIB
	//	BOOL bGotBits = GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(),
	//		0L,                        // Start scan line
	//		(DWORD)bi.biHeight,        // # of scan lines
	//		(LPBYTE)lpbi               // address for bitmap bits
	//		+ (bi.biSize + nColors * sizeof(RGBQUAD)),
	//		(LPBITMAPINFO)lpbi,        // address of bitmapinfo
	//		(DWORD)DIB_RGB_COLORS);    // Use RGB for color table

	//	if (!bGotBits)
	//	{
	//		GlobalFree(hDIB);

	//		SelectPalette(hDC, hPal, FALSE);
	//		::ReleaseDC(NULL, hDC);
	//		return NULL;
	//	}

	//	SelectPalette(hDC, hPal, FALSE);
	//	::ReleaseDC(NULL, hDC);

	//	return hDIB;

	//	//End of the function
	//}

	//第三个帖子
	/*

// Setup bmpinfo structure yourself
  m_bmpinfo=new BITMAPINFO;    // PBITMAPINFO *m_bmpinfo;
//  m_bmpinfo->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
  m_bmpinfo->bmiHeader.biSize=sizeof(BITMAPINFO);
  m_bmpinfo->bmiHeader.biWidth=IMG_WIDTH;
  m_bmpinfo->bmiHeader.biHeight=IMG_HEIGHT;
  m_bmpinfo->bmiHeader.biPlanes=1;
  m_bmpinfo->bmiHeader.biBitCount=24;
  m_bmpinfo->bmiHeader.biCompression=0;
  m_bmpinfo->bmiHeader.biSizeImage=0;
  m_bmpinfo->bmiHeader.biXPelsPerMeter=0;
  m_bmpinfo->bmiHeader.biYPelsPerMeter=0;
  m_bmpinfo->bmiHeader.biClrUsed=0;
  m_bmpinfo->bmiHeader.biClrImportant=0;

//-------------在内存中绘制位图头信息-----------------------------------------------------------------------------------

// Initialize DIB for drawing...
 hdib=::DrawDibOpen();    // HDRAWDIB hdib;
 if(hdib!=NULL)
 {

  ::DrawDibBegin(hdib,
		m_hdc,
		-1,    // don't stretch
		-1,    // don't stretch
		&m_bmpinfo->bmiHeader,
		IMG_WIDTH,         // width of image
		IMG_HEIGHT,        // height of image
		0
		);
 }

//---------------绘制位图数据 buf--------------char* buf--------------------------------------------------------------------

 ::DrawDibDraw(hdib,
	  m_hdc,
	  local_wnd_x,  // dest : left pos
	  local_wnd_y,  // dest : top pos
	  -1,      // -1 don't zoom x
	  -1,      // -1 don't zoom y
	  &m_bmpinfo->bmiHeader, // bmp header info
	  buf,      // bmp data
	  0,      // src :left
	  0,      // src :top
	  IMG_WIDTH,     // src : width
	  IMG_HEIGHT,     // src : height
	  DDF_SAME_DRAW    // use prev params....
	  );
//------------------------------结束绘制---------------------------------------------------------------------

 // Close graphics....
 if(hdib!=NULL)
 {
 ::DrawDibEnd(hdib);
 ::DrawDibClose(hdib);
 }

 //第二种方法
 BITMAPINFO *m_bmphdr;
 DWORD dwBmpHdr = sizeof(BITMAPINFO);
 m_bmphdr = new BITMAPINFO[dwBmpHdr];
 m_bmphdr->bmiHeader.biBitCount = 24;
 m_bmphdr->bmiHeader.biClrImportant = 0;
 m_bmphdr->bmiHeader.biSize = dwBmpHdr;
 m_bmphdr->bmiHeader.biSizeImage = 0;
 m_bmphdr->bmiHeader.biWidth = IMG_WIDTH;
 m_bmphdr->bmiHeader.biHeight = IMG_HEIGHT;
 m_bmphdr->bmiHeader.biXPelsPerMeter = 0;
 m_bmphdr->bmiHeader.biYPelsPerMeter = 0;
 m_bmphdr->bmiHeader.biClrUsed = 0;
 m_bmphdr->bmiHeader.biPlanes = 1;
 m_bmphdr->bmiHeader.biCompression = BI_RGB;

 int nResult = ::StretchDIBits(m_hdc,
 local_wnd_x,
 local_wnd_y,
 IMG_WIDTH,//rc.right - rc.left,
 IMG_HEIGHT,//rc.top,
 0, 0,
 IMG_WIDTH, IMG_HEIGHT,
 buf,
 m_bmphdr,
 DIB_RGB_COLORS,
 SRCCOPY);
	*/

/*
第三个帖子
方法一：将内存设备描述表copy到位图中获取位图句柄
HDC hScrDC,hMemDC;//屏幕和内存设备描述表
HBITMAP hBitmap,hOldBitmap;//位图句柄
if(IsRectEmpty(rect)) return NULL;
//为屏幕创建设备描述表
//hScrDC=CreateCompatibleDC(NULL);
//hScrDC=::GetDC(this->m_hWnd);
hScrDC=GetWindowDC()->GetSafeHdc();
//为屏幕设备描述表创建兼容的内存设备描述表
hMemDC=CreateCompatibleDC(hScrDC);
//创建一个与屏幕设备描述表兼容的位图
hBitmap=CreateCompatibleBitmap(hScrDC,rect.Width(),rect.Height());
//把新位衅选到内存设备描述表中
hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
//把屏幕设备描述表拷贝到内存设备描述表中
BitBlt(hMemDC,-2,-2,rect.Width(),rect.Height(),hScrDC,0,0,SRCCOPY);
//得到屏幕位图句柄
hBitmap=(HBITMAP)SelectObject(hMemDC,hOldBitmap);
DeleteDC(hScrDC);
DeleteDC(hMemDC);
return hBitmap;

方法二：针对于vc6.0

http://blog.csdn.net/wltg2001/archive/2008/04/17/2300258.aspx这个主要分两个部分，一个是拷屏，一个是保存为BMP
第一部分大致代码如下：
CDC   dc;
dc.CreateDC( "DISPLAY ",NULL,NULL,NULL);
CBitmap   bm;
int   Width=GetSystemMetrics(SM_CXSCREEN);
int   Height=GetSystemMetrics(SM_CYSCREEN);
bm.CreateCompatibleBitmap(&dc,Width,Height);
CDC   tdc;
tdc.CreateCompatibleDC(&dc);
CBitmap*pOld=tdc.SelectObject(&bm);
tdc.BitBlt(0,0,Width,Height,&dc,0,0,SRCCOPY);
tdc.SelectObject(pOld);
此时CBitmap bm就是屏幕位图了。
第二步是将HBITMAP保存为BMP文件，看一下这个：参考

方法三：用gdi+
CDC *pDC = GetWindowDC();

CDC  memDC;

memDC.CreateCompatibleDC(pDC)  ;

CRect rt;

GetWindowRect(&rt);

CBitmap Bmp;

Bmp.CreateCompatibleBitmap(pDC,rt.Width(), rt.Height())  ;

CBitmap *pBmpPrev   =   (CBitmap*)memDC.SelectObject(&Bmp)   ;

memDC.BitBlt(0,   0,   rt.Width(),   rt.Height(),   pDC,   0,   0,   SRCCOPY);

CImage image;

image.Attach((HBITMAP)Bmp.m_hObject);

image.Save(L"c:\\1.bmp");
*/
	return 0;
}

void CChildView::OnFileSaveview()
{
	// TODO: Add your command handler code here
	HDC hdc;
	hdc = ::GetDC(m_hWnd);
	HDC hmemDC = ::CreateCompatibleDC(hdc);

	CRect destRect;
	GetClientRect(&destRect);

	//CDC *pDC = GetWindowDC();
	/*CClientDC dc(this);*/
	CDC *pDC = CWnd::GetDC();
	if (pDC->IsPrinting())
	{
		long width = 0, height = 0;
		int   xLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSX);
		int   yLogPixPerInch = pDC->GetDeviceCaps(LOGPIXELSY);
		//得到设备坐标和逻辑坐标的比例
		long   xExt = (long)destRect.Width() * xLogPixPerInch / 96;
		long   yExt = (long)destRect.Height() * yLogPixPerInch / 96;
		width = xExt;
		height = yExt;

		//后面使用GDI+进行绘图
		HBITMAP hBmp = ::CreateCompatibleBitmap(hdc, destRect.Width(), destRect.Height());
		HANDLE hOld = ::SelectObject(hmemDC, hBmp);
		Graphics graphic(hmemDC);

		//获取纸张的大小，然后拉伸拷贝
		int iPageWidth = pDC->GetDeviceCaps(HORZRES);
		int iPageHeight = pDC->GetDeviceCaps(VERTRES);
		::StretchBlt(pDC->m_hDC, 0, 0, iPageWidth, iPageHeight, hmemDC, 0, 0, width, height, SRCCOPY);    ::SelectObject(hmemDC, hOld);

		//下面进行各种文字、图形、图片的绘制
		Bitmap bitmap(hBmp, NULL);
		CLSID clsID;

		//保存不同格式的(.jpg,bmp,png)的图片需要不同的CLSID, imageFormat为用户期望保存的图片格式
		CString imageFormat = _T("E:\\vsproj\\3DGameParser\\Panel\\view.bmp");
		CString str = _T("bmp");
		if (_T("jpg") == str.MakeLower())
		{
			GetEncoderClsid(_T("image/jpeg"), &clsID);
		}
		else if (_T("bmp") == str.MakeLower())
		{
			GetEncoderClsid(_T("image/bmp"), &clsID);
		}
		else if (_T("png") == str.MakeLower())
		{
			GetEncoderClsid(_T("image/png"), &clsID);
		}

		//保存为图片，strFN为图片保存的路径和文件名
		bitmap.Save(imageFormat, &clsID, NULL);
		::SelectObject(hmemDC, hOld);
		::DeleteObject(hBmp);
		::DeleteDC(hmemDC);
	}
}
