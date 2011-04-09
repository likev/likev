// MeteorSearch.cpp : 实现文件
//

#include "stdafx.h"
#include "generate-line.h"
#include "MeteorSearch.h"
#include "ShowSearchResult.h"
#include <string-trans.h>
#include <map-useful.h>

// MeteorSearch 对话框

IMPLEMENT_DYNAMIC(MeteorSearch, CDialog)

MeteorSearch::MeteorSearch(CWnd* pParent /*=NULL*/)
: CDialog(MeteorSearch::IDD, pParent)

{
	end_day = CTime::GetCurrentTime();

	begin_day = end_day - CTimeSpan(1,0,0,0);

	if(end_day.GetHour() > 20)
	{
		begin_hour = 20;
		end_hour = 20;
	}
	else
	{
		begin_hour = 8;
		end_hour = 8;
	}

	is_anyhour_set = false;

}

MeteorSearch::~MeteorSearch()
{
}

void MeteorSearch::DoDataExchange(CDataExchange* pDX)
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


BEGIN_MESSAGE_MAP(MeteorSearch, CDialog)
	//	ON_BN_CLICKED(IDC_RADIO8, &MeteorSearch::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN_SEARCH, &MeteorSearch::OnBnClickedButtonBeginSearch)
	ON_BN_CLICKED(IDC_BUTTON_BACK, &MeteorSearch::OnBnClickedButtonBack)
	ON_BN_CLICKED(IDC_BUTTON_FORWARD, &MeteorSearch::OnBnClickedButtonForward)
	ON_BN_CLICKED(IDC_CHECK_ALLSTATION, &MeteorSearch::OnBnClickedCheckAllstation)
	ON_BN_CLICKED(IDC_RADIO_TODAY, &MeteorSearch::OnBnClickedRadioToday)
	ON_BN_CLICKED(IDC_RADIO_YEASTERDAY, &MeteorSearch::OnBnClickedRadioYeasterday)
	ON_BN_CLICKED(IDC_RADIO_CURMONTH, &MeteorSearch::OnBnClickedRadioCurmonth)
	ON_BN_CLICKED(IDC_RADIO_LASTMONTH, &MeteorSearch::OnBnClickedRadioLastmonth)
	ON_BN_CLICKED(IDC_RADIO_ANYTIME, &MeteorSearch::OnBnClickedRadioAnytime)
	ON_BN_CLICKED(IDC_RADIO_20_20, &MeteorSearch::OnBnClickedRadio2020)
	ON_BN_CLICKED(IDC_RADIO_08_08, &MeteorSearch::OnBnClickedRadio0808)
	ON_BN_CLICKED(IDC_RADIO_ANYHOUR, &MeteorSearch::OnBnClickedRadioAnyhour)
	ON_BN_CLICKED(IDC_RADIO_TEMPH, &MeteorSearch::OnBnClickedRadioTemph)
	ON_BN_CLICKED(IDC_RADIO_RAIN, &MeteorSearch::OnBnClickedRadioRain)
	ON_BN_CLICKED(IDC_RADIO_MAX_WIND, &MeteorSearch::OnBnClickedRadioMaxWind)
	ON_BN_CLICKED(IDC_RADIO_MAX_AVG_WIND, &MeteorSearch::OnBnClickedRadioMaxAvgWind)
	ON_BN_CLICKED(IDC_RADIO_STN_PRESS, &MeteorSearch::OnBnClickedRadioStnPress)
	ON_BN_CLICKED(IDC_RADIO_RELAT_HUMID, &MeteorSearch::OnBnClickedRadioRelatHumid)
	ON_BN_CLICKED(IDC_RADIO_MAX_VALUE, &MeteorSearch::OnBnClickedRadioMaxValue)
	ON_BN_CLICKED(IDC_RADIO_MIN_VALUE, &MeteorSearch::OnBnClickedRadioMinValue)
	ON_BN_CLICKED(IDC_RADIO_AVG_VALUE, &MeteorSearch::OnBnClickedRadioAvgValue)
	ON_BN_CLICKED(IDC_RADIO_HOUR_VALUE, &MeteorSearch::OnBnClickedRadioHourValue)
	ON_BN_CLICKED(IDC_RADIO_ACCUMULATE, &MeteorSearch::OnBnClickedRadioAccumulate)
	ON_BN_CLICKED(IDC_DrawResultLine, &MeteorSearch::OnBnClickedDrawresultline)
END_MESSAGE_MAP()


// MeteorSearch 消息处理程序

void MeteorSearch::OnBnClickedButtonBack()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	this->begin_day -= CTimeSpan(1,0,0,0);
	this->end_day   -= CTimeSpan(1,0,0,0);

	UpdateData(FALSE);
}

void MeteorSearch::OnBnClickedButtonForward()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	this->begin_day += CTimeSpan(1,0,0,0);
	this->end_day   += CTimeSpan(1,0,0,0);

	UpdateData(FALSE);
}

void MeteorSearch::OnBnClickedCheckAllstation()
{
	// TODO: 在此添加控件通知处理程序代码
	//
	BOOL isset = ((CButton *)GetDlgItem(IDC_CHECK_ALLSTATION))->GetCheck();

	for(int i=IDC_CHECK_YIYANG; i <= IDC_CHECK_SONGXIAN; i++)
	{
		((CButton *)GetDlgItem(i))->SetCheck(isset);
	}
}

BOOL MeteorSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CButton *)GetDlgItem(IDC_CHECK_ALLSTATION))->SetCheck(1);
	OnBnClickedCheckAllstation();

	if(end_hour == 20)
	{
		((CButton *)GetDlgItem(IDC_RADIO_TODAY))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO_20_20))->SetCheck(1);
	}
	else
	{
		((CButton *)GetDlgItem(IDC_RADIO_YEASTERDAY))->SetCheck(1);
		((CButton *)GetDlgItem(IDC_RADIO_08_08))->SetCheck(1);
	}

	((CButton *)GetDlgItem(IDC_RADIO_TEMPH))->SetCheck(1);
	((CButton *)GetDlgItem(IDC_RADIO_MAX_VALUE))->SetCheck(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void MeteorSearch::OnBnClickedRadioToday()
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

void MeteorSearch::OnBnClickedRadioYeasterday()
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

void MeteorSearch::OnBnClickedRadioCurmonth()
{
	// 本月时间设置
	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(end_day.GetDay()-1,0,0,0);

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioLastmonth()
{
	// 上个月时间设置
	CTime CurTime = CTime::GetCurrentTime();
	end_day = CurTime - CTimeSpan(CurTime.GetDay(),0,0,0);
	begin_day = CTime(end_day.GetYear(),end_day.GetMonth(),1,0,0,0);

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioAnytime()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();

}

void MeteorSearch::OnBnClickedRadio2020()
{
	// TODO: 在此添加控件通知处理程序代码
	begin_hour = end_hour = 20;

	if(((CButton *)GetDlgItem(IDC_RADIO_TODAY))->GetCheck() )
	{
		OnBnClickedRadioToday();
	}
	else if(((CButton *)GetDlgItem(IDC_RADIO_YEASTERDAY))->GetCheck() )
	{
		OnBnClickedRadioYeasterday();
	}

	UpdateData(FALSE);

	ButtonShowHideWindow();

}

void MeteorSearch::OnBnClickedRadio0808()
{
	// TODO: 在此添加控件通知处理程序代码
	begin_hour = end_hour = 8;

	if(((CButton *)GetDlgItem(IDC_RADIO_TODAY))->GetCheck() )
	{
		OnBnClickedRadioToday();
	}
	else if(((CButton *)GetDlgItem(IDC_RADIO_YEASTERDAY))->GetCheck() )
	{
		OnBnClickedRadioYeasterday();
	}

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioAnyhour()
{
	// TODO: 在此添加控件通知处理程序代码


	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioTemph()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioRain()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioMaxWind()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioMaxAvgWind()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioStnPress()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioRelatHumid()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioMaxValue()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioMinValue()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioAvgValue()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioHourValue()
{
	// TODO: 在此添加控件通知处理程序代码
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioAccumulate()
{
	// TODO: 在此添加控件通知处理程序代码
}

// 根据选项的变化隐藏或显示窗口
void MeteorSearch::ButtonShowHideWindow(void)
{
	BOOL is_whole_point_set = ((CButton *)GetDlgItem(IDC_RADIO_HOUR_VALUE))->GetCheck();
	if(is_whole_point_set)
	{//统计整点值时
		int id_now_check = GetCheckedRadioButton(IDC_RADIO_20_20,IDC_RADIO_ANYHOUR);
		((CButton *)GetDlgItem(id_now_check))->SetCheck(0);
		((CButton *)GetDlgItem(IDC_RADIO_ANYHOUR))->SetCheck(1);
	}

	is_anytime_set = ((CButton *)GetDlgItem(IDC_RADIO_ANYTIME))->GetCheck();
	is_anyhour_set = ((CButton *)GetDlgItem(IDC_RADIO_ANYHOUR))->GetCheck();

	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(is_anytime_set);
	GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(is_anytime_set);
	GetDlgItem(IDC_EDIT_BEGINHOUR)->EnableWindow(is_anyhour_set);
	GetDlgItem(IDC_EDIT_ENDHOUR)->EnableWindow(is_anyhour_set);

	int n_show = SW_HIDE;
	if(is_anytime_set) n_show = SW_SHOW;
	back_button.ShowWindow(n_show);
	forward_button.ShowWindow(n_show);

	//是否选择风速
	BOOL is_max_wind_set    = ((CButton *)GetDlgItem(IDC_RADIO_MAX_WIND))->GetCheck(),
		is_max_10_wind_set  = ((CButton *)GetDlgItem(IDC_RADIO_MAX_AVG_WIND))->GetCheck();

	int	n_show2 = SW_SHOW;
	if(is_max_wind_set || is_max_10_wind_set)
		n_show2 = SW_HIDE;

	GetDlgItem(IDC_RADIO_MIN_VALUE)->ShowWindow(n_show2);
	GetDlgItem(IDC_RADIO_AVG_VALUE)->ShowWindow(n_show2);
	GetDlgItem(IDC_RADIO_ACCUMULATE)->ShowWindow(n_show2);

}


//搜索启动
void MeteorSearch::OnBnClickedButtonBeginSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	GetStartArgument();
	GetRequiredRecords();

	view_contents.resize(select_stations.size()+1);

	//风矢量的查询
	if(is_wind_query)
	{
		AnalysisAllRecords(vector_records);
	}
	else
	{
		AnalysisAllRecords(value_records);
	}

	ShowSearchResult show_result;

	SetResultTitles(show_result.title);
	SetHeadTitle(show_result.headtitles);

	show_result.contents = view_contents;

	if(show_result.DoModal() == IDCANCEL )
	{
	}
}
// 将所有选项数值化，作为启动参数
void MeteorSearch::GetStartArgument(void)
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

	//获取选择的时间段
	int hour_span_id = GetCheckedRadioButton(IDC_RADIO_20_20,IDC_RADIO_ANYHOUR);
	switch(hour_span_id)
	{
	case IDC_RADIO_20_20:
		hour_span = HS2020; 
		break;
	case IDC_RADIO_08_08:
		hour_span = HS0808; 
		break;
	case IDC_RADIO_ANYHOUR:
		hour_span = HSANY;
		break;
	default:
		break;
	}

	//获取选择的要素
	int element_id = GetCheckedRadioButton(IDC_RADIO_TEMPH,IDC_RADIO_RELAT_HUMID);
	switch(element_id)
	{
	case IDC_RADIO_TEMPH:
		select_element = TEMPH; 
		break;
	case IDC_RADIO_RAIN:
		select_element = RAIN; 
		break;
	case IDC_RADIO_MAX_WIND:
		select_element = MAXWIND;
		break;
	case IDC_RADIO_MAX_AVG_WIND:
		select_element = MAXAVGWIND;
		break;
	case IDC_RADIO_STN_PRESS:
		select_element = STNPRESS;
		break;
	case IDC_RADIO_RELAT_HUMID:
		select_element = RELATHUMID;
		break;

	default:
		break;
	}

	//是否为风矢量查询
	is_wind_query = (select_element == MAXWIND || select_element == MAXAVGWIND);

	//获取统计的方式
	int statis_way_id = GetCheckedRadioButton(IDC_RADIO_MAX_VALUE,IDC_RADIO_ACCUMULATE);
	switch(statis_way_id)
	{
	case IDC_RADIO_MAX_VALUE:
		statis_way = MAXVALUE;
		break;
	case IDC_RADIO_MIN_VALUE:
		statis_way = MINVALUE;
		break;
	case IDC_RADIO_AVG_VALUE:
		statis_way = AVGVALUE;
		break;
	case IDC_RADIO_HOUR_VALUE:
		statis_way = WHOLEPOINT;
		break;
	case IDC_RADIO_ACCUMULATE:
		statis_way = ACCUMULATE;
		break;
	default:
		break;
	}

}

// 获取显示表格的表头
bool MeteorSearch::SetHeadTitle(std::vector<std::string> & headtitles)
{
	headtitles.clear();

	headtitles.push_back("时间");

	for(size_t i=0;i<select_stations.size();i++)
	{
		headtitles.push_back(to_string(select_stations[i]));
	}

	return false;
}

// 设置结果对话框的标题
void MeteorSearch::SetResultTitles(CString & title)
{
	CString time_str, hour_span_str, element_str, statis_str;
	switch(hour_span)
	{
	case HS2020:
		hour_span_str = "20-20时";
		break;
	case HS0808:
		hour_span_str = "08-08时";
		break;
	default:
		break;
	}

	switch(select_element)
	{
	case TEMPH:
		element_str = "温度";
		break;
	case RAIN: 
		element_str = "降水";
		break;
	case MAXWIND:
		element_str = "极大风速";
		break;
	case MAXAVGWIND:
		element_str = "最大风速";
		break;
	case STNPRESS:
		element_str = "本站气压";
		break;
	case RELATHUMID:
		element_str = "相对湿度";
		break;

	default:
		break;
	}

	switch(statis_way)
	{
	case MAXVALUE:
		statis_str = "最大值";
		break;
	case MINVALUE:
		statis_str = "最小值";
		break;
	case AVGVALUE:
		statis_str = "平均值";
		break;
	case WHOLEPOINT:
		statis_str = "整点值";
		break;
	case ACCUMULATE:
		statis_str = "累计值";
		break;
	default:
		break;
	}

	//标题
	time_str = begin_time.Format("%Y-%m-%d %H")+end_time.Format("---%Y-%m-%d %H时");

	title.Format("%s %s %s %s",time_str,hour_span_str,element_str,statis_str);

}

// 获取查询需要的所有记录
void MeteorSearch::GetRequiredRecords(void)
{
	//...value_records vector_records...;
	//选择的时间段 HOURSPAN hour_span;
	//需要统计的元素 ELEMENT select_element;
	//选择的统计量 STATISWAY statis_way;
	if(select_element==TEMPH && statis_way==MAXVALUE)
	{//温度最高值
		query_element = awssql::HIGH_TEMPH;
	}
	else if(select_element==TEMPH && statis_way==MINVALUE)
	{//温度最低值
		query_element = awssql::LOW_TEMPH;
	}
	else if(select_element==TEMPH && (statis_way==WHOLEPOINT || statis_way==AVGVALUE) )
	{//温度整点值
		query_element = awssql::TEMPH;
	}
	else if(select_element==RAIN)
	{//雨量
		query_element = awssql::HOURRAIN;
	}
	else if(select_element==MAXWIND)
	{//极大风速
		query_element = awssql::MAX_WIND;
	}
	else if(select_element==MAXAVGWIND)
	{//最大风速
		query_element = awssql::MAX_10_WIND;
	}
	else if(select_element==STNPRESS)
	{//本站气压
		query_element = awssql::STATION_ATMOS_PRESS;
	}


	//风矢量的查询
	if(this->is_wind_query)
	{
		vector_records.clear();
		for(std::vector<int>::iterator it=select_stations.begin();
			it != select_stations.end(); it++)
		{
			VectorArray per_records;
			awssql::get_records(*it,query_element,per_records,begin_time+CTimeSpan(0,1,0,0),end_time);
			vector_records[*it] = per_records;
		}
	}
	else //温度降水气压等查询
	{
		value_records.clear();
		for(std::vector<int>::iterator it=select_stations.begin();
			it != select_stations.end(); it++)
		{
			ValueArray per_records;
			awssql::get_records(*it,query_element,per_records,begin_time+CTimeSpan(0,1,0,0),end_time);
			value_records[*it] = per_records;
		}
	}
}

// 分析统计所有记录
template<typename T>
int MeteorSearch::AnalysisAllRecords(std::map<int,T> & records)
{
	std::map<int,T> all_results;

	for(size_t i=0;i<select_stations.size();i++)
	{	//每一个站的记录值序列
		T per_statis_result;

		if(statis_way==WHOLEPOINT)//风速整点值
		{
			per_statis_result = records[select_stations[i]];
		}
		else
		{//最大值等
			StatisticRecordsArray(records[select_stations[i]], per_statis_result);
		}

		all_results[select_stations[i]] = per_statis_result;

		view_contents.at(i+1).clear();
		for(T::iterator it = per_statis_result.begin();
			it != per_statis_result.end(); it++)
		{
			view_contents.at(i+1).push_back(to_string(it->second));
		}
	}

	GetViewFirstCol(all_results);

	return 0;
}


/*
根据选择的时段统计分析
降水温度等标量记录为value_records
风矢量记录为 vector_records

*/
template<typename T>
bool MeteorSearch::StatisticRecordsArray(T & origin, T & dest)
{
	dest.clear();
	typedef std::pair<CTime, T::mapped_type> V;
	V value;

	if(hour_span == HSANY)
	{//整个时段的最高值
		value = StatisticOnePeriod<V>(origin.begin(),origin.end());
		dest[value.first] = value.second;
	}
	else
	{
		T::iterator posbegin,posend;
		for(posbegin=origin.begin(); posbegin != origin.end();posbegin= posend)
		{
			//计算出当天结束时间
			CTime next_time = awssql::NearTime(posbegin->first,end_hour,false);
			//查找出所在位置
			posend = std::find_if(posbegin,origin.end(),pair_grater_by_time(next_time) );

			//计算出当天最高最低值
			value = StatisticOnePeriod<V>(posbegin,posend);
			dest[value.first] = value.second;

			//if(posend == origin.end()) break;
		}
	}

	return false;
}


// 统计一个时段（最大最小或平均值）
template<typename V,typename T>
V MeteorSearch::StatisticOnePeriod(T begin , T end)
{
	T pos;
	V return_value;

	if(statis_way == MINVALUE)//当前时段的最低值
	{
		pos = std::min_element(begin,end,less_pair_value<const CTime,double>);
		return_value = *pos;
	}
	else if(statis_way == MAXVALUE)//当前时段的最高值
	{
		pos = std::max_element(begin,end,less_pair_value<const CTime,double>);
		return_value = *pos;
	}
	else if(statis_way == AVGVALUE)
	{
		return_value = std::accumulate(begin,end,return_value,add_pair_value<const CTime,double>);
		return_value.second /= std::count_if(begin,end,return_define_value<bool>(true));
	}
	else if(statis_way == ACCUMULATE)
	{
		return_value = std::accumulate(begin,end,return_value,add_pair_value<const CTime,double>);
	}

	return return_value;
}

// 统计一个时段（风速最大值）
template<typename V>
V MeteorSearch::StatisticOnePeriod(VectorArray::iterator begin , VectorArray::iterator end)
{
	VectorArray::iterator pos;
	V return_value;

	if(statis_way == MAXVALUE)//当前时段的最高值
	{
		pos = std::max_element(begin,end,less_pair_value<const CTime,awssql::wind_vector>);
		return_value = *pos;
	}

	return return_value;
}

// 设置显示的第一列内容
template<typename T>
int MeteorSearch::GetViewFirstCol(std::map<int,T> & records)
{
	view_contents.at(0).clear();
	std::string time_str;
	for(CTime cur=begin_time + CTimeSpan(0,1,0,0); cur<=end_time;)
	{
		if(hour_span == HSANY)
		{
			if(statis_way == WHOLEPOINT)
			{
				time_str = cur.Format("%Y-%m-%d %H:00:00");
				cur += CTimeSpan(0,1,0,0);
			}
			else
			{
				time_str = begin_time.Format("%Y-%m-%d %H")+end_time.Format("-- %Y-%m-%d %H");
				cur = end_time + CTimeSpan(1,0,0,0);//本次结束后退出循环
			}
		}
		else if(hour_span == HS2020)
		{
			cur += CTimeSpan(1,0,0,0);
			time_str = cur.Format("%Y-%m-%d");
		}
		else if(hour_span == HS0808)
		{
			time_str = cur.Format("%Y-%m-%d");
			cur += CTimeSpan(1,0,0,0);
		}
		view_contents.at(0).push_back(time_str);
	}
	return 0;
}

void MeteorSearch::OnBnClickedDrawresultline()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox("正在完成此功能！","提示");
}
