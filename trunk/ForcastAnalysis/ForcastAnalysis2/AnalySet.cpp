// AnalySet.cpp : 实现文件
//

#include "stdafx.h"
#include "ForcastAnalysis2.h"
#include "AnalySet.h"


// AnalySet 对话框

IMPLEMENT_DYNAMIC(AnalySet, CDialog)

AnalySet::AnalySet(CWnd* pParent /*=NULL*/)
	: CDialog(AnalySet::IDD, pParent)
	, begin(0)
	, end(0)
	, folder(_T(""))
	, checked_times(0)
{

}

AnalySet::~AnalySet()
{
}

void AnalySet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, begin);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, end);
	DDX_Text(pDX, IDC_EDIT1, folder);
}


BEGIN_MESSAGE_MAP(AnalySet, CDialog)
	ON_BN_CLICKED(IDOK, &AnalySet::OnBnClickedOk)
	ON_BN_CLICKED(IDC_FLODERSET, &AnalySet::OnBnClickedFloderset)
END_MESSAGE_MAP()


// AnalySet 消息处理程序

void AnalySet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int i = GetCheckedRadioButton(IDC_RADIO1,IDC_RADIO4)-IDC_RADIO1;
	switch(i)
	{
	case 0:
		checked_times = 16;break;
	case 1:
		checked_times = 4;break;
	case 2:
		checked_times = 6;break;
	case 3:
		checked_times = 10;break;
	default:
		break;
	}

	OnOK();
}

void AnalySet::OnBnClickedFloderset()
{
	// TODO: 在此添加控件通知处理程序代码

	//打开文件夹
	BROWSEINFO   bInfo={};
	bInfo.hwndOwner   =   m_hWnd;    
	bInfo.lpszTitle   =   "所选择路径:   ";  
	bInfo.ulFlags   =   BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE;          

	LPITEMIDLIST   lpDlist;  //用来保存返回信息的IDList，使用SHGetPathFromIDList函数转换为字符串  
	lpDlist   =   SHBrowseForFolder(&bInfo)   ;   //显示选择对话框  
	if(lpDlist   !=   NULL)  
	{  
		char   tchPath[255];
		SHGetPathFromIDList(lpDlist,  tchPath);//把项目标识列表转化成目录  
		
		folder = tchPath;
		UpdateData(FALSE);
	}
}
