// SetWethDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MessAtoB.h"
#include "SetWethDialog.h"


// CSetWethDialog 对话框

IMPLEMENT_DYNAMIC(CSetWethDialog, CDialog)

CSetWethDialog::CSetWethDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSetWethDialog::IDD, pParent)
	, weather12(_T(""))
	, weather24(_T(""))
	, weather36(_T(""))
	, weather48(_T(""))
	, is_select_all(FALSE)
{
	forcast_period = PERIOD12;
	ischeck.assign(4,std::vector<int>(11,0));
}

CSetWethDialog::~CSetWethDialog()
{
}

void CSetWethDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, weather12);
	DDX_Text(pDX, IDC_EDIT2, weather24);
	DDX_Text(pDX, IDC_EDIT3, weather36);
	DDX_Text(pDX, IDC_EDIT4, weather48);
	DDX_Check(pDX, IDC_CHECK12, is_select_all);
}


BEGIN_MESSAGE_MAP(CSetWethDialog, CDialog)
//	ON_BN_CLICKED(IDC_BUTTON1, &CSetWethDialog::OnBnClickedButton1)
	ON_WM_CREATE()
	ON_EN_SETFOCUS(IDC_EDIT1, &CSetWethDialog::OnEnSetfocusEdit1)
	ON_EN_SETFOCUS(IDC_EDIT2, &CSetWethDialog::OnEnSetfocusEdit2)
	ON_EN_SETFOCUS(IDC_EDIT3, &CSetWethDialog::OnEnSetfocusEdit3)
	ON_EN_SETFOCUS(IDC_EDIT4, &CSetWethDialog::OnEnSetfocusEdit4)
	//ON_BN_CLICKED(IDC_BUTTON_APL, &CSetWethDialog::OnBnClickedButtonApl)
	ON_EN_CHANGE(IDC_EDIT1, &CSetWethDialog::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_CHECK12, &CSetWethDialog::OnBnClickedCheckAll)
	ON_BN_CLICKED(IDOK, &CSetWethDialog::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CSetWethDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	CButton * pbut = NULL;

	for(int i=IDC_CHECK1; i <= IDC_CHECK11; i++)
	{
		pbut=(CButton *)GetDlgItem(i);
		pbut->SetCheck(0);
	}

	if(is_forcast48)
	{
		GetDlgItem(IDC_EDIT3)->EnableWindow();
		GetDlgItem(IDC_EDIT4)->EnableWindow();
	}
	return TRUE;
}

// CSetWethDialog 消息处理程序
//重设按钮响应
//void CSetWethDialog::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	weather12 = weather24 = weather36 = weather48 = "";
//	UpdateData(FALSE);
//}

int CSetWethDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	return 0;
}


void CSetWethDialog::OnEnSetfocusEdit1()
{
	// TODO: 在此添加控件通知处理程序代码

	OnBnClickedButtonApl();
	forcast_period = PERIOD12;
	GetDlgItem(IDC_STATIC_SEL)->SetWindowTextA("12小时");
	is_select_all = 0;UpdateData(FALSE);
	
	CButton * pbut = NULL;

	for(int i=IDC_CHECK1; i <= IDC_CHECK11; i++)
	{
		pbut=(CButton *)GetDlgItem(i);
		pbut->SetCheck(ischeck[0][i-IDC_CHECK1]);
	}
}

void CSetWethDialog::OnEnSetfocusEdit2()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonApl();
	forcast_period = PERIOD24;
	GetDlgItem(IDC_STATIC_SEL)->SetWindowTextA("24小时");
	is_select_all = 0;UpdateData(FALSE);
		
	CButton * pbut = NULL;

	for(int i=IDC_CHECK1; i <= IDC_CHECK11; i++)
	{
		pbut=(CButton *)GetDlgItem(i);
		pbut->SetCheck(ischeck[1][i-IDC_CHECK1]);
	}
}

void CSetWethDialog::OnEnSetfocusEdit3()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonApl();
	forcast_period = PERIOD36;
	GetDlgItem(IDC_STATIC_SEL)->SetWindowTextA("36小时");
	is_select_all = 0;UpdateData(FALSE);
		
	CButton * pbut = NULL;

	for(int i=IDC_CHECK1; i <= IDC_CHECK11; i++)
	{
		pbut=(CButton *)GetDlgItem(i);
		pbut->SetCheck(ischeck[2][i-IDC_CHECK1]);
	}
}

void CSetWethDialog::OnEnSetfocusEdit4()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonApl();
	forcast_period = PERIOD48;
	GetDlgItem(IDC_STATIC_SEL)->SetWindowTextA("48小时");
	is_select_all = 0;UpdateData(FALSE);
		
	CButton * pbut = NULL;

	for(int i=IDC_CHECK1; i <= IDC_CHECK11; i++)
	{
		pbut=(CButton *)GetDlgItem(i);
		pbut->SetCheck(ischeck[3][i-IDC_CHECK1]);
	}
}

void CSetWethDialog::OnBnClickedButtonApl()
{
	// TODO: 在此添加控件通知处理程序代码
    UpdateData(TRUE);

	CString str;
	GetDlgItem(IDC_STATIC_SEL)->GetWindowTextA(str);

	CButton * pbut = NULL;

	//储存选项
	for(int i=IDC_CHECK1; i <= IDC_CHECK11; i++)
	{
		pbut=(CButton *)GetDlgItem(i);
		ischeck[forcast_period][i-IDC_CHECK1] = pbut->GetCheck();
	}
	
}

void CSetWethDialog::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CSetWethDialog::OnBnClickedCheckAll()
{
	// TODO: 在此添加控件通知处理程序代码
	is_select_all = !is_select_all;
	CButton * pbut = NULL;

	for(int i=IDC_CHECK1; i <= IDC_CHECK11; i++)
	{
		pbut=(CButton *)GetDlgItem(i);
		pbut->SetCheck(is_select_all);
	}
}

void CSetWethDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedButtonApl();
	OnOK();
}
