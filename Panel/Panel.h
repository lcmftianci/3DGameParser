
// Panel.h : main header file for the Panel application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPanelApp:
// See Panel.cpp for the implementation of this class
//

class CPanelApp : public CWinApp
{
public:
	CPanelApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPanelApp theApp;
