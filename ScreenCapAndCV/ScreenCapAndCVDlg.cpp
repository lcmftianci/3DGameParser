
// ScreenCapAndCVDlg.cpp : implementation file
//
#include "stdafx.h"
#include "ScreenCapAndCV.h"
#include "ScreenCapAndCVDlg.h"
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_SHOW 0X6000

//线程声明
DWORD WINAPI ThreadB1(LPVOID lpParam);

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScreenCapAndCVDlg dialog



CScreenCapAndCVDlg::CScreenCapAndCVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCREENCAPANDCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bCapture = false;
}

void CScreenCapAndCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenCapAndCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_MESSAGE(WM_MY_MESSAGE, OnMyMessage)
	ON_COMMAND(ID_CAPPICACTIVE, &CScreenCapAndCVDlg::OnCappicactive)
	ON_COMMAND(ID_CAPPICDESK, &CScreenCapAndCVDlg::OnCappicdesk)
	ON_COMMAND(ID_CAPVIDEO, &CScreenCapAndCVDlg::OnCapvideo)
	ON_COMMAND(ID_STOPVIDEO, &CScreenCapAndCVDlg::OnStopvideo)
	ON_COMMAND(ID_STARTVDEO, &CScreenCapAndCVDlg::OnStartvdeo)
END_MESSAGE_MAP()


// CScreenCapAndCVDlg message handlers

BOOL CScreenCapAndCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//添加Menu
	m_Menu.LoadMenu(IDR_MENU1);  //  IDR_MENU1为你加入的菜单的ID，在Resource视图的Menu文件夹下可以找到
	SetMenu(&m_Menu);

	hAccel = ::LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_ACCELERATOR1));
	m_nHotKey = GlobalAddAtom(L"MyHotKey") - 0xC000;
	::RegisterHotKey(this->GetSafeHwnd(), ID_SHOW, MOD_ALT, 'S');
	//::RegisterHotKey(this->GetSafeHwnd(), ID_EXIT, MOD_CONTROL, 'E');
	RegisterHotKey(NULL, m_nHotKey, MOD_ALT/* | MOD_NOREPEAT*/, VK_F8);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScreenCapAndCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CScreenCapAndCVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//双缓存绘制防闪烁
		CPaintDC dc(this); // device context for painting
		CDC MemDC;
		CBitmap   MemBitmap;//定义一个位图对象
		MemDC.CreateCompatibleDC(NULL);
		if (m_image.IsNull())
			return;
		CRect rect;
		GetClientRect(rect);
		MemBitmap.CreateCompatibleBitmap(GetDC(), rect.Width(), rect.Height());
		CBitmap   *pOldBit = MemDC.SelectObject(&MemBitmap);
		MemDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

		MemDC.SetStretchBltMode(HALFTONE);
		m_image.StretchBlt(MemDC, rect);

		GetDC()->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScreenCapAndCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI ThreadB1(LPVOID lpParam)
{
	//// 定义结构对象  
	//PROCESS_INFORMATION pi;
	//STARTUPINFO         si;
	//BOOL                bRet;
	//// 申请空间  
	//ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	//ZeroMemory(&si, sizeof(STARTUPINFO));
	//// 设置进程启动属性  
	//si.cb = sizeof(STARTUPINFO);
	//si.lpReserved = NULL;
	//si.lpDesktop = NULL;
	//si.lpTitle = NULL;
	//si.dwFlags = STARTF_USESHOWWINDOW;
	//si.wShowWindow = SW_SHOWNORMAL;
	//si.cbReserved2 = NULL;
	//si.lpReserved2 = NULL;
	//bRet = CreateProcess(_T("C://Program Files//Internet Explorer//IEXPLORE.exe"),_T("http://www.coderfans.cn"),NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	//无用代码

	//多线程录屏功能
	//ShowWindow(SW_HIDE);
	//ShowWindow(SW_HIDE);
	int nParam1 = 0;
	int nParam2 = 0;
	MSG msg;
	CaptureData capData;
	while (!bFlag)
	{
		Sleep(50);//一秒钟20张图片
		ConfigureCapture(theApp.GetSafeHwnd(), &capData);
		CaptureScreen(&capData);
		//再循环的里边接受消息
		//PostMessage(WM_HOTKEY);
		//::PostMessage(GetSafeHwnd(), WM_MY_MESSAGE, 0, 0);
		//::PostMessage(GetSafeHwnd(), WM_MY_MESSAGE, (WPARAM)&nParam1, (LPARAM)&nParam2);
		SendMessage(WM_MY_MESSAGE, (WPARAM)&nParam1, (LPARAM)&nParam2);
	}
	//ShowWindow(SW_SHOW);
	bFlag = false;
	return 0;
}



void CScreenCapAndCVDlg::CapVideoFunction()
{
	//ShowWindow(SW_HIDE);
	int nParam1 = 0;
	int nParam2 = 0;
	MSG msg;
	CaptureData capData;
	while (!m_bCapture)
	{
		Sleep(50);//一秒钟20张图片
		ConfigureCapture(GetSafeHwnd(), &capData);
		CaptureScreen(&capData);
		//再循环的里边接受消息
		//PostMessage(WM_HOTKEY);
		//::PostMessage(GetSafeHwnd(), WM_MY_MESSAGE, 0, 0);
		//::PostMessage(GetSafeHwnd(), WM_MY_MESSAGE, (WPARAM)&nParam1, (LPARAM)&nParam2);
		SendMessage(WM_MY_MESSAGE, (WPARAM)&nParam1, (LPARAM)&nParam2);
	}
	//ShowWindow(SW_SHOW);
	m_bCapture = false;
}

PROC CScreenCapAndCVDlg::HotKeyDown(MSG Msg)
{
	if (Msg.lParam == MOD_ALT && Msg.wParam == VK_F8)
		m_bCapture = true;
	UnregisterHotKey(NULL, m_nHotKey);   //注销HotKey,   释放资源
	return NULL;
}

void CScreenCapAndCVDlg::OnCappicactive()
{
	// TODO: Add your command handler code here
	//ShowWindow(SW_HIDE);
	Sleep(500);
	ConfigureCapture(GetSafeHwnd(), &m_CapData);
	m_CapData.bCaptureFullScreen = false;
	CaptureScreen(&m_CapData);
	//ShowWindow(SW_SHOW);

	if (m_CapData.szCaptureFilename[0] != '\0') {
		// In a real application that had interest in the
		// actual image and not just a screen capture
		// we would want to pass the Bitmap/CImage back
		// and forth directly, but for screen capture
		// sample purposes, this works fine.
		CString strPathName(m_CapData.szCapturePath);
		if (strPathName.Right(1) != "\\")
			strPathName += '\\';
		strPathName += m_CapData.szCaptureFilename;
		SetImage(strPathName);
	}
}


//截取桌面
void CScreenCapAndCVDlg::OnCappicdesk()
{
	// TODO: Add your command handler code here
	ShowWindow(SW_HIDE);
	Sleep(500);
	ConfigureCapture(GetSafeHwnd(), &m_CapData);
	CaptureScreen(&m_CapData);
	ShowWindow(SW_SHOW);

	if (m_CapData.szCaptureFilename[0] != '\0') {
		// In a real application that had interest in the
		// actual image and not just a screen capture
		// we would want to pass the Bitmap/CImage back
		// and forth directly, but for screen capture
		// sample purposes, this works fine.
		CString strPathName(m_CapData.szCapturePath);
		if (strPathName.Right(1) != "\\")
			strPathName += '\\';
		strPathName += m_CapData.szCaptureFilename;
		SetImage(strPathName);
	}
}


//录制屏幕
void CScreenCapAndCVDlg::OnCapvideo()
{
	// TODO: Add your command handler code here
	DWORD   dw1, dw2;
	HANDLE hHandle;
	hHandle = CreateThread(NULL, 0, ThreadB1, NULL, 0, &dw1);
}

//停止录制屏幕，合成视频并播放
void CScreenCapAndCVDlg::OnStopvideo()
{
	// TODO: Add your command handler code here
	m_bCapture = true;
	bFlag = false;
}


//播放视频
void CScreenCapAndCVDlg::OnStartvdeo()
{
	// TODO: Add your command handler code here
	Mat img = imread("E:\\OpenCV3\\opencv\\sources\\samples\\data\\fruits.jpg");
	imshow("载入图片", img);
	waitKey(5000);
}

LRESULT CScreenCapAndCVDlg::OnHotKey(WPARAM wPARAM, LPARAM lPARAM)
{
	if (wPARAM == ID_SHOW)
	{
		m_bCapture = true;
		return S_OK;
	}
	return S_FALSE;
}

LRESULT CScreenCapAndCVDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	if (wParam == ID_SHOW)
	{
		m_bCapture = true;
		return S_OK;
	}
	return S_FALSE;
}

//设置图片
void CScreenCapAndCVDlg::SetImage(const CString &strPath)
{
	if (!m_image.IsNull())
		m_image.Destroy();

	HRESULT hr = m_image.Load(strPath);
	if (FAILED(hr)) {
		TRACE("Image Load Failed: %x\n", hr);
	}
	Invalidate();
}

BOOL CScreenCapAndCVDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)  //判断是否有按键按下     
	{
		switch (pMsg->wParam)
		{
		case VK_DOWN:     //表示是方向键中的向下的键               //add handle code here           
			break;
		case VK_UP:      //表示是方向键中的向上的键                //add handle code here           
			break;

		default:
			break;
		}
	}
	if (::TranslateAccelerator(GetSafeHwnd(), hAccel, pMsg))
		return   true;
}