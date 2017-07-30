
// ScreenCapAndCVDlg.h : header file
//

#pragma once
#include "ScreenUtil.h"
#include <iostream>
#include <vector>

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

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

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

	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg LRESULT OnMyCode(WPARAM wParam, LPARAM lParam);
public:
	void CapVideoFunction();

	//线程声明，全局或者静态成员才可以做线程函数
	static DWORD WINAPI ThreadB1(LPVOID lpParam);			//屏幕截图线程

	static DWORD WINAPI ThreadConvertVideo(LPVOID lpParam); //合成视频线程

protected:
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);

	virtual BOOL PreTranslateMessage(MSG *pMsg);

	int m_nHotKey;

private:
	bool m_bCapture; //截屏开始停止标识符
	HACCEL hAccel;

	std::vector<std::string> m_arrImgPath;//存储所有图片的文件路径用于合成视频用
};
