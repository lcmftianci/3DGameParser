
// VirtualDesktopDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualDesktop.h"
#include "VirtualDesktopDlg.h"
#include "afxdialogex.h"
#include "gdiplus.h"

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CVirtualDesktopDlg dialog



CVirtualDesktopDlg::CVirtualDesktopDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIRTUALDESKTOP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVirtualDesktopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVirtualDesktopDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK, onShowTask)
	ON_MESSAGE(WM_HOTKEY, OnHotKey) //链接热键消息
	ON_BN_CLICKED(IDOK, &CVirtualDesktopDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CVirtualDesktopDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CVirtualDesktopDlg message handlers

BOOL CVirtualDesktopDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	//动态加载自己的图标
	////GdiplusStartupInput gdiplusStartInput;
	////ULONG_PTR gdiplusTocken;
	////GdiplusStartup(&gdiplusTocken, &gdiplusStartInput, NULL);
	////const WCHAR* pStr = L"F:\\迅雷下载\\开发文档\\yuzhu\\001.jpg";
	//////Gdiplus::Bitmap* pTmp = new Gdiplus::Bitmap(pStr);
	////Gdiplus::Bitmap* pTmp = Gdiplus::Bitmap::FromFile(pStr);
	////if (pTmp != NULL)
	////{
	////	HICON hIcon = NULL;
	////	pTmp->GetHICON(&hIcon);
	////	SetIcon(hIcon, FALSE);		// Set small icon
	////	CWnd* pMainWnd;
	////	pMainWnd = AfxGetMainWnd();
	////	pMainWnd->SetIcon(hIcon, TRUE);
	////}

	//GdiplusShutdown(gdiplusTocken);

	// TODO: Add extra initialization here
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW); //设置窗体样式为工具样式，这样任务栏就没有图标了  

	IsOriginalDesktopActive = FALSE;
	IsInitialDesktop = TRUE;
	IsWindowShow = TRUE;
	::RegisterHotKey(this->GetSafeHwnd(), 521, MOD_CONTROL, 'X'); //设置显示程序热键为 Win+X 

	ToTray();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVirtualDesktopDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVirtualDesktopDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVirtualDesktopDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CVirtualDesktopDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1314) //消息为 Alt+Z 时  
	{
		if (IsOriginalDesktopActive) //是否在原始桌面  
		{
// 			CWnd* hDeskWnd = GetDesktopWindow();
// 			hDeskWnd->ShowWindow(SW_HIDE);
// 			Sleep(5000);
// 			hDeskWnd->ShowWindow(SW_SHOW);
			hDesktop = CreateDesktopW(L"Virtual", NULL, NULL, 0, GENERIC_ALL, NULL); //创建虚拟桌面（与CloseDesktop相对应）  
			SetThreadDesktop(hDesktop);
			SwitchDesktop(hDesktop);
		}
		else
		{
			SetThreadDesktop(hOriginalThread);
			SwitchDesktop(hOriginalInput);
			CloseDesktop(hDesktop); //关闭虚拟桌面  
			//Sleep(5000);
		}
		IsOriginalDesktopActive = !IsOriginalDesktopActive;
	}
	if (wParam == 521)
	{
		if (IsWindowShow)
		{
			AnimateWindow(521, AW_BLEND | AW_HIDE);//隐藏窗口  
		}
		else
		{
			AnimateWindow(521, AW_BLEND);//显示窗口
		}
		IsWindowShow = !IsWindowShow;
	}

	return TRUE;
}



void CVirtualDesktopDlg::OnBnClickedOk()
{
	if (IsInitialDesktop) //第一次运行时初始化程序，加上判断防止灰色按钮克星  
	{
		//创建名称为“Virtual”的虚拟桌面  
		hDesktop = CreateDesktop("Virtual", NULL, NULL, 0, GENERIC_ALL, NULL);

		//初始化创建进程必须的结构体  
		ZeroMemory(&StartupInfo, sizeof(StartupInfo));
		ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
		StartupInfo.cb = sizeof(StartupInfo);
		StartupInfo.lpDesktop = "Virtual";

		//记录原始桌面的句柄  
		hOriginalThread = GetThreadDesktop(GetCurrentThreadId());
		hOriginalInput = OpenInputDesktop(0, FALSE, DESKTOP_SWITCHDESKTOP);

		//创建桌面外壳进程  
		CreateProcess(NULL, "explorer", NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo);

		//完成初始化，以后不会再次被调用，防止打开虚拟桌面出现资源管理器  
		IsInitialDesktop = !IsInitialDesktop;

		SetThreadDesktop(hDesktop); //设置桌面活动焦点是虚拟桌面  
		SwitchDesktop(hDesktop); //切换到虚拟桌面  

		GetDlgItem(IDOK)->EnableWindow(FALSE); //设置初始化按钮失效，只允许热键操作  
		RegisterHotKey(m_hWnd, 1314, MOD_CONTROL, 'Z'); //设置热键为 Alt+Z  
	}

	return;
	CDialog::OnOK();
}


void CVirtualDesktopDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//注销热键  
	UnregisterHotKey(m_hWnd, 1314);
	UnregisterHotKey(m_hWnd, 521);

	//关闭创建的explorer  
	if (!IsInitialDesktop)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessInfo.dwProcessId); //获取虚拟桌面的explorer句柄  
		if (hProcess)
		{
			TerminateProcess(hProcess, 1); //结束虚拟桌面的explorer  
		}
		CloseHandle(hProcess);
	}
	exit(0);
	CDialog::OnClose();
}

//初始化托盘程序
void CVirtualDesktopDlg::ToTray(void)
{
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;
	//自定义的消息名称 WM_SHOWTASK 头函数中定义为WM_USER+10
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	StrCpy(m_nid.szTip, "托盘图标");//当鼠标放在上面时，所显示的内容
	Shell_NotifyIcon(NIM_ADD, &m_nid);//在托盘区添加图标
}

LRESULT CVirtualDesktopDlg::onShowTask(WPARAM wParam, LPARAM lParam) //wParam接收的是图标的ID，lParam接收的是鼠标的行为
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
		case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭”
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);//得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();//声明一个弹出式菜单
									//增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已
									//隐藏），将程序结束。
			menu.AppendMenu(MF_STRING, WM_DESTROY, "退出");
			//确定弹出式菜单的位置
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
			//资源回收
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
		case WM_LBUTTONDBLCLK://双击左键的处理
		{
			this->ShowWindow(SW_SHOWNORMAL);//简单的显示主窗口
		}
		break;
		case WM_MOUSEMOVE:
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);//得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu();//声明一个弹出式菜单
								   //增加菜单项“关闭”，点击则发送消息WM_DESTROY给主窗口（已
								   //隐藏），将程序结束。
			menu.AppendMenu(MF_STRING, WM_DESTROY, "退出");
			menu.AppendMenu(MF_STRING, WM_DESTROY, "提示");
			menu.AppendMenu(MF_STRING, WM_DESTROY, "提示2");
			//确定弹出式菜单的位置
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
			//资源回收
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	}
	return 0;
}
