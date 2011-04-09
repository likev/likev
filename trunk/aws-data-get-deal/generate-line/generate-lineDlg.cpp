// generate-lineDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CgeneratelineDlg 对话框




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


// CgeneratelineDlg 消息处理程序

BOOL CgeneratelineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CgeneratelineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CgeneratelineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CgeneratelineDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TemphLineDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
	}
}

void CgeneratelineDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
	ShowMinMaxTemph(8);
}

int CgeneratelineDlg::ShowMinMaxTemph(int hour)
{
	// TODO: 在此添加控件通知处理程序代码
	SelectDateSimple get_date_dlg;

	if(get_date_dlg.DoModal() == IDOK)
	{
		CTime date_end = get_date_dlg.date, date_begin;
		date_end = CTime(date_end.GetYear(),date_end.GetMonth(),date_end.GetDay(),hour,0,0);
		date_begin = date_end-CTimeSpan(1,0,0,0);

		ShowSearchResult show_dlg;
		//标题
		show_dlg.title = date_begin.Format("%Y-%m-%d %H")+date_end.Format("---%Y-%m-%d %H时 最高最低温度");

		date_begin += CTimeSpan(0,1,0,0);

		int ss[]={57065,57066,57070,57071,57074,57076,57077,57078,57162};

		std::string headtitles[] = {"站点","最高温度","出现时间","最低温度","出现时间"};
		show_dlg.headtitles = ShowSearchResult::StringArray(headtitles,headtitles+5);

		show_dlg.contents.resize(5);
		for(int i=0;i<9;i++)
		{
			show_dlg.contents[0].push_back(to_string(ss[i]));
			std::map<CTime,double> records;
			std::map<CTime,double>::iterator p;

			get_records(ss[i],awssql::HIGH_TEMPH,records,date_begin,date_end);

			p=std::max_element(records.begin(),records.end(),less_pair_value<const CTime,double>);
			
			//最高温度及出现的时间
			show_dlg.contents[1].push_back(to_string(p->second));
			show_dlg.contents[2].push_back(p->first.Format("%Y-%m-%d %H:%M:%S").GetBuffer());
			

			get_records(ss[i],awssql::LOW_TEMPH,records,date_begin,date_end);

			p=std::min_element(records.begin(),records.end(),less_pair_value<const CTime,double>);

			//最低温度及出现的时间
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
	// TODO: 在此添加控件通知处理程序代码

	MeteorSearch meteor_dlg;

	if(meteor_dlg.DoModal() == IDOK)
	{
	}

}

//20-20累计降水量
void CgeneratelineDlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	AccumRainfall(20);
}

// 累计降水量查询
int CgeneratelineDlg::AccumRainfall(int hour)
{
	// TODO: 在此添加控件通知处理程序代码
	SelectDateSimple get_date_dlg;

	if(get_date_dlg.DoModal() == IDOK)
	{
		CTime date_end = get_date_dlg.date, date_begin;
		date_end = CTime(date_end.GetYear(),date_end.GetMonth(),date_end.GetDay(),hour,0,0);
		date_begin = date_end-CTimeSpan(1,0,0,0);

		ShowSearchResult show_dlg;
		//标题
		show_dlg.title = date_begin.Format("%Y-%m-%d %H")+date_end.Format("---%Y-%m-%d %H时 累计降水量");

		date_begin += CTimeSpan(0,1,0,0);

		int ss[]={57065,57066,57070,57071,57074,57076,57077,57078,57162};

		std::string headtitles[] = {"站点","累计降水量"};
		show_dlg.headtitles = ShowSearchResult::StringArray(headtitles,headtitles+2);

		show_dlg.contents.resize(2);
		for(int i=0;i<9;i++)
		{
			show_dlg.contents[0].push_back(to_string(ss[i]));
			std::map<CTime,double> records;

			get_records(ss[i],awssql::HOURRAIN,records,date_begin,date_end);

			std::pair<CTime,double> sum(0,0);
			

			sum=std::accumulate(records.begin(),records.end(),sum,add_pair_value<const CTime,double>);
			
			//累计降水量
			show_dlg.contents[1].push_back(to_string(sum.second));
		
		}

		show_dlg.column_width = 140;

		if(show_dlg.DoModal() == IDOK)
		{
		}

	}
	return 0;
}

//08-08累计降水量
void CgeneratelineDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	AccumRainfall(8);
}

void CgeneratelineDlg::OnBnClickedButtonMeteorStatisB()
{
	// TODO: 在此添加控件通知处理程序代码
	MeteorSearchB meteor_dlg;

	if(meteor_dlg.DoModal() == IDOK)
	{
	}
}

void CgeneratelineDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 打开帮助链接
	ShellExecute(NULL,"open","https://docs.google.com/View?id=d4hgc4n_2942rgz2qvhg",NULL,NULL,SW_SHOWNORMAL);
	*pResult = 0;
}
