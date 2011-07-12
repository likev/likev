// ShortForcast.cpp : 实现文件
//

#include "stdafx.h"
#include "MessAtoB.h"
#include "ShortForcast.h"
#include "string-trans.h"
#include <fstream>
#include <iostream>

// ShortForcast 对话框

IMPLEMENT_DYNAMIC(ShortForcast, CDialog)

ShortForcast::ShortForcast(CWnd* pParent /*=NULL*/)
	: CDialog(ShortForcast::IDD, pParent)
{
	CTime ct1=CTime::GetCurrentTime();//当前日期
	int cth = ct1.GetHour();
	CString sth,sth2;

	if(cth<10)
	{
		sth = "08";
		sth2 = "14";
	}
	else if(cth<16)
	{
		sth = "14";
		sth2 = "20";
	}
	else
	{
		sth = "20";
		sth2 = "08";
	}

	forcast_content
	  = "                "+sth+"-"+sth2+"时短时天气预报\r\n\r\n"
		"预计"+sth+"-"+sth2+"时：全区\r\n\r\n"
		"                                       "+ct1.Format("%Y年%#m月%#d日");
	file_path = "//172.18.172.63/data_/xjdata/FORECAST/dsyb/"+ct1.Format("%Y/%Y%m%d")+sth+".txt";
}

ShortForcast::~ShortForcast()
{
}

void ShortForcast::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ShortForcast, CDialog)
	ON_BN_CLICKED(IDOK, &ShortForcast::OnBnClickedOk)
END_MESSAGE_MAP()


// ShortForcast 消息处理程序

BOOL ShortForcast::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化


	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_FContent);
	pEdit ->SetWindowTextA(forcast_content);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


bool ShortForcast::PutShortForcast()
{
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_FContent);
	pEdit ->GetWindowText(forcast_content);
	forcast_content.Replace("\r\n","\n");

	if(strtofile(file_path.GetBuffer(),forcast_content.GetBuffer() ))    //数据保存为文件
	{
		MessageBox("文件成功上传至"+file_path,"成功",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("文件上传失败，请重试！", "警告", MB_ICONERROR);
		return false;
	}
	
	return true;
}
void ShortForcast::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	if(PutShortForcast()) OnOK();
}
