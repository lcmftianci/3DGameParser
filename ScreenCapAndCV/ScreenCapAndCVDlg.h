
// ScreenCapAndCVDlg.h : header file
//

#pragma once
#include "ScreenUtil.h"


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
public:
	afx_msg void OnCappicactive();
	afx_msg void OnCappicdesk();
	afx_msg void OnCapvideo();
	afx_msg void OnStopvideo();
	afx_msg void OnStartvdeo();
};
