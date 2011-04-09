// AnalySet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ForcastAnalysis2.h"
#include "AnalySet.h"


// AnalySet �Ի���

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


// AnalySet ��Ϣ�������

void AnalySet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//���ļ���
	BROWSEINFO   bInfo={};
	bInfo.hwndOwner   =   m_hWnd;    
	bInfo.lpszTitle   =   "��ѡ��·��:   ";  
	bInfo.ulFlags   =   BIF_RETURNONLYFSDIRS|BIF_NEWDIALOGSTYLE;          

	LPITEMIDLIST   lpDlist;  //�������淵����Ϣ��IDList��ʹ��SHGetPathFromIDList����ת��Ϊ�ַ���  
	lpDlist   =   SHBrowseForFolder(&bInfo)   ;   //��ʾѡ��Ի���  
	if(lpDlist   !=   NULL)  
	{  
		char   tchPath[255];
		SHGetPathFromIDList(lpDlist,  tchPath);//����Ŀ��ʶ�б�ת����Ŀ¼  
		
		folder = tchPath;
		UpdateData(FALSE);
	}
}
