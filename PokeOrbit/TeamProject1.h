
// TeamProject1.h : main header file for the TeamProject1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTeamProject1App:
// See TeamProject1.cpp for the implementation of this class
//


/**
 * Class that describes the app
 */
class CTeamProject1App : public CWinApp
{
public:
	CTeamProject1App();

/** \cond */
// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

private:
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
};

extern CTeamProject1App theApp;
/** \endcond */