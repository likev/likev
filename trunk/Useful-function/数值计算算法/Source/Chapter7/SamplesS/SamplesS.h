// SamplesS.h : main header file for the SAMPLESS application
//

#if !defined(AFX_SAMPLESS_H__F1F04740_CD06_456F_A97C_BA992D125C6C__INCLUDED_)
#define AFX_SAMPLESS_H__F1F04740_CD06_456F_A97C_BA992D125C6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSamplesSApp:
// See SamplesS.cpp for the implementation of this class
//

class CSamplesSApp : public CWinApp
{
public:
	CSamplesSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSamplesSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSamplesSApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLESS_H__F1F04740_CD06_456F_A97C_BA992D125C6C__INCLUDED_)
