// ComplexCalculatorDlg.h : header file
//

#if !defined(AFX_COMPLEXCALCULATORDLG_H__41A4FC3B_798C_42B2_ABF2_12311F809ABF__INCLUDED_)
#define AFX_COMPLEXCALCULATORDLG_H__41A4FC3B_798C_42B2_ABF2_12311F809ABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CComplexCalculatorDlg dialog

class CComplexCalculatorDlg : public CDialog
{
// Construction
public:
	CComplexCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CComplexCalculatorDlg)
	enum { IDD = IDD_COMPLEXCALCULATOR_DIALOG };
	double	m_dblA;
	double	m_dblB;
	double	m_dblC;
	double	m_dblD;
	CString	m_strResult;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComplexCalculatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CComplexCalculatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton6();
	afx_msg void OnButton5();
	afx_msg void OnButton10();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPLEXCALCULATORDLG_H__41A4FC3B_798C_42B2_ABF2_12311F809ABF__INCLUDED_)
