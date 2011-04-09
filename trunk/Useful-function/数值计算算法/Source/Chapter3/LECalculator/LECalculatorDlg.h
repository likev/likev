// LECalculatorDlg.h : header file
//

#if !defined(AFX_LECALCULATORDLG_H__AC6A3159_31B4_4E07_850F_9FA7FC2D0651__INCLUDED_)
#define AFX_LECALCULATORDLG_H__AC6A3159_31B4_4E07_850F_9FA7FC2D0651__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CLECalculatorDlg dialog

class CLECalculatorDlg : public CDialog
{
// Construction
public:
	CLECalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CLECalculatorDlg)
	enum { IDD = IDD_LECALCULATOR_DIALOG };
	CString	m_strCoefficient;
	CString	m_strConstant;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLECalculatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CString m_strResult;

	// Generated message map functions
	//{{AFX_MSG(CLECalculatorDlg)
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LECALCULATORDLG_H__AC6A3159_31B4_4E07_850F_9FA7FC2D0651__INCLUDED_)
