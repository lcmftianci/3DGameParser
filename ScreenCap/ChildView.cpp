
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "ScreenCap.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

void CChildView::SetImage(const CString &strPath)
{
	if (!m_image.IsNull())
		m_image.Destroy();

	HRESULT hr = m_image.Load(strPath);
	if (FAILED(hr)) {
		TRACE("Image Load Failed: %x\n", hr);
	}
	Invalidate();
}

// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	if (m_image.IsNull())
		return;
	CRect rect;
	GetClientRect(rect);
	// In a real app you would probably want to maintain aspect ratio.
	dc.SetStretchBltMode(HALFTONE);
	m_image.StretchBlt(dc, rect);
	// Do not call CWnd::OnPaint() for painting messages
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	if (m_image.IsNull())
		return(CWnd::OnEraseBkgnd(pDC));
	return(TRUE);
}


