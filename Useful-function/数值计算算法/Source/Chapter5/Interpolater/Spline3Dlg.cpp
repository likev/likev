// Spline3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "Interpolater.h"
#include "Spline3Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpline3Dlg dialog


CSpline3Dlg::CSpline3Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpline3Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpline3Dlg)
	m_strResult = _T("");
	//}}AFX_DATA_INIT
}


void CSpline3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpline3Dlg)
	DDX_Text(pDX, IDC_EDIT1, m_strResult);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpline3Dlg, CDialog)
	//{{AFX_MSG_MAP(CSpline3Dlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpline3Dlg message handlers

BOOL CSpline3Dlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
