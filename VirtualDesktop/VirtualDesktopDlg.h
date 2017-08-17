
// VirtualDesktopDlg.h : header file
//

#pragma once

#define  WM_SHOWTASK  WM_USER+100		//托盘消息


// CVirtualDesktopDlg dialog
class CVirtualDesktopDlg : public CDialogEx
{
// Construction
public:
	CVirtualDesktopDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIRTUALDESKTOP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFO StartupInfo;
	HDESK hDesktop;
	HDESK hOriginalThread;
	HDESK hOriginalInput;
	//Desktop m_desk;
	BOOL IsOriginalDesktopActive; //是否在原始桌面rz  
	BOOL IsInitialDesktop; //是否初始化桌面，防止灰色按钮克星造成不可估计的后果  
	BOOL IsWindowShow; //程序是否可见  


protected:
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);//自定义热键消息  
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

public:
	//变量 托盘结构体的变量
	NOTIFYICONDATA m_nid;
	//初始化上述变量的函数
	void ToTray(void);
	//托盘的消息处理函数
	LRESULT onShowTask(WPARAM wParam, LPARAM lParam);
};
