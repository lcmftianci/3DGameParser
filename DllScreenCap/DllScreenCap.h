// DllScreenCap.h : main header file for the DllScreenCap DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CDllScreenCapApp
// See DllScreenCap.cpp for the implementation of this class
//

class CDllScreenCapApp : public CWinApp
{
public:
	CDllScreenCapApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
