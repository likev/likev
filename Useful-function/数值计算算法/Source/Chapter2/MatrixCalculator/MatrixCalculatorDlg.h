// MatrixCalculatorDlg.h : header file
//

#if !defined(AFX_MATRIXCALCULATORDLG_H__7B713C6A_2298_49AA_9899_3C8C4CC9F085__INCLUDED_)
#define AFX_MATRIXCALCULATORDLG_H__7B713C6A_2298_49AA_9899_3C8C4CC9F085__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMatrixCalculatorDlg dialog

class CMatrixCalculatorDlg : public CDialog
{
// Construction
public:
	CMatrixCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMatrixCalculatorDlg)
	enum { IDD = IDD_MATRIXCALCULATOR_DIALOG };
	CString	m_strMatrix1;
	CString	m_strMatrix2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatrixCalculatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CString	m_strMatrix3;

	// Generated message map functions
	//{{AFX_MSG(CMatrixCalculatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton10();
	afx_msg void OnButton11();
	afx_msg void OnButton12();
	afx_msg void OnButton13();
	afx_msg void OnButton14();
	afx_msg void OnButton15();
	afx_msg void OnButton16();
	afx_msg void OnButton17();
	afx_msg void OnButton18();
	afx_msg void OnButton19();
	afx_msg void OnButton20();
	afx_msg void OnButton21();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATRIXCALCULATORDLG_H__7B713C6A_2298_49AA_9899_3C8C4CC9F085__INCLUDED_)
