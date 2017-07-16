
// ScreenCaptureDlg.h : header file
//

#pragma once
#include "ScreenUtil.h"


// CScreenCaptureDlg dialog
class CScreenCaptureDlg : public CDialogEx
{
// Construction
public:
	CScreenCaptureDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREENCAPTURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CMenu m_Menu;
	CaptureData m_CapData;

private:
	CImage	m_image;
public:
	void SetImage(const CString &strPath);


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCap();
};
