
// ScreenCapAndCVDlg.h : header file
//

#pragma once
#include "ScreenUtil.h"

#define WM_MY_MESSAGE (WM_USER+1000)


// CScreenCapAndCVDlg dialog
class CScreenCapAndCVDlg : public CDialogEx
{
// Construction
public:
	CScreenCapAndCVDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREENCAPANDCV_DIALOG };
#endif

private:
	CImage	m_image;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	void SetImage(const CString &strPath);

// Implementation
protected:
	HICON m_hIcon;
	CMenu m_Menu;
	CaptureData m_CapData;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	PROC HotKeyDown(MSG Msg);
public:
	afx_msg void OnCappicactive();
	afx_msg void OnCappicdesk();
	afx_msg void OnCapvideo();
	afx_msg void OnStopvideo();
	afx_msg void OnStartvdeo();
	afx_msg LRESULT OnHotKey(WPARAM wPARAM, LPARAM lPARAM);

public:
	void CapVideoFunction();

protected:
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);

	virtual BOOL PreTranslateMessage(MSG *pMsg);

	int m_nHotKey;

private:
	bool m_bCapture; //截屏开始停止标识符
	HACCEL hAccel;
};
