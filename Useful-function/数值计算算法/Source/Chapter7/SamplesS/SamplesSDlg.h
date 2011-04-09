// SamplesSDlg.h : header file
//

#if !defined(AFX_SAMPLESSDLG_H__0C3FA702_71AF_438D_B8D3_3B1E3FA092E7__INCLUDED_)
#define AFX_SAMPLESSDLG_H__0C3FA702_71AF_438D_B8D3_3B1E3FA092E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSamplesSDlg dialog

class CSamplesSDlg : public CDialog
{
// Construction
public:
	CSamplesSDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSamplesSDlg)
	enum { IDD = IDD_SAMPLES_DIALOG };
	CString	m_strMatrix1;
	CString	m_strMatrix2;
	CString	m_strMatrix3;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSamplesSDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSamplesSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPLESSDLG_H__0C3FA702_71AF_438D_B8D3_3B1E3FA092E7__INCLUDED_)
