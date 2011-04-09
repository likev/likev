// NLequationCalculatorDlg.h : header file
//

#if !defined(AFX_NLEQUATIONCALCULATORDLG_H__CA75DFA1_47A9_4F2E_A563_5B09CF897061__INCLUDED_)
#define AFX_NLEQUATIONCALCULATORDLG_H__CA75DFA1_47A9_4F2E_A563_5B09CF897061__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNLequationCalculatorDlg dialog

class CNLequationCalculatorDlg : public CDialog
{
// Construction
public:
	CNLequationCalculatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CNLequationCalculatorDlg)
	enum { IDD = IDD_NLEQUATIONCALCULATOR_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNLequationCalculatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CNLequationCalculatorDlg)
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NLEQUATIONCALCULATORDLG_H__CA75DFA1_47A9_4F2E_A563_5B09CF897061__INCLUDED_)
