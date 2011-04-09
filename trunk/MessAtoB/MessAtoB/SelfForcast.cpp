// SelfForcast.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MessAtoB.h"
#include "SelfForcast.h"
#include "string-trans.h"
#include <fstream>
#include <iostream>

// SelfForcast �Ի���

IMPLEMENT_DYNAMIC(SelfForcast, CDialog)

SelfForcast::SelfForcast(CWnd* pParent /*=NULL*/)
	: CDialog(SelfForcast::IDD, pParent)
{
	std::string content;
	filetostr("b.txt",content);
	file_content = content.c_str();
}

SelfForcast::~SelfForcast()
{
}

void SelfForcast::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SelfForcast, CDialog)
	ON_BN_CLICKED(IDOK, &SelfForcast::OnBnClickedOk)
END_MESSAGE_MAP()


// SelfForcast ��Ϣ�������

BOOL SelfForcast::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CComboBox *pComboNames = (CComboBox *)GetDlgItem(IDC_COMBO_Names);
	
	std::ifstream fin("ForecastersNames.txt");

	if(fin.is_open() ) 
	{
		std::string name;
		while(fin>>name)
		{
			if(name.size() > 2)
			{
				pComboNames ->AddString(name.c_str());
			}
		}
	}

	if(pComboNames->GetCount() > 0)
	{
		pComboNames->SetCurSel(0);
	}

	pComboNames->SetItemHeight(-1,30);
	pComboNames->SetItemHeight(0,30);

	file_content.Replace("\n","\r\n");

	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_FileContent);
	pEdit ->SetWindowTextA(file_content);


	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


bool SelfForcast::PutSelfForcast()
{

	CComboBox *pComboNames = (CComboBox *)GetDlgItem(IDC_COMBO_Names);
	int cur_sel = pComboNames -> GetCurSel();
	CString self_name;
	pComboNames->GetLBText(cur_sel,self_name);

	size_t pos = ftp_filename.rfind('.');
	ftp_filename = ftp_filename.substr(0,pos+1) + self_name.GetBuffer();

	//this->MessageBox(ftp_filename.c_str());

	try
	{
		//cout<<"���ڵ�½������......"<<endl;
		
		CInternetSession sess("My FTP Session");//"65.19.143.3","likev@xufanglu.cn","271828han",21,1
		
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.21","ybpf","ybpf123");//��¼
		//if(pConnect->SetCurrentDirectory("/ybpf"))
			if(pConnect->PutFile("b.txt",ftp_filename.c_str()))
			{
				MessageBox("�ϴ��ɹ���","�ɹ�",MB_ICONINFORMATION);
				return true;
			}
	}
	catch (CInternetException* pEx)
	{
		char error[1025];
		pEx->GetErrorMessage(error, 1024);
		////cout<<"ERROR!"<<error<<endl;
		MessageBox("Error: "+CString(error));
		pEx->Delete();
		return false;
	}
	return false;
}
void SelfForcast::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PutSelfForcast();
	OnOK();
}
