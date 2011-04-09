// PYDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MessAtoB.h"
#include "PYDlg.h"
#include "comn.h"
#include "string-trans.h"

// CPYDlg 对话框

IMPLEMENT_DYNAMIC(CPYDlg, CDialog)

CPYDlg::CPYDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPYDlg::IDD, pParent)
	, py_edit_content(_T(""))
{

}

CPYDlg::~CPYDlg()
{
}

void CPYDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, py_edit_content);
}


BEGIN_MESSAGE_MAP(CPYDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPYDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPYDlg 消息处理程序

//上传喷药指数
void CPYDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	py_edit_content.Replace("\r\n","\n");

	CTime ct1=CTime::GetCurrentTime();//当前日期

	std::string file_name = ct1.Format("%Y%m%d08_BFLB.PY"),
		py_file_content = py_edit_content;
	
	strtofile(file_name,py_file_content);

	try
	{
		//cout<<"正在登陆服务器......"<<endl;
		
		CInternetSession sess("My FTP Session");//"65.19.143.3","likev@xufanglu.cn","271828han",21,1
		
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.5","luoyang","luoyang");//登录
		if(pConnect->SetCurrentDirectory("/"))
			if(pConnect->PutFile(file_name.c_str(),file_name.c_str()))
			{
				MessageBox("上传成功！","成功",MB_ICONINFORMATION);
			}
	}
	catch (CInternetException* pEx)
	{
		char error[1025];
		pEx->GetErrorMessage(error, 1024);
		////cout<<"ERROR!"<<error<<endl;
		MessageBox("Error: "+CString(error));
		pEx->Delete();
	}

	OnOK();
}
