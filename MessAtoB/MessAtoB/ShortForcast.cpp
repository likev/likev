// ShortForcast.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MessAtoB.h"
#include "ShortForcast.h"
#include "string-trans.h"
#include <fstream>
#include <iostream>

// ShortForcast �Ի���

IMPLEMENT_DYNAMIC(ShortForcast, CDialog)

ShortForcast::ShortForcast(CWnd* pParent /*=NULL*/)
	: CDialog(ShortForcast::IDD, pParent)
{
	CTime ct1=CTime::GetCurrentTime();//��ǰ����
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
	  = "                "+sth+"-"+sth2+"ʱ��ʱ����Ԥ��\r\n\r\n"
		"Ԥ��"+sth+"-"+sth2+"ʱ��ȫ��\r\n\r\n"
		"                                       "+ct1.Format("%Y��%#m��%#d��");
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


// ShortForcast ��Ϣ�������

BOOL ShortForcast::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��


	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_FContent);
	pEdit ->SetWindowTextA(forcast_content);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


bool ShortForcast::PutShortForcast()
{
	CEdit *pEdit = (CEdit *)GetDlgItem(IDC_EDIT_FContent);
	pEdit ->GetWindowText(forcast_content);
	forcast_content.Replace("\r\n","\n");

	if(strtofile(file_path.GetBuffer(),forcast_content.GetBuffer() ))    //���ݱ���Ϊ�ļ�
	{
		MessageBox("�ļ��ɹ��ϴ���"+file_path,"�ɹ�",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("�ļ��ϴ�ʧ�ܣ������ԣ�", "����", MB_ICONERROR);
		return false;
	}
	
	return true;
}
void ShortForcast::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(PutShortForcast()) OnOK();
}
