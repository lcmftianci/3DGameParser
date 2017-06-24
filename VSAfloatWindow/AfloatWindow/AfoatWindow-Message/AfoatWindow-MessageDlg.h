
// AfoatWindow-MessageDlg.h : header file
//

#pragma once


// CAfoatWindowMessageDlg dialog
class CAfoatWindowMessageDlg : public CDialogEx
{
// Construction
public:
	CAfoatWindowMessageDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_AFOATWINDOWMESSAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
    CBitmap  m_bmp;
    void SetupRegion(CDC *pDC,CBitmap &cBitmap,COLORREF TransColor);
};
