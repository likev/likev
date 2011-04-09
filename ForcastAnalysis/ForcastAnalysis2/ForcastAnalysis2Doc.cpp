// ForcastAnalysis2Doc.cpp : CForcastAnalysis2Doc 类的实现
//
#include <string-trans.h>

#include "stdafx.h"
#include "ForcastAnalysis2.h"

#include "ForcastAnalysis2Doc.h"
#include "AnalySet.h"
#include "analy-day.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CForcastAnalysis2Doc

IMPLEMENT_DYNCREATE(CForcastAnalysis2Doc, CDocument)

BEGIN_MESSAGE_MAP(CForcastAnalysis2Doc, CDocument)
	ON_COMMAND(ID_ANALYSET, &CForcastAnalysis2Doc::OnAnalyset)
END_MESSAGE_MAP()


// CForcastAnalysis2Doc 构造/析构

CForcastAnalysis2Doc::CForcastAnalysis2Doc()
{
	// TODO: 在此添加一次性构造代码

	//设置开始结束时间
	stat_begin = stat_end = CTime::GetCurrentTime();

	//设置文件夹默认路径
	char pathbuf[MAX_PATH];
	GetCurrentDirectory(MAX_PATH,pathbuf);

	stat_floder = pathbuf;
}

CForcastAnalysis2Doc::~CForcastAnalysis2Doc()
{
}

BOOL CForcastAnalysis2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CForcastAnalysis2Doc 序列化

void CForcastAnalysis2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CForcastAnalysis2Doc 诊断

#ifdef _DEBUG
void CForcastAnalysis2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CForcastAnalysis2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CForcastAnalysis2Doc 命令

void CForcastAnalysis2Doc::OnAnalyset()
{
	// TODO: 在此添加命令处理程序代码
	AnalySet dlg;
	//初始化设置对话框
	dlg.begin = stat_begin;
	dlg.end   = stat_end;
	dlg.folder= stat_floder;

	if(dlg.DoModal() != IDOK)
	{
		return;
	}

	//获取设置的数据
	stat_begin = CTime(dlg.begin.GetYear(),dlg.begin.GetMonth(),dlg.begin.GetDay(),dlg.checked_times,0,0);
	stat_end   = CTime(dlg.end.GetYear(),dlg.end.GetMonth(),dlg.end.GetDay(),dlg.checked_times,0,0);

	stat_floder= dlg.folder;

	BeginAnaly();
}

// 分析处理启动
void CForcastAnalysis2Doc::BeginAnaly(void)
{
	ReadStationNums();

	for(cur_time=stat_begin; cur_time<=stat_end; cur_time+=CTimeSpan(1,0,0,0) )
	{
		PerdayDeal();
	}

}

//处理每一天
void CForcastAnalysis2Doc::PerdayDeal(void)
{
	ReadCityMessages();
	PerdayStat();
	
}

// 读取当前分析时间的城镇报
bool CForcastAnalysis2Doc::ReadCityMessages(void)
{
	using namespace std;

	size_t station_size = station_nums.size();
	city_mess_day.resize(station_size);
	perday_fst.resize(station_size);

	string filename = get_filename(stat_floder,cur_time);
	if(filename.size()<1)
		return false;

	string file_content, str_number;
	//读取城镇报预报文件内容
	filetostr(filename,file_content);

	for(size_t it=0; it != station_size; it++)
	{
		to_string(station_nums[it],str_number);

		//读取当前站点的预报信息
		city_mess_day[it].init(str_number, file_content);

		city_message &cur = city_mess_day[it];

		//转化为city_fst类 便于比较
		read_city_fst(perday_fst[it],cur);
		
		if(cur_time == 16)
			perday_fst[it].time = cur_time+CTimeSpan(0,4,0,0);
		else
			perday_fst[it].time = cur_time+CTimeSpan(0,8-cur_time.GetHour(),0,0);

		//初始化当前站点的统计结果
		statistics[cur.stn ] = stat_result(cur.fcn/2);
	}

	return true;

}

//统计每一天数据
void CForcastAnalysis2Doc::PerdayStat(void)
{
	for(size_t i=0; i != station_nums.size(); i++)
	{
		PerCityStat(station_nums[i]);
		analyse_record(perday_fst[i],statistics);
	}
}
// 读取需要分析的站点号
bool CForcastAnalysis2Doc::ReadStationNums(void)
{
	//读取需要分析的站点
	std::ifstream fin("stations_numbers.txt");
	if(!fin.is_open())
	{
		AfxMessageBox("找不到站号配置文件 stations_numbers.txt！");
		return false;
	}

	int stn_number=99999;
	while(fin>>stn_number)
	{
		station_nums.push_back(stn_number);
	}
	fin.close();
	return true;
}

// 统计单个县的各时次预报
void CForcastAnalysis2Doc::PerCityStat(int station_number)
{
}
