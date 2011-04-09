#if !defined(AFX_IMAGDATADLG_H__2249F4A4_0CFC_4415_9EE8_5173D9809ECC__INCLUDED_)
#define AFX_IMAGDATADLG_H__2249F4A4_0CFC_4415_9EE8_5173D9809ECC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImagDataDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImagDataDlg dialog

class CImagDataDlg : public CDialog
{
// Construction
public:
	CImagDataDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImagDataDlg)
	enum { IDD = IDD_IMAG_DATA };
	CString	m_strCoefficient;
	CString	m_strConstant;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImagDataDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImagDataDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGDATADLG_H__2249F4A4_0CFC_4415_9EE8_5173D9809ECC__INCLUDED_)
