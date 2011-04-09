#if !defined(AFX_SPLINE3DLG_H__BD5B0125_86F4_47DB_8D9E_6954EB0ECC84__INCLUDED_)
#define AFX_SPLINE3DLG_H__BD5B0125_86F4_47DB_8D9E_6954EB0ECC84__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Spline3Dlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpline3Dlg dialog

class CSpline3Dlg : public CDialog
{
// Construction
public:
	CSpline3Dlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSpline3Dlg)
	enum { IDD = IDD_SPLINE3 };
	CString	m_strResult;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpline3Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpline3Dlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLINE3DLG_H__BD5B0125_86F4_47DB_8D9E_6954EB0ECC84__INCLUDED_)
