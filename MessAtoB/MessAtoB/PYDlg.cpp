// PYDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MessAtoB.h"
#include "PYDlg.h"
#include "comn.h"
#include "string-trans.h"

// CPYDlg �Ի���

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


// CPYDlg ��Ϣ�������

//�ϴ���ҩָ��
void CPYDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	py_edit_content.Replace("\r\n","\n");

	CTime ct1=CTime::GetCurrentTime();//��ǰ����

	std::string file_name = ct1.Format("%Y%m%d08_BFLB.PY"),
		py_file_content = py_edit_content;
	
	strtofile(file_name,py_file_content);

	try
	{
		//cout<<"���ڵ�½������......"<<endl;
		
		CInternetSession sess("My FTP Session");//"65.19.143.3","likev@xufanglu.cn","271828han",21,1
		
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.5","luoyang","luoyang");//��¼
		if(pConnect->SetCurrentDirectory("/"))
			if(pConnect->PutFile(file_name.c_str(),file_name.c_str()))
			{
				MessageBox("�ϴ��ɹ���","�ɹ�",MB_ICONINFORMATION);
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
