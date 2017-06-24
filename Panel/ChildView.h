
// ChildView.h : interface of the CChildView class
//


#pragma once
#include <iostream>


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:
	void GetSavePath();
// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	CPoint m_OldPoint;
	CPoint m_Point;
	BOOL m_bDraw;
	COLORREF m_Color;
	std::string m_strFilePath;
public:
	afx_msg void OnToolsColor();
	afx_msg void OnToolsSize();
	afx_msg void OnFileSave32773();
};

