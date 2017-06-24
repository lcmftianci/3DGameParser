
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Panel.h"
#include "ChildView.h"
#include "PenWidth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_strFilePath = "";
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
	ON_COMMAND(ID_FILE_SAVE32773, &CChildView::OnFileSave32773)
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
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_OldPoint = point;
	m_Point = point;
	m_bDraw = TRUE;
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_bDraw = FALSE;
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
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
	}
	dc.SelectObject(OldPen);
}



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
	ofn.lpstrFilter = _T("All\0*.*\0Text\0*.TXT\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box. 

	if (GetOpenFileName(&ofn) == TRUE)
	{
		hf = CreateFile(ofn.lpstrFile, GENERIC_READ, 0,	(LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING,	FILE_ATTRIBUTE_NORMAL,(HANDLE)NULL);
		char arrPath[220] = "";
		CString strPath = ofn.lpstrFile;

		//sprintf(arrPath, "%s", ofn.lpstrFile);
		//m_strFilePath = ofn.lpstrFile->GetBuffer(0);
		//MultiByteToWideChar(CP_ACP, 0, ofn.lpstrFile, -1, nid.szTip, 128);
		//m_strFilePath = arrPath;
	}
}


void CChildView::OnFileSave32773()
{
	// TODO: Add your command handler code here

	// 调用方法  
	HWND hWnd = ::FindWindow(NULL, _T("Panel"));
	if (hWnd)
	{
		if (m_strFilePath == "")
			GetSavePath();
		SaveHwndToBmpFile(hWnd, _T("F://12.bmp"));
	}

}
