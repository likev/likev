// ReadSnowUIDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ReadSnowUI.h"
#include "ReadSnowUIDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CReadSnowUIDlg 对话框




CReadSnowUIDlg::CReadSnowUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReadSnowUIDlg::IDD, pParent)
	, beginHour(_T("20时"))
	, endHour(_T("20时"))
	, selectRagion(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	endDay = CTime::GetCurrentTime();
	beginDay = endDay - CTimeSpan(1,0,0,0);

	InitDataFromFile();
}

void CReadSnowUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO1, beginHour);
	DDX_CBString(pDX, IDC_COMBO2, endHour);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, beginDay);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, endDay);
	DDX_Radio(pDX, IDC_RADIO1, selectRagion);
}

BEGIN_MESSAGE_MAP(CReadSnowUIDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_Query, &CReadSnowUIDlg::OnBnClickedButtonQuery)
END_MESSAGE_MAP()


// CReadSnowUIDlg 消息处理程序

BOOL CReadSnowUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CReadSnowUIDlg::OnPaint()
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
HCURSOR CReadSnowUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReadSnowUIDlg::OnBnClickedButtonQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	beginDay += CTimeSpan(0,getSelectHour(beginHour)-beginDay.GetHour(),0,0);
	endDay += CTimeSpan(0,getSelectHour(endHour)-endDay.GetHour(),0,0);

	if(endDay > CTime::GetCurrentTime()) endDay = CTime::GetCurrentTime();

	if(beginDay >= endDay)
	{
		this->MessageBox("时间范围有误，请重新选择时间！","错误",MB_OK|MB_ICONINFORMATION );
		return;
	}

	WriteDataToFile();
}

// 将数据写入文件
bool CReadSnowUIDlg::WriteDataToFile(void)
{
	std::string timestr = beginDay.Format("%Y年%#m月%#d日%H时 -- ")+endDay.Format("%#d日%H时");
	log_to_file("ftplog.txt","查询时间段："+timestr);
	
	DealSnowData dsd(beginDay, endDay );

	if(0 == selectRagion) 
	{
		log_to_file("ftplog.txt","查询洛阳地区");

		dsd.SetStations(luoyangStationID);

		std::vector<CTime> timeList = dsd.GetTimeList();
		std::vector< std::vector<SnowInfo> > allStationsRecord = dsd.GetAllStationsRecord();
		std::vector<SnowInfo> accumulatedResult = dsd.GetAccumulateSnow();

		std::ofstream fout("result.txt");

		fout<<"\n            洛阳市各站 "<<timestr<<" 降雪统计  \n"
			  "--------------------------------------------------------------------------\n\n\n"
			  "各时次详细降雪情况 雪深(cm)/降雪量(mm)：\n"
			  "---------------------------------------------\n";
		
		fout<<"站点";

		for(int index=0;index<timeList.size();index++)
		{
			fout<<std::setw(10)<<timeList[index].Format("%#d/%H时");
		}
		fout<<"  最大雪深/累计降雪量\n\n";
		
		for(int index=0;index<allStationsRecord.size();index++)
		{
			fout<<luoyangStationName[index];
			
			for(int col=0; col<allStationsRecord[index].size(); col++)
			{
				fout<<std::setw(10)<<allStationsRecord[index][col].GetSnowStr();
			}
			fout<<std::setw(10)<<accumulatedResult[index].GetSnowStr()<<std::endl;
		}

		fout<<"\n\n\n";
		fout<<"各站的 最大雪深(cm)/累计降雪量(mm)：\n"
			"---------------------------------------------\n";
		
		for(int index=0;index<accumulatedResult.size();index++)
		{
			fout<<"    "<<luoyangStationName[index]<<": "<<accumulatedResult[index].GetSnowStr();
		}
		
		fout.close();
	}

	else 
	{
		log_to_file("ftplog.txt","查询河南地区");
		MessageBox("此项功能待完成！","提示",MB_OK|MB_ICONINFORMATION );

		return false;
	}

	ShellExecute(NULL, "open", "result.txt", NULL, NULL, SW_SHOWNORMAL);

	return true;
}

void CReadSnowUIDlg::InitDataFromFile()
{
	std::ifstream fin;

	fin.open("luoyang-stations.txt");

	if(!fin.is_open())
	{
		log_to_file("ftplog.txt","打开文件luoyang-stations.txt失败");
		return;
	}

	std::string str;
	
	while(fin>>str)
	{
		luoyangStationID.push_back(str);
		fin>>str;
		luoyangStationName.push_back(str);
	}
	fin.close();

	fin.clear();
	fin.open("henan-stations.txt");
	if(!fin.is_open())
	{
		log_to_file("ftplog.txt","打开文件henan-stations.txt失败");
		return;
	}
	
	while(fin>>str)
	{
		henanStationID.push_back(str);
		fin>>str;
		henanStationName.push_back(str);
	}
	fin.close();
}

int CReadSnowUIDlg::getSelectHour(CString hourString)const
{
	if("06时" == hourString) return 6;
	else if("07时" == hourString) return 7;
	else if("08时" == hourString) return 8;
	else if("11时" == hourString) return 11;
	else if("14时" == hourString) return 14;
	else if("17时" == hourString) return 17;
	else if("20时" == hourString) return 20;
	else return 20;
}
