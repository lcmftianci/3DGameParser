
// AfloatWindowDlg.h : header file
//

#pragma once


// CAfloatWindowDlg dialog
class CAfloatWindowDlg : public CDialogEx
{
// Construction
public:
	CAfloatWindowDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AFLOATWINDOW_DIALOG };

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
    afx_msg LRESULT OnNcHitTest(CPoint pt);
	DECLARE_MESSAGE_MAP()

private:
    void ShowPicture();

};
