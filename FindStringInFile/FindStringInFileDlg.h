
// FindStringInFileDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <iostream>
#include <vector>
using namespace std;


// CFindStringInFileDlg dialog
class CFindStringInFileDlg : public CDialogEx
{
// Construction
public:
	CFindStringInFileDlg(CWnd* pParent = NULL);	// standard constructor

public:
	//±éÀúÎÄ¼þ¼Ð
	void FindFile(string strFilePath);
	void InputArr(string strData);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINDSTRINGINFILE_DIALOG };
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
	afx_msg void OnBnClickedBtnPath();
	afx_msg void OnBnClickedFind();
	CEdit m_EditStr;
	CEdit m_EditPath;

	std::vector<string> m_arrNewStrPath;
	std::vector<string> m_arrFilePath;

	CString m_strFindPath;
	CString m_strFind;
};
