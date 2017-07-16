
// ScreenCap.h : main header file for the ScreenCap application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CScreenCapApp:
// See ScreenCap.cpp for the implementation of this class
//

class CScreenCapApp : public CWinApp
{
public:
	CScreenCapApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CScreenCapApp theApp;
