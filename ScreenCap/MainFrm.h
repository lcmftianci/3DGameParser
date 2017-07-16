
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ChildView.h"
extern "C"
{
#include "ScreenCapApi.h" 
}

// extern "C" _declspec(dllimport) BOOL ConfigureCapture(HWND hWndParent, CaptureData* lpData);
// extern "C" _declspec(dllimport) void CaptureScreen(CaptureData* lpData);

/*#include "ScreenCapApi.h"*/
class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;
	CChildView    m_wndView;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	DECLARE_MESSAGE_MAP()

public:
	void OnFileConfigureScreenCapture(void);
private:
	CaptureData m_CapData;
public:
	void OnFileScreencapture(void);
};


