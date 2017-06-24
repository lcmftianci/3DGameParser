#pragma once


// CPenWidth dialog

class CPenWidth : public CDialogEx
{
	DECLARE_DYNAMIC(CPenWidth)

public:
	CPenWidth(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPenWidth();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEN_WIDTH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
