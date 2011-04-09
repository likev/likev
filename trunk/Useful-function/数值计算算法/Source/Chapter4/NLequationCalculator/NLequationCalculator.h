// NLequationCalculator.h : main header file for the NLEQUATIONCALCULATOR application
//

#if !defined(AFX_NLEQUATIONCALCULATOR_H__A0656DD8_45D1_4DC7_B08A_8817F0F4D8B9__INCLUDED_)
#define AFX_NLEQUATIONCALCULATOR_H__A0656DD8_45D1_4DC7_B08A_8817F0F4D8B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CNLequationCalculatorApp:
// See NLequationCalculator.cpp for the implementation of this class
//

class CNLequationCalculatorApp : public CWinApp
{
public:
	CNLequationCalculatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNLequationCalculatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNLequationCalculatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NLEQUATIONCALCULATOR_H__A0656DD8_45D1_4DC7_B08A_8817F0F4D8B9__INCLUDED_)
