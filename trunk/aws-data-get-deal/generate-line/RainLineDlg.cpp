// RainLineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "generate-line.h"
#include "RainLineDlg.h"
#include "read_aws_from_mysql.h"
#include "map-useful.h"

// RainLineDlg �Ի���

IMPLEMENT_DYNAMIC(RainLineDlg, CDialog)

RainLineDlg::RainLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(RainLineDlg::IDD, pParent)
{
	begin_day = CTime::GetCurrentTime();
	end_day = begin_day - CTimeSpan(300,0,0,0);

	begin_hour = 0;
	end_hour = 0;

	int ss[]={57065,57066,57070,57071,57074,57076,57077,57078,57162};
	stations.assign(ss,ss+9);

	draw_type = ACCUMULATED;

	is_lastest_rain = true;

	MAX_RAIN_SPAN_HOUR = 12;
}

BOOL RainLineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CheckDlgButton(IDC_LastestRain,1);
	CheckDlgButton(IDC_ACCUMULATED,1);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

RainLineDlg::~RainLineDlg()
{
}

void RainLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, begin_day);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, end_day);
	DDX_Text(pDX, IDC_BeginHour, begin_hour);
	DDV_MinMaxInt(pDX, begin_hour, 0, 23);
	DDX_Text(pDX, IDC_EndHour, end_hour);
	DDV_MinMaxInt(pDX, end_hour, 0, 23);
}


BEGIN_MESSAGE_MAP(RainLineDlg, CDialog)
//	ON_BN_CLICKED(IDC_RAnyTime, &RainLineDlg::OnBnClickedRanytime)
ON_BN_SETFOCUS(IDC_RAnyTime, &RainLineDlg::OnBnSetfocusRanytime)
//ON_NOTIFY(BCN_HOTITEMCHANGE, IDC_RAnyTime, &RainLineDlg::OnBnHotItemChangeRanytime)
ON_BN_CLICKED(IDC_RAnyTime, &RainLineDlg::OnBnClickedRanytime)
ON_BN_CLICKED(IDC_LastestRain, &RainLineDlg::OnBnClickedLastestrain)
ON_BN_CLICKED(IDC_Last3Hour, &RainLineDlg::OnBnClickedLast3hour)
ON_BN_CLICKED(IDC_Last6Hour, &RainLineDlg::OnBnClickedLast6hour)
ON_BN_CLICKED(IDC_Last12Hour, &RainLineDlg::OnBnClickedLast12hour)
ON_BN_CLICKED(IDC_Last24Hour, &RainLineDlg::OnBnClickedLast24hour)
ON_BN_CLICKED(IDC_RToday, &RainLineDlg::OnBnClickedRtoday)
ON_BN_CLICKED(IDC_RYeasterday, &RainLineDlg::OnBnClickedRyeasterday)
ON_BN_CLICKED(IDC_RCurMonth, &RainLineDlg::OnBnClickedRcurmonth)
ON_BN_CLICKED(IDC_RLastMonth, &RainLineDlg::OnBnClickedRlastmonth)
ON_BN_CLICKED(IDC_DrawLine, &RainLineDlg::OnBnClickedDrawline)
ON_BN_CLICKED(IDC_ACCUMULATED, &RainLineDlg::OnBnClickedAccumulated)
ON_BN_CLICKED(IDC_RAINBYHOUR, &RainLineDlg::OnBnClickedRainbyhour)
END_MESSAGE_MAP()


// RainLineDlg ��Ϣ�������

//void RainLineDlg::OnBnClickedRanytime()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}

void RainLineDlg::OnBnSetfocusRanytime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow();
		GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow();
		GetDlgItem(IDC_BeginHour)->EnableWindow();
		GetDlgItem(IDC_EndHour)->EnableWindow();
}

//void RainLineDlg::OnBnHotItemChangeRanytime(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// �˹���Ҫ�� Internet Explorer 6 ����߰汾��
//	// ���� _WIN32_IE ������ >= 0x0600��
//	LPNMBCHOTITEM pHotItem = reinterpret_cast<LPNMBCHOTITEM>(pNMHDR);
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	*pResult = 0;
//}

// ��ѡ��ť��ı�
int RainLineDlg::RadioChange(void)
{
	if(GetCheckedRadioButton(IDC_LastestRain,IDC_RAnyTime) == IDC_RAnyTime)
	{
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow();
		GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow();
		GetDlgItem(IDC_BeginHour)->EnableWindow();
		GetDlgItem(IDC_EndHour)->EnableWindow();
	}
	else
	{
		GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(0);
		GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(0);
		GetDlgItem(IDC_BeginHour)->EnableWindow(0);
		GetDlgItem(IDC_EndHour)->EnableWindow(0);
	}

	if(GetCheckedRadioButton(IDC_LastestRain,IDC_RAnyTime) == IDC_LastestRain)
	{
		is_lastest_rain = true;
	}
	else
	{
		is_lastest_rain = false;
	}

	return 0;
}

void RainLineDlg::OnBnClickedRanytime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RadioChange();
}

void RainLineDlg::OnBnClickedLastestrain()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RadioChange();

	begin_day = CTime::GetCurrentTime();
	end_day = begin_day - CTimeSpan(300,0,0,0);

	begin_hour = 0;
	end_hour = 0;

	is_lastest_rain = true;

	UpdateData(FALSE);

}

void RainLineDlg::OnBnClickedLast3hour()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RadioChange();

	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(0,2,0,0);

	begin_hour = begin_day.GetHour();
	end_hour = end_day.GetHour();

	UpdateData(FALSE);
}

void RainLineDlg::OnBnClickedLast6hour()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RadioChange();

	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(0,5,0,0);

	begin_hour = begin_day.GetHour();
	end_hour = end_day.GetHour();

	UpdateData(FALSE);
}

void RainLineDlg::OnBnClickedLast12hour()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RadioChange();

	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(0,11,0,0);

	begin_hour = begin_day.GetHour();
	end_hour = end_day.GetHour();

	UpdateData(FALSE);
}

void RainLineDlg::OnBnClickedLast24hour()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RadioChange();

	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(0,23,0,0);

	begin_hour = begin_day.GetHour();
	end_hour = end_day.GetHour();

	UpdateData(FALSE);
}

void RainLineDlg::OnBnClickedRtoday()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RadioChange();

	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(1,0,0,0);

	begin_hour = 20;
	end_hour = 20;

	UpdateData(FALSE);
}

void RainLineDlg::OnBnClickedRyeasterday()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RadioChange();

	end_day = CTime::GetCurrentTime()- CTimeSpan(1,0,0,0);
	begin_day = end_day - CTimeSpan(1,0,0,0);

	begin_hour = 20;
	end_hour = 20;

	UpdateData(FALSE);
}

void RainLineDlg::OnBnClickedRcurmonth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RadioChange();

	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(end_day.GetDay()-1,0,0,0);

	begin_hour = 0;
	end_hour = end_day.GetHour();

	UpdateData(FALSE);
}

void RainLineDlg::OnBnClickedRlastmonth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	RadioChange();

	CTime CurTime = CTime::GetCurrentTime();
	end_day = CurTime - CTimeSpan(CurTime.GetDay(),0,0,0);
	begin_day = CTime(end_day.GetYear(),end_day.GetMonth(),1,0,0,0);

	begin_hour = 0;
	end_hour = 23;

	UpdateData(FALSE);
}



void RainLineDlg::OnBnClickedDrawline()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	
	if(begin_hour<0 || begin_hour>23 || end_hour<0 || end_hour>23) return;

	LeftTime  = CTime(begin_day.GetYear(),begin_day.GetMonth(),begin_day.GetDay(),begin_hour,0,0);
	RightTime = CTime(end_day.GetYear(),end_day.GetMonth(),end_day.GetDay(),end_hour,0,0);

	if(is_lastest_rain)
	{
		CalcLastestTime();
	}

	generate_html();
	
	char app_buf[1024],path_buf[1024];
	DWORD result1 = GetPrivateProfileString("filepath","htmlapp","C:\\Program Files\\Internet Explorer\\iexplore.exe",app_buf,1000,"./glsetup.ini");

	GetCurrentDirectory(1024,path_buf);
	CString apppath = app_buf,
		filepath = CString(path_buf) + "\\draw-line\\rain-line.html";

	//ִ��
	PROCESS_INFORMATION proif;
	STARTUPINFO stif = {sizeof(stif)};

	BOOL res = ::CreateProcess(NULL,("\""+apppath+"\" \""+filepath+"\"").GetBuffer(),NULL,NULL,FALSE,0,NULL,NULL,&stif,&proif);

}

std::string RainLineDlg::get_additional_info()
{
	using namespace std;

	int hours_plus = int((RightTime-LeftTime).GetTotalHours()/6);

	CString xleft = (LeftTime - CTimeSpan(0,5,0,0)).Format("'%Y-%m-%d %H:00'"),
		    xright= (RightTime + CTimeSpan(0,hours_plus,0,0)).Format("'%Y-%m-%d %H:00'");

	std::vector<double>::iterator pos_min, pos_max;
	pos_min = std::min_element(min_values.begin(), min_values.end());
	pos_max = std::max_element(max_values.begin(), max_values.end());

	double min_value = *pos_min, max_value = *pos_max;
	double range = (*pos_max-*pos_min+3);
	min_value = min_value - range/5.0;
	max_value = max_value + range/5.0;

	switch(draw_type)
	{
	case ACCUMULATED:
		plot_title = "���ۼƽ�ˮ����";
		break;
	case RAINBYHOUR:
		plot_title = "����ʱ��ˮ����";
		break;
	default:
		break;
	}

	CString records, time_range, value_range, raintitle;
	time_range.Format("var mintime = %s, maxtime= %s;",xleft,xright);
	//var min_value = -4, max_value = 36, tick_interval = 2;
	value_range.Format("\n  var min_value = %f, max_value = %f, tick_interval = %4.1f;",min_value, max_value, range/15);

	raintitle.Format("\n  var plot_title= '%s' ;",plot_title.c_str());
	return (LPCSTR)(time_range+value_range+raintitle);
}

// ����html�ļ�
int RainLineDlg::generate_html(void)
{
	std::string filecontent;
	filetostr("draw-line\\rain-line.html",filecontent);

	size_t pos1= filecontent.find("//record-begin"),
		   pos2= filecontent.find("//record-end");

	filecontent.erase(pos1+14,pos2-pos1-14);

	std::string records;

	max_values.clear(); min_values.clear();
	for(size_t i=0;i!=stations.size();i++)
	{
		records += "\n  "+get_records_str(stations[i]);
	}

	records += "\n  "+get_additional_info();

	filecontent.insert(pos1+14,records+"\n  ");

	strtofile("draw-line\\rain-line.html",filecontent);

	return 0;
}

// ��ȡ��վ��������¼
std::string RainLineDlg::get_records_str(int station_number)
{
	using namespace std;	

	int rows = get_records(station_number,awssql::HOURRAIN,mrecords,LeftTime,RightTime);
	
	CString  dayrecord;
	string records_str="var l"+to_string(station_number)+" = [ ";

	if(!rows)//û�м�¼
		return records_str+ "];";

	switch(draw_type)
	{
	case ACCUMULATED:
		ToAccumulatedRain(mrecords);
		break;
	case RAINBYHOUR:
		ToHourRain(mrecords);
		break;
	default:
		break;
	}

	for(map<CTime,double>::iterator it = mrecords.begin();
		it != mrecords.end(); it++)
	{
		CString datestr = it->first.Format("['%Y-%m-%d %H:00',");
		dayrecord.Format("%s'%f'],",datestr,it->second);
		//dayrecord = dayrecord+"'"+to_string(it->second).c_str()+"'],";

		records_str += dayrecord;

	}
	records_str.erase(records_str.size()-1);

	records_str += " ];";

	//�ҳ���վ������¼�������Сֵ
	FindMinMaxValue();

	return records_str;
}

typedef std::map<CTime,double>::iterator map_iter_type;

std::pair<map_iter_type,map_iter_type> 
GetRainBeginEnd(map_iter_type itb, map_iter_type ite, int max_hour_span)
{
	map_iter_type begin= std::find_if(itb,ite,is_map_value_nzero<CTime,double>),end,
		begin_next = begin;

	if(begin == ite) return std::make_pair(ite,ite);

	do
	{
		end = std::find_if(begin_next,ite,is_map_value_zero<CTime,double>);
		if(end == ite) break;

		begin_next = std::find_if(end,ite,is_map_value_nzero<CTime,double>);
		if(begin_next == ite) break;
	}while((begin_next->first - end->first).GetTotalHours()<=max_hour_span);

	return std::make_pair(begin,end);
}

// ת��Ϊ�ۼƽ�ˮֵ
void RainLineDlg::ToAccumulatedRain(std::map<CTime,double> & records)
{
	ToHourRain(records);

	using std::map;using std::pair;

	//�洢ÿ�ν�ˮ���ۼƽ�ˮ��
	map<CTime,double> result;

	//�ϴν�ˮ������ʱ��
	map_iter_type lastend;

	//��ˮ����ʼĩ
	std::pair<map_iter_type,map_iter_type> rainproc;

	lastend = records.begin();

	while(lastend != records.end() )
	{
		//���ν�ˮ
		rainproc = GetRainBeginEnd(lastend, records.end(), MAX_RAIN_SPAN_HOUR);

		map<CTime,double> thisresult;
		map_partial_sum(lastend, rainproc.second, thisresult);

		result.insert(thisresult.begin(),thisresult.end());

		lastend = rainproc.second;

	}
	records = result;
	

}

// ת��ΪСʱ��ˮ
//ɾ���м��0ֵ
void RainLineDlg::ToHourRain(std::map<CTime,double> & records)
{
	if(records.size() <3) return;

	bool del=false;
	for(std::map<CTime,double>::iterator it = ++records.begin();
		it != --records.end();it++)
	{
		std::map<CTime,double>::iterator p1 = it, p2=p1;
		p1--;  //������һλ��
		p2++;  //������һλ��

		if(!(p1->second || p2->second) && !it->second)
		{
			records.erase(it);
			it = p1; //��ָ��ָ��ɾ��Ԫ����һλ��
		}
	}
}

void RainLineDlg::OnBnClickedAccumulated()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw_type = ACCUMULATED;
}

void RainLineDlg::OnBnClickedRainbyhour()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	draw_type = RAINBYHOUR;
}

// �ҵ����һ�β�ѯ��������Сֵ
int RainLineDlg::FindMinMaxValue(void)
{
	std::map<CTime,double>::iterator pos;
	pos = std::min_element(mrecords.begin(),mrecords.end(),less_pair_value<const CTime,double>);
	min_values.push_back(pos->second);

	pos = std::max_element(mrecords.begin(),mrecords.end(),less_pair_value<const CTime,double>);
	max_values.push_back(pos->second);

	return 0;
}

// ��������һ�ν���������ʼʱ��
void RainLineDlg::CalcLastestTime(void)
{
	bool stop = false;

	CTime end_time = CTime::GetCurrentTime(),
		begin_time = end_time - CTimeSpan(30,0,0,0);

	while(!stop)
	{
		stop = true;
		for(size_t i=0;i!=stations.size();i++)
		{
			get_records(stations[i],awssql::HOURRAIN,mrecords,begin_time,end_time);

			ToAccumulatedRain(mrecords);

			std::map<CTime,double>::reverse_iterator itb,ite;
			itb = std::find_if(mrecords.rbegin(),mrecords.rend(),is_map_value_nzero<CTime,double>);
			ite = std::find_if(itb,mrecords.rend(),is_map_value_zero<CTime,double>);

			if( itb==mrecords.rend() || ite==mrecords.rend() 
			||++itb==mrecords.rend() || ++ite==mrecords.rend())
			{
				begin_time -= CTimeSpan(30,0,0,0);
				stop = false;
				break;
			}
			else //����һ�ν�ˮ
			{
				--itb;  
				--ite;

				if(ite->first < LeftTime)  LeftTime = ite->first;
				if(itb->first > RightTime) RightTime= itb->first;

			}
		}
	}
	
	RightTime += CTimeSpan(0,1,0,0);
}
