// MeteorSearchB.cpp : 实现文件
//

#include "stdafx.h"
#include "generate-line.h"
#include "MeteorSearchB.h"
#include "ShowSearchResult.h"
#include <map-useful.h>

// MeteorSearchB 对话框

IMPLEMENT_DYNAMIC(MeteorSearchB, CDialog)

MeteorSearchB::MeteorSearchB(CWnd* pParent /*=NULL*/)
	: CDialog(MeteorSearchB::IDD, pParent)
{
	end_day = CTime::GetCurrentTime();

	begin_day = end_day - CTimeSpan(1,0,0,0);

	begin_hour = 20;
	end_hour = 20;

	is_anyhour_set = false;
}

MeteorSearchB::~MeteorSearchB()
{
}

void MeteorSearchB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, begin_day);
	DDX_Text(pDX, IDC_EDIT_BEGINHOUR, begin_hour);
	DDV_MinMaxInt(pDX, begin_hour, 0, 23);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, end_day);
	DDX_Text(pDX, IDC_EDIT_ENDHOUR, end_hour);
	DDV_MinMaxInt(pDX, end_hour, 0, 23);
	DDX_Control(pDX, IDC_BUTTON_BACK, back_button);
	DDX_Control(pDX, IDC_BUTTON_FORWARD, forward_button);
}


BEGIN_MESSAGE_MAP(MeteorSearchB, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &MeteorSearchB::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, &MeteorSearchB::OnBnClickedButtonForward)
		ON_BN_CLICKED(IDC_RADIO_ANYTIME, &MeteorSearchB::OnBnClickedRadioAnyHour)
//		ON_BN_CLICKED(IDC_MAXWIND, &MeteorSearchB::OnBnClickedMaxwind)
ON_BN_CLICKED(IDC_RADIO_TODAY, &MeteorSearchB::OnBnClickedRadioToday)
ON_BN_CLICKED(IDC_RADIO_YEASTERDAY, &MeteorSearchB::OnBnClickedRadioYeasterday)
ON_BN_CLICKED(IDC_RADIO_CURMONTH, &MeteorSearchB::OnBnClickedRadioCurmonth)
ON_BN_CLICKED(IDC_RADIO_LASTMONTH, &MeteorSearchB::OnBnClickedRadioLastmonth)
ON_BN_CLICKED(IDC_CHECK_ALLSTATION, &MeteorSearchB::OnBnClickedCheckAllstation)
ON_BN_CLICKED(IDC_CHECK_SELECT_ALL, &MeteorSearchB::OnBnClickedCheckSelectAll)
ON_BN_CLICKED(IDC_BUTTON_BEGIN_SEARCH, &MeteorSearchB::OnBnClickedButtonBeginSearch)
END_MESSAGE_MAP()


// MeteorSearchB 消息处理程序
void MeteorSearchB::OnBnClickedButtonBack()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	this->begin_day -= CTimeSpan(1,0,0,0);
	this->end_day   -= CTimeSpan(1,0,0,0);

	UpdateData(FALSE);
}

void MeteorSearchB::OnBnClickedButtonForward()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	this->begin_day += CTimeSpan(1,0,0,0);
	this->end_day   += CTimeSpan(1,0,0,0);

	UpdateData(FALSE);
}

void MeteorSearchB::OnBnClickedRadioAnyHour()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();

}

// 根据选项的变化隐藏或显示窗口
void MeteorSearchB::ButtonShowHideWindow(void)
{
	is_anytime_set = ((CButton *)GetDlgItem(IDC_RADIO_ANYTIME))->GetCheck();

	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(is_anytime_set);
	GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(is_anytime_set);
	GetDlgItem(IDC_EDIT_BEGINHOUR)->EnableWindow(is_anytime_set);
	GetDlgItem(IDC_EDIT_ENDHOUR)->EnableWindow(is_anytime_set);

	int n_show = SW_HIDE;
	if(is_anytime_set) n_show = SW_SHOW;
	back_button.ShowWindow(n_show);
	forward_button.ShowWindow(n_show);

}

// 将所有选项数值化，作为启动参数
void MeteorSearchB::GetStartArgument(void)
{
	UpdateData(TRUE);

	//获取开始和结束的准确时间
	begin_time = CTime(begin_day.GetYear(),begin_day.GetMonth(),begin_day.GetDay(),begin_hour,0,0);
	end_time = CTime(end_day.GetYear(),end_day.GetMonth(),end_day.GetDay(),end_hour,0,0);

	//获取选择的站点
	select_stations.clear();
	for(int i=IDC_CHECK_YIYANG; i <= IDC_CHECK_SONGXIAN; i++)
	{
		if( ((CButton *)GetDlgItem(i))->GetCheck() )
		{
			switch(i)
			{
			case IDC_CHECK_YIYANG:
				select_stations.push_back(57065);break;
			case IDC_CHECK_LUONING:
				select_stations.push_back(57066);break;
			case IDC_CHECK_XINAN:
				select_stations.push_back(57070);break;
			case IDC_CHECK_MENGJIN:
				select_stations.push_back(57071);break;
			case IDC_CHECK_YICHUAN:
				select_stations.push_back(57074);break;
			case IDC_CHECK_YANSHI:
				select_stations.push_back(57076);break;
			case IDC_CHECK_LUANCHUAN:
				select_stations.push_back(57077);break;
			case IDC_CHECK_RUYANG:
				select_stations.push_back(57078);break;
			case IDC_CHECK_SONGXIAN:
				select_stations.push_back(57162);break;
			default:
				break;
			}
		}
	}

	//获取选择的要素
	select_element.clear();
	head_titles.clear();
	head_titles.push_back("区站号");
	for(int i=IDC_CHECK_HIGH_TEMPH; i <= IDC_CHECK_ACCU_RAIN; i++)
	{
		if(!((CButton *)GetDlgItem(i))->GetCheck()) continue;

		switch(i)
		{//HIGH_TEMPH,LOW_TEMPH,MAX_WIND,MAX_10WIND,HIGH_STN_PRESS,LOW_STN_PRESS,ACCU_RAIN
		case IDC_CHECK_HIGH_TEMPH:
			select_element.push_back(HIGH_TEMPH); 
			head_titles.push_back("最高气温");
			break;
		case IDC_CHECK_LOW_TEMPH:
			select_element.push_back(LOW_TEMPH); 
			head_titles.push_back("最低气温");
			break;
		case IDC_CHECK_MAX_WIND:
			select_element.push_back(MAX_WIND);
			head_titles.push_back("极大风速");
			break;
		case IDC_CHECK_MAX_10WIND:
			select_element.push_back(MAX_10WIND);
			head_titles.push_back("最大风速");
			break;
		case IDC_CHECK_HIGH_STN_PRESS:
			select_element.push_back(HIGH_STN_PRESS);
			head_titles.push_back("最高气压");
			break;
		case IDC_CHECK_LOW_STN_PRESS:
			select_element.push_back(LOW_STN_PRESS);
			head_titles.push_back("最低气压");
			break;
		case IDC_CHECK_ACCU_RAIN:
			select_element.push_back(ACCU_RAIN);
			head_titles.push_back("累计降水量");
			break;
		default:
			break;
		}

	}

}


void MeteorSearchB::OnBnClickedRadioToday()
{
	// TODO: 在此添加控件通知处理程序代码
	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(1,0,0,0);

	if(end_hour ==8)
	{
		OnBnClickedButtonForward();
	}
	else if(is_anyhour_set)
	{
		begin_day = end_day;
	}

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearchB::OnBnClickedRadioYeasterday()
{
	// TODO: 在此添加控件通知处理程序代码
	end_day = CTime::GetCurrentTime()- CTimeSpan(1,0,0,0);
	begin_day = end_day - CTimeSpan(1,0,0,0);

	if(end_hour ==8)
	{
		OnBnClickedButtonForward();
	}
	else if(is_anyhour_set)
	{
		begin_day = end_day;
	}

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearchB::OnBnClickedRadioCurmonth()
{
	// TODO: 在此添加控件通知处理程序代码
	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(end_day.GetDay()-1,0,0,0);

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearchB::OnBnClickedRadioLastmonth()
{
	// TODO: 在此添加控件通知处理程序代码
	CTime CurTime = CTime::GetCurrentTime();
	end_day = CurTime - CTimeSpan(CurTime.GetDay(),0,0,0);
	begin_day = CTime(end_day.GetYear(),end_day.GetMonth(),1,0,0,0);

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearchB::OnBnClickedCheckAllstation()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isset = ((CButton *)GetDlgItem(IDC_CHECK_ALLSTATION))->GetCheck();

	for(int i=IDC_CHECK_YIYANG; i <= IDC_CHECK_SONGXIAN; i++)
	{
		((CButton *)GetDlgItem(i))->SetCheck(isset);
	}
}

void MeteorSearchB::OnBnClickedCheckSelectAll()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL isset = ((CButton *)GetDlgItem(IDC_CHECK_SELECT_ALL))->GetCheck();

	for(int i=IDC_CHECK_HIGH_TEMPH; i <= IDC_CHECK_ACCU_RAIN; i++)
	{
		((CButton *)GetDlgItem(i))->SetCheck(isset);
	}
}

BOOL MeteorSearchB::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CButton *)GetDlgItem(IDC_CHECK_ALLSTATION))->SetCheck(1);
	OnBnClickedCheckAllstation();

	if(end_hour == 20)
	{
		((CButton *)GetDlgItem(IDC_RADIO_TODAY))->SetCheck(1);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_RADIO_YEASTERDAY))->SetCheck(1);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void MeteorSearchB::OnBnClickedButtonBeginSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetStartArgument();

	ShowSearchResult show_result;
	
	CString time_str = begin_time.Format("(%Y-%m-%d %H")+end_time.Format("---%Y-%m-%d %H时)");
	show_result.title = "多站多要素综合查询"+time_str;
	show_result.headtitles = head_titles;
	
	view_contents.resize(head_titles.size());
	
	GetViewContent();
	show_result.contents = view_contents;

	if(show_result.DoModal() == IDCANCEL )
	{
	}
}

// 获取需要显示的内容
void MeteorSearchB::GetViewContent(void)
{
	std::map<CTime,double> value_array;
	std::map<CTime,awssql::wind_vector > vector_array;

	std::string cell_str;

	view_contents[0].clear();
	for(int j=0; j<select_stations.size();j++)
	{
		view_contents[0].push_back(to_string(select_stations[j]));
	}

	begin_time += CTimeSpan(0,1,0,0);

	for(int i=0; i < select_element.size(); i++)
	{
		view_contents[i+1].clear();
		for(int j=0; j<select_stations.size();j++)
		{
			switch(select_element[i])
			{//HIGH_TEMPH,LOW_TEMPH,MAX_WIND,MAX_10WIND,HIGH_STN_PRESS,LOW_STN_PRESS,ACCU_RAIN
			case HIGH_TEMPH:
				{//MAXVALUE,MINVALUE,ACCUMULATE};
					awssql::get_records(select_stations[j],awssql::HIGH_TEMPH,value_array,begin_time,end_time);
					cell_str = StatisticOnePeriod(value_array,MAXVALUE);
					break;
				}
			case LOW_TEMPH:
				{//MAXVALUE,MINVALUE,ACCUMULATE};
					awssql::get_records(select_stations[j],awssql::LOW_TEMPH,value_array,begin_time,end_time);
					cell_str = StatisticOnePeriod(value_array,MINVALUE);
					break;
				}
			case MAX_WIND:
				{//MAXVALUE,MINVALUE,ACCUMULATE};
					awssql::get_records(select_stations[j],awssql::MAX_WIND,vector_array,begin_time,end_time);
					cell_str = StatisticOnePeriod(vector_array,MAXVALUE);
					break;
				}
			case MAX_10WIND:
				{//MAXVALUE,MINVALUE,ACCUMULATE};
					awssql::get_records(select_stations[j],awssql::MAX_10_WIND,vector_array,begin_time,end_time);
					cell_str = StatisticOnePeriod(vector_array,MAXVALUE);
					break;
				}
			case HIGH_STN_PRESS:
				{//MAXVALUE,MINVALUE,ACCUMULATE};
					awssql::get_records(select_stations[j],awssql::STATION_ATMOS_PRESS,value_array,begin_time,end_time);
					cell_str = StatisticOnePeriod(value_array,MAXVALUE);
					break;
				}
			case LOW_STN_PRESS:
				{//MAXVALUE,MINVALUE,ACCUMULATE};
					awssql::get_records(select_stations[j],awssql::STATION_ATMOS_PRESS,value_array,begin_time,end_time);
					cell_str = StatisticOnePeriod(value_array,MINVALUE);
					break;
				}
			case ACCU_RAIN:
				{
					get_records(select_stations[j],awssql::HOURRAIN,value_array,begin_time,end_time);
					cell_str = StatisticAccumulate(value_array);
					break;
				}
			default:
				break;
			}

			view_contents[i+1].push_back(cell_str);

		}

	}

}

// 统计一个时段（最大最小值）
template<typename T>
std::string MeteorSearchB::StatisticOnePeriod(T& map, STATISWAY statis_way)
{
	//std::map<int,int>::mapped_type
	T::iterator begin=map.begin(),end=map.end(), pos;
	std::string return_value;

	if(statis_way == MINVALUE)//时段的最低值
	{
		pos = std::min_element(begin,end,less_pair_value<const CTime,T::mapped_type>);
		return_value = to_string(pos->second).c_str() + pos->first.Format("   %Y-%m-%d %H:%M:%S");
	}
	else if(statis_way == MAXVALUE)//时段的最高值
	{
		pos = std::max_element(begin,end,less_pair_value<const CTime,T::mapped_type>);
		return_value = to_string(pos->second).c_str() + pos->first.Format("   %Y-%m-%d %H:%M:%S");
	}
	//else if(statis_way == ACCUMULATE)
	//{
	//	return_value = std::accumulate(begin,end,return_value,add_pair_value<const CTime,T::mapped_type>);
	//}

	return return_value;
}

//计算要素的累计值
template<typename T>
std::string MeteorSearchB::StatisticAccumulate(T& map)
{
	std::pair<CTime,T::mapped_type> accumulate_value;
	accumulate_value = std::accumulate(map.begin(),map.end(),accumulate_value,add_pair_value<const CTime,T::mapped_type>);

	std::string return_value = to_string(accumulate_value.second);

	return return_value;
}
