// ConvertToSPEX.h : main header file for the ConvertToSPEX application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CConvertToSPEXApp:
// See ConvertToSPEX.cpp for the implementation of this class
//

class CConvertToSPEXApp : public CWinApp
{
public:
	CConvertToSPEXApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnFileOpen();
};

extern CConvertToSPEXApp theApp;