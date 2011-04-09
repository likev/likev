// InterpolaterDlg.h : header file
//

#if !defined(AFX_INTERPOLATERDLG_H__89057718_661D_4360_A827_1749ED02F7D4__INCLUDED_)
#define AFX_INTERPOLATERDLG_H__89057718_661D_4360_A827_1749ED02F7D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInterpolaterDlg dialog

class CInterpolaterDlg : public CDialog
{
// Construction
public:
	CInterpolaterDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInterpolaterDlg)
	enum { IDD = IDD_INTERPOLATER_DIALOG };
	CString	m_strXi;
	CString	m_strYi;
	int		m_nNumNodes;
	int		m_nNumTargetNodes;
	CString	m_strTargetXi;
	CString	m_strStepOrBorderCondition;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterpolaterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CString	m_strTargetYi;

	// Generated message map functions
	//{{AFX_MSG(CInterpolaterDlg)
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERPOLATERDLG_H__89057718_661D_4360_A827_1749ED02F7D4__INCLUDED_)
