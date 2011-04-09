// ImagDataDlg.cpp : implementation file
//

#include "stdafx.h"
#include "LECalculator.h"
#include "ImagDataDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImagDataDlg dialog


CImagDataDlg::CImagDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImagDataDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImagDataDlg)
	m_strCoefficient = _T("");
	m_strConstant = _T("");
	//}}AFX_DATA_INIT
}


void CImagDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImagDataDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strCoefficient);
	DDX_Text(pDX, IDC_EDIT2, m_strConstant);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImagDataDlg, CDialog)
	//{{AFX_MSG_MAP(CImagDataDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagDataDlg message handlers
