// SetWethDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MessAtoB.h"
#include "SetWethDialog.h"


// CSetWethDialog �Ի���

IMPLEMENT_DYNAMIC(CSetWethDialog, CDialog)

CSetWethDialog::CSetWethDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetWethDialog::IDD, pParent)
	, m_edit1(_T(""))
	, m_edit2(_T(""))
	, m_edit3(_T(""))
	, m_edit4(_T(""))
{

}

CSetWethDialog::~CSetWethDialog()
{
}

void CSetWethDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT2, m_edit2);
	DDX_Text(pDX, IDC_EDIT3, m_edit3);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
}


BEGIN_MESSAGE_MAP(CSetWethDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetWethDialog::OnBnClickedButton1)
	ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL CSetWethDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	if(whent()==3)
	{
		GetDlgItem(IDC_EDIT3)->EnableWindow();
		GetDlgItem(IDC_EDIT4)->EnableWindow();
	}
	return TRUE;
}

// CSetWethDialog ��Ϣ�������
//���谴ť��Ӧ
void CSetWethDialog::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_edit1 = m_edit2 = m_edit3 = m_edit4 = "";
	UpdateData(FALSE);
}

int CSetWethDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	


	return 0;
}
