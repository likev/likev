// Interpolater.h : main header file for the INTERPOLATER application
//

#if !defined(AFX_INTERPOLATER_H__A067F9A3_B050_4879_A645_9E6AB2B00B3D__INCLUDED_)
#define AFX_INTERPOLATER_H__A067F9A3_B050_4879_A645_9E6AB2B00B3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CInterpolaterApp:
// See Interpolater.cpp for the implementation of this class
//

class CInterpolaterApp : public CWinApp
{
public:
	CInterpolaterApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterpolaterApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInterpolaterApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERPOLATER_H__A067F9A3_B050_4879_A645_9E6AB2B00B3D__INCLUDED_)
