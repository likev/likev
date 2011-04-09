// Sample.h : main header file for the SAMPLE application
//

#if !defined(AFX_SAMPLE_H__03BA4068_C4F7_4F51_B46F_45ABB75EC6AC__INCLUDED_)
#define AFX_SAMPLE_H__03BA4068_C4F7_4F51_B46F_45ABB75EC6AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSampleApp:
// See Sample.cpp for the implementation of this class
//

class CSampleApp : public CWinApp
{
public:
	CSampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLE_H__03BA4068_C4F7_4F51_B46F_45ABB75EC6AC__INCLUDED_)
