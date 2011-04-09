// ForcastAnalysis2Doc.cpp : CForcastAnalysis2Doc ���ʵ��
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


// CForcastAnalysis2Doc ����/����

CForcastAnalysis2Doc::CForcastAnalysis2Doc()
{
	// TODO: �ڴ����һ���Թ������

	//���ÿ�ʼ����ʱ��
	stat_begin = stat_end = CTime::GetCurrentTime();

	//�����ļ���Ĭ��·��
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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CForcastAnalysis2Doc ���л�

void CForcastAnalysis2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CForcastAnalysis2Doc ���

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


// CForcastAnalysis2Doc ����

void CForcastAnalysis2Doc::OnAnalyset()
{
	// TODO: �ڴ���������������
	AnalySet dlg;
	//��ʼ�����öԻ���
	dlg.begin = stat_begin;
	dlg.end   = stat_end;
	dlg.folder= stat_floder;

	if(dlg.DoModal() != IDOK)
	{
		return;
	}

	//��ȡ���õ�����
	stat_begin = CTime(dlg.begin.GetYear(),dlg.begin.GetMonth(),dlg.begin.GetDay(),dlg.checked_times,0,0);
	stat_end   = CTime(dlg.end.GetYear(),dlg.end.GetMonth(),dlg.end.GetDay(),dlg.checked_times,0,0);

	stat_floder= dlg.folder;

	BeginAnaly();
}

// ������������
void CForcastAnalysis2Doc::BeginAnaly(void)
{
	ReadStationNums();

	for(cur_time=stat_begin; cur_time<=stat_end; cur_time+=CTimeSpan(1,0,0,0) )
	{
		PerdayDeal();
	}

}

//����ÿһ��
void CForcastAnalysis2Doc::PerdayDeal(void)
{
	ReadCityMessages();
	PerdayStat();
	
}

// ��ȡ��ǰ����ʱ��ĳ���
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
	//��ȡ����Ԥ���ļ�����
	filetostr(filename,file_content);

	for(size_t it=0; it != station_size; it++)
	{
		to_string(station_nums[it],str_number);

		//��ȡ��ǰվ���Ԥ����Ϣ
		city_mess_day[it].init(str_number, file_content);

		city_message &cur = city_mess_day[it];

		//ת��Ϊcity_fst�� ���ڱȽ�
		read_city_fst(perday_fst[it],cur);
		
		if(cur_time == 16)
			perday_fst[it].time = cur_time+CTimeSpan(0,4,0,0);
		else
			perday_fst[it].time = cur_time+CTimeSpan(0,8-cur_time.GetHour(),0,0);

		//��ʼ����ǰվ���ͳ�ƽ��
		statistics[cur.stn ] = stat_result(cur.fcn/2);
	}

	return true;

}

//ͳ��ÿһ������
void CForcastAnalysis2Doc::PerdayStat(void)
{
	for(size_t i=0; i != station_nums.size(); i++)
	{
		PerCityStat(station_nums[i]);
		analyse_record(perday_fst[i],statistics);
	}
}
// ��ȡ��Ҫ������վ���
bool CForcastAnalysis2Doc::ReadStationNums(void)
{
	//��ȡ��Ҫ������վ��
	std::ifstream fin("stations_numbers.txt");
	if(!fin.is_open())
	{
		AfxMessageBox("�Ҳ���վ�������ļ� stations_numbers.txt��");
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

// ͳ�Ƶ����صĸ�ʱ��Ԥ��
void CForcastAnalysis2Doc::PerCityStat(int station_number)
{
}
