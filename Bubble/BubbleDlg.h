
// BubbleDlg.h : header file
//

#pragma once


// CBubbleDlg dialog
class CBubbleDlg : public CDialogEx
{
// Construction
public:
	CBubbleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUBBLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	//virtual BOOL PreTranslateMessage(MSG* pMsg);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);

	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);

	void ShowPicture();

	void DeleteTray();

	void ToTray();

	afx_msg LRESULT OnNcHitTest(CPoint point);
	DECLARE_MESSAGE_MAP()
};
