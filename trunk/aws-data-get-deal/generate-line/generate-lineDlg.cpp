// generate-lineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "generate-line.h"
#include "generate-lineDlg.h"
#include "TemphLineDlg.h"
#include "RainLineDlg.h"
#include "ShowSearchResult.h"
#include "SelectDateSimple.h"
#include "MeteorSearch.h"
#include "MeteorSearchB.h"

#include <string-trans.h>
#include <read_aws_from_mysql.h>
#include <map-useful.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CgeneratelineDlg �Ի���




CgeneratelineDlg::CgeneratelineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CgeneratelineDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgeneratelineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CgeneratelineDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CgeneratelineDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CgeneratelineDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CgeneratelineDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CgeneratelineDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_METEOR_STATISA, &CgeneratelineDlg::OnBnClickedButtonMeteorStatisA)
	ON_BN_CLICKED(IDC_BUTTON7, &CgeneratelineDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON11, &CgeneratelineDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON_METEOR_STATISB, &CgeneratelineDlg::OnBnClickedButtonMeteorStatisB)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CgeneratelineDlg::OnNMClickSyslink1)
END_MESSAGE_MAP()


// CgeneratelineDlg ��Ϣ�������

BOOL CgeneratelineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CgeneratelineDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CgeneratelineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CgeneratelineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CgeneratelineDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TemphLineDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
	}
}

void CgeneratelineDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RainLineDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
	}

}

void CgeneratelineDlg::OnBnClickedButton5()
{
	ShowMinMaxTemph(20);
}

void CgeneratelineDlg::OnBnClickedButton6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowMinMaxTemph(8);
}

int CgeneratelineDlg::ShowMinMaxTemph(int hour)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SelectDateSimple get_date_dlg;

	if(get_date_dlg.DoModal() == IDOK)
	{
		CTime date_end = get_date_dlg.date, date_begin;
		date_end = CTime(date_end.GetYear(),date_end.GetMonth(),date_end.GetDay(),hour,0,0);
		date_begin = date_end-CTimeSpan(1,0,0,0);

		ShowSearchResult show_dlg;
		//����
		show_dlg.title = date_begin.Format("%Y-%m-%d %H")+date_end.Format("---%Y-%m-%d %Hʱ �������¶�");

		date_begin += CTimeSpan(0,1,0,0);

		int ss[]={57065,57066,57070,57071,57074,57076,57077,57078,57162};

		std::string headtitles[] = {"վ��","����¶�","����ʱ��","����¶�","����ʱ��"};
		show_dlg.headtitles = ShowSearchResult::StringArray(headtitles,headtitles+5);

		show_dlg.contents.resize(5);
		for(int i=0;i<9;i++)
		{
			show_dlg.contents[0].push_back(to_string(ss[i]));
			std::map<CTime,double> records;
			std::map<CTime,double>::iterator p;

			get_records(ss[i],awssql::HIGH_TEMPH,records,date_begin,date_end);

			p=std::max_element(records.begin(),records.end(),less_pair_value<const CTime,double>);
			
			//����¶ȼ����ֵ�ʱ��
			show_dlg.contents[1].push_back(to_string(p->second));
			show_dlg.contents[2].push_back(p->first.Format("%Y-%m-%d %H:%M:%S").GetBuffer());
			

			get_records(ss[i],awssql::LOW_TEMPH,records,date_begin,date_end);

			p=std::min_element(records.begin(),records.end(),less_pair_value<const CTime,double>);

			//����¶ȼ����ֵ�ʱ��
			show_dlg.contents[3].push_back(to_string(p->second));
			show_dlg.contents[4].push_back(p->first.Format("%Y-%m-%d %H:%M:%S").GetBuffer());
			

		}

		show_dlg.column_width = 140;

		if(show_dlg.DoModal() == IDOK)
		{
		}

	}

	return 0;
}

void CgeneratelineDlg::OnBnClickedButtonMeteorStatisA()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	MeteorSearch meteor_dlg;

	if(meteor_dlg.DoModal() == IDOK)
	{
	}

}

//20-20�ۼƽ�ˮ��
void CgeneratelineDlg::OnBnClickedButton7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AccumRainfall(20);
}

// �ۼƽ�ˮ����ѯ
int CgeneratelineDlg::AccumRainfall(int hour)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SelectDateSimple get_date_dlg;

	if(get_date_dlg.DoModal() == IDOK)
	{
		CTime date_end = get_date_dlg.date, date_begin;
		date_end = CTime(date_end.GetYear(),date_end.GetMonth(),date_end.GetDay(),hour,0,0);
		date_begin = date_end-CTimeSpan(1,0,0,0);

		ShowSearchResult show_dlg;
		//����
		show_dlg.title = date_begin.Format("%Y-%m-%d %H")+date_end.Format("---%Y-%m-%d %Hʱ �ۼƽ�ˮ��");

		date_begin += CTimeSpan(0,1,0,0);

		int ss[]={57065,57066,57070,57071,57074,57076,57077,57078,57162};

		std::string headtitles[] = {"վ��","�ۼƽ�ˮ��"};
		show_dlg.headtitles = ShowSearchResult::StringArray(headtitles,headtitles+2);

		show_dlg.contents.resize(2);
		for(int i=0;i<9;i++)
		{
			show_dlg.contents[0].push_back(to_string(ss[i]));
			std::map<CTime,double> records;

			get_records(ss[i],awssql::HOURRAIN,records,date_begin,date_end);

			std::pair<CTime,double> sum(0,0);
			

			sum=std::accumulate(records.begin(),records.end(),sum,add_pair_value<const CTime,double>);
			
			//�ۼƽ�ˮ��
			show_dlg.contents[1].push_back(to_string(sum.second));
		
		}

		show_dlg.column_width = 140;

		if(show_dlg.DoModal() == IDOK)
		{
		}

	}
	return 0;
}

//08-08�ۼƽ�ˮ��
void CgeneratelineDlg::OnBnClickedButton11()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	AccumRainfall(8);
}

void CgeneratelineDlg::OnBnClickedButtonMeteorStatisB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MeteorSearchB meteor_dlg;

	if(meteor_dlg.DoModal() == IDOK)
	{
	}
}

void CgeneratelineDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �򿪰�������
	ShellExecute(NULL,"open","https://docs.google.com/View?id=d4hgc4n_2942rgz2qvhg",NULL,NULL,SW_SHOWNORMAL);
	*pResult = 0;
}
