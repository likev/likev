// LECalculator.h : main header file for the LECALCULATOR application
//

#if !defined(AFX_LECALCULATOR_H__6F7D3B03_1C93_4481_A652_3620DE121C11__INCLUDED_)
#define AFX_LECALCULATOR_H__6F7D3B03_1C93_4481_A652_3620DE121C11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLECalculatorApp:
// See LECalculator.cpp for the implementation of this class
//

class CLECalculatorApp : public CWinApp
{
public:
	CLECalculatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLECalculatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLECalculatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LECALCULATOR_H__6F7D3B03_1C93_4481_A652_3620DE121C11__INCLUDED_)
