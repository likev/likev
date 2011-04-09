// TemphLineDlg.cpp : 实现文件
//绘制指定时间段温度曲线

#include "stdafx.h"
#include "generate-line.h"
#include "TemphLineDlg.h"
#include <read_aws_from_mysql.h>
#include <map-useful.h>

// TemphLineDlg 对话框

IMPLEMENT_DYNAMIC(TemphLineDlg, CDialog)

TemphLineDlg::TemphLineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(TemphLineDlg::IDD, pParent)
	, select_item(LAST3DAYS)
{
	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(3,0,0,0);

	begin_hour = begin_day.GetHour();
	end_hour = end_day.GetHour();

	int ss[]={57065,57066,57070,57071,57074,57076,57077,57078,57162};
	stations.assign(ss,ss+9);
}

TemphLineDlg::~TemphLineDlg()
{
}

void TemphLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, begin_day);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, end_day);
	DDX_Text(pDX, IDC_BeginHour, begin_hour);
	DDX_Text(pDX, IDC_EndHour, end_hour);
	DDV_MinMaxInt(pDX, begin_hour, 0, 23);
	DDV_MinMaxInt(pDX, end_hour, 0, 23);
}


BEGIN_MESSAGE_MAP(TemphLineDlg, CDialog)
	ON_BN_CLICKED(IDC_AnyTime, &TemphLineDlg::OnBnClickedAnyTime)
	ON_BN_CLICKED(IDC_Last3Days, &TemphLineDlg::OnBnClickedLast3days)
	ON_BN_CLICKED(IDC_Last10Days, &TemphLineDlg::OnBnClickedLast10days)
	ON_BN_CLICKED(IDC_CurMonth, &TemphLineDlg::OnBnClickedCurmonth)
	ON_BN_CLICKED(IDC_LastMonth, &TemphLineDlg::OnBnClickedLastmonth)
	ON_BN_CLICKED(IDC_DrawLine, &TemphLineDlg::OnBnClickedDrawline)
END_MESSAGE_MAP()


// TemphLineDlg 消息处理程序

BOOL TemphLineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CheckDlgButton(IDC_Last3Days,1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void TemphLineDlg::OnBnClickedAnyTime()
{
	// TODO: 在此添加控件通知处理程序代码
	RadioChange();
}

// 选项改变
void TemphLineDlg::RadioChange(void)
{
	if(GetCheckedRadioButton(IDC_Last3Days,IDC_AnyTime) == IDC_AnyTime)
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
}

void TemphLineDlg::OnBnClickedLast3days()
{
	// TODO: 在此添加控件通知处理程序代码
	RadioChange();

	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(3,0,0,0);

	begin_hour = begin_day.GetHour();
	end_hour = end_day.GetHour();

	UpdateData(FALSE);
}

void TemphLineDlg::OnBnClickedLast10days()
{
	// TODO: 在此添加控件通知处理程序代码
	RadioChange();

	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(10,0,0,0);

	begin_hour = begin_day.GetHour();
	end_hour = end_day.GetHour();

	UpdateData(FALSE);
}

void TemphLineDlg::OnBnClickedCurmonth()
{
	// TODO: 在此添加控件通知处理程序代码
	RadioChange();

	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(end_day.GetDay()-1,0,0,0);

	begin_hour = 0;
	end_hour = end_day.GetHour();

	UpdateData(FALSE);
}

void TemphLineDlg::OnBnClickedLastmonth()
{
	// TODO: 在此添加控件通知处理程序代码
	RadioChange();

	CTime CurTime = CTime::GetCurrentTime();
	end_day = CurTime - CTimeSpan(CurTime.GetDay(),0,0,0);
	begin_day = CTime(end_day.GetYear(),end_day.GetMonth(),1,0,0,0);

	begin_hour = 0;
	end_hour = 23;

	UpdateData(FALSE);
}

bool CheckHourValid(int hour)
{
	if(hour<0 || hour>23)
		return false;

	return true;
}
void TemphLineDlg::OnBnClickedDrawline()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	if(!CheckHourValid(begin_hour)) return;
	if(!CheckHourValid(end_hour) ) return;

	LeftTime  = CTime(begin_day.GetYear(),begin_day.GetMonth(),begin_day.GetDay(),begin_hour,0,0);
	RightTime = CTime(end_day.GetYear(),end_day.GetMonth(),end_day.GetDay(),end_hour,0,0);

	generate_html();

	char app_buf[1024],path_buf[1024];
	DWORD result1 = GetPrivateProfileString("filepath","htmlapp","C:\\Program Files\\Internet Explorer\\iexplore.exe",app_buf,1000,"./glsetup.ini");

	GetCurrentDirectory(1024,path_buf);
	CString apppath = app_buf,
		filepath = CString(path_buf) + "\\draw-line\\temph-line.html";

	//执行
	PROCESS_INFORMATION proif;
	STARTUPINFO stif = {sizeof(stif)};

	BOOL res = ::CreateProcess(NULL,("\""+apppath+"\" \""+filepath+"\"").GetBuffer(),NULL,NULL,FALSE,0,NULL,NULL,&stif,&proif);

}

std::string TemphLineDlg::get_additional_info()
{
	using namespace std;

	int hours_plus = int((RightTime-LeftTime).GetTotalHours()/6);

	CString xleft = (LeftTime - CTimeSpan(0,5,0,0)).Format("'%Y-%m-%d %H:00'"),
		    xright= (RightTime + CTimeSpan(0,hours_plus,0,0)).Format("'%Y-%m-%d %H:00'");

	std::vector<double>::iterator pos_min, pos_max;
	pos_min = std::min_element(min_values.begin(), min_values.end());
	pos_max = std::max_element(max_values.begin(), max_values.end());

	int min_value = int(*pos_min+0.5), max_value = int(*pos_max+0.5);
	min_value = min_value - min_value%2 - 4;
	max_value = max_value + max_value%2 + 4;

	CString records, time_range, value_range;
	time_range.Format("var mintime = %s, maxtime= %s;",xleft,xright);
	//var min_value = -4, max_value = 36, tick_interval = 2;
	value_range.Format("\n  var min_value = %d, max_value = %d, tick_interval = 2;",min_value, max_value);

	return (LPCSTR)(time_range+value_range);
}

// 生成html文件
int TemphLineDlg::generate_html(void)
{
	std::string filecontent;
	filetostr("draw-line\\temph-line.html",filecontent);

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

	strtofile("draw-line\\temph-line.html",filecontent);

	return 0;
}

// 获取单站的连续记录
std::string TemphLineDlg::get_records_str(int station_number)
{
	using namespace std;	

	int rows = get_records(station_number,awssql::TEMPH,mrecords,LeftTime,RightTime);
	
	CString  dayrecord;
	string records_str="var l"+to_string(station_number)+" = [ ";

	if(!rows)//没有记录
		return records_str+ "];";

	for(map<CTime,double>::iterator it = mrecords.begin();
		it != mrecords.end(); it++)
	{
		dayrecord = it->first.Format("['%Y-%m-%d %H:00',");
		dayrecord.Format("%s'%4.1f'],",dayrecord,it->second);

		records_str += dayrecord;
	}
	records_str.erase(records_str.size()-1);

	records_str += " ];";

	//找出单站连续记录的最大最小值
	FindMinMaxValue();

	return records_str;
}


// 找到最近一次查询的最大和最小值
int TemphLineDlg::FindMinMaxValue(void)
{
	std::map<CTime,double>::iterator pos;
	pos = std::min_element(mrecords.begin(),mrecords.end(),less_pair_value<const CTime,double>);
	min_values.push_back(pos->second);

	pos = std::max_element(mrecords.begin(),mrecords.end(),less_pair_value<const CTime,double>);
	max_values.push_back(pos->second);
	
	return 0;
}
