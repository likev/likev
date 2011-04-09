// ComplexCalculator.h : main header file for the COMPLEXCALCULATOR application
//

#if !defined(AFX_COMPLEXCALCULATOR_H__26CAE571_198C_4BCB_B6F9_5B0D04FBD9A4__INCLUDED_)
#define AFX_COMPLEXCALCULATOR_H__26CAE571_198C_4BCB_B6F9_5B0D04FBD9A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CComplexCalculatorApp:
// See ComplexCalculator.cpp for the implementation of this class
//

class CComplexCalculatorApp : public CWinApp
{
public:
	CComplexCalculatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComplexCalculatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CComplexCalculatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPLEXCALCULATOR_H__26CAE571_198C_4BCB_B6F9_5B0D04FBD9A4__INCLUDED_)
