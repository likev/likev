// MeteorSearch.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "generate-line.h"
#include "MeteorSearch.h"
#include "ShowSearchResult.h"
#include <string-trans.h>
#include <map-useful.h>

// MeteorSearch �Ի���

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


// MeteorSearch ��Ϣ�������

void MeteorSearch::OnBnClickedButtonBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	this->begin_day -= CTimeSpan(1,0,0,0);
	this->end_day   -= CTimeSpan(1,0,0,0);

	UpdateData(FALSE);
}

void MeteorSearch::OnBnClickedButtonForward()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	this->begin_day += CTimeSpan(1,0,0,0);
	this->end_day   += CTimeSpan(1,0,0,0);

	UpdateData(FALSE);
}

void MeteorSearch::OnBnClickedCheckAllstation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}

void MeteorSearch::OnBnClickedRadioToday()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// ����ʱ������
	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(end_day.GetDay()-1,0,0,0);

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioLastmonth()
{
	// �ϸ���ʱ������
	CTime CurTime = CTime::GetCurrentTime();
	end_day = CurTime - CTimeSpan(CurTime.GetDay(),0,0,0);
	begin_day = CTime(end_day.GetYear(),end_day.GetMonth(),1,0,0,0);

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioAnytime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();

}

void MeteorSearch::OnBnClickedRadio2020()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������


	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioTemph()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioRain()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioMaxWind()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioMaxAvgWind()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioStnPress()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioRelatHumid()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioMaxValue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioMinValue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioAvgValue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioHourValue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();
}

void MeteorSearch::OnBnClickedRadioAccumulate()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

// ����ѡ��ı仯���ػ���ʾ����
void MeteorSearch::ButtonShowHideWindow(void)
{
	BOOL is_whole_point_set = ((CButton *)GetDlgItem(IDC_RADIO_HOUR_VALUE))->GetCheck();
	if(is_whole_point_set)
	{//ͳ������ֵʱ
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

	//�Ƿ�ѡ�����
	BOOL is_max_wind_set    = ((CButton *)GetDlgItem(IDC_RADIO_MAX_WIND))->GetCheck(),
		is_max_10_wind_set  = ((CButton *)GetDlgItem(IDC_RADIO_MAX_AVG_WIND))->GetCheck();

	int	n_show2 = SW_SHOW;
	if(is_max_wind_set || is_max_10_wind_set)
		n_show2 = SW_HIDE;

	GetDlgItem(IDC_RADIO_MIN_VALUE)->ShowWindow(n_show2);
	GetDlgItem(IDC_RADIO_AVG_VALUE)->ShowWindow(n_show2);
	GetDlgItem(IDC_RADIO_ACCUMULATE)->ShowWindow(n_show2);

}


//��������
void MeteorSearch::OnBnClickedButtonBeginSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	GetStartArgument();
	GetRequiredRecords();

	view_contents.resize(select_stations.size()+1);

	//��ʸ���Ĳ�ѯ
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
// ������ѡ����ֵ������Ϊ��������
void MeteorSearch::GetStartArgument(void)
{
	UpdateData(TRUE);

	//��ȡ��ʼ�ͽ�����׼ȷʱ��
	begin_time = CTime(begin_day.GetYear(),begin_day.GetMonth(),begin_day.GetDay(),begin_hour,0,0);
	end_time = CTime(end_day.GetYear(),end_day.GetMonth(),end_day.GetDay(),end_hour,0,0);

	//��ȡѡ���վ��
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

	//��ȡѡ���ʱ���
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

	//��ȡѡ���Ҫ��
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

	//�Ƿ�Ϊ��ʸ����ѯ
	is_wind_query = (select_element == MAXWIND || select_element == MAXAVGWIND);

	//��ȡͳ�Ƶķ�ʽ
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

// ��ȡ��ʾ���ı�ͷ
bool MeteorSearch::SetHeadTitle(std::vector<std::string> & headtitles)
{
	headtitles.clear();

	headtitles.push_back("ʱ��");

	for(size_t i=0;i<select_stations.size();i++)
	{
		headtitles.push_back(to_string(select_stations[i]));
	}

	return false;
}

// ���ý���Ի���ı���
void MeteorSearch::SetResultTitles(CString & title)
{
	CString time_str, hour_span_str, element_str, statis_str;
	switch(hour_span)
	{
	case HS2020:
		hour_span_str = "20-20ʱ";
		break;
	case HS0808:
		hour_span_str = "08-08ʱ";
		break;
	default:
		break;
	}

	switch(select_element)
	{
	case TEMPH:
		element_str = "�¶�";
		break;
	case RAIN: 
		element_str = "��ˮ";
		break;
	case MAXWIND:
		element_str = "�������";
		break;
	case MAXAVGWIND:
		element_str = "������";
		break;
	case STNPRESS:
		element_str = "��վ��ѹ";
		break;
	case RELATHUMID:
		element_str = "���ʪ��";
		break;

	default:
		break;
	}

	switch(statis_way)
	{
	case MAXVALUE:
		statis_str = "���ֵ";
		break;
	case MINVALUE:
		statis_str = "��Сֵ";
		break;
	case AVGVALUE:
		statis_str = "ƽ��ֵ";
		break;
	case WHOLEPOINT:
		statis_str = "����ֵ";
		break;
	case ACCUMULATE:
		statis_str = "�ۼ�ֵ";
		break;
	default:
		break;
	}

	//����
	time_str = begin_time.Format("%Y-%m-%d %H")+end_time.Format("---%Y-%m-%d %Hʱ");

	title.Format("%s %s %s %s",time_str,hour_span_str,element_str,statis_str);

}

// ��ȡ��ѯ��Ҫ�����м�¼
void MeteorSearch::GetRequiredRecords(void)
{
	//...value_records vector_records...;
	//ѡ���ʱ��� HOURSPAN hour_span;
	//��Ҫͳ�Ƶ�Ԫ�� ELEMENT select_element;
	//ѡ���ͳ���� STATISWAY statis_way;
	if(select_element==TEMPH && statis_way==MAXVALUE)
	{//�¶����ֵ
		query_element = awssql::HIGH_TEMPH;
	}
	else if(select_element==TEMPH && statis_way==MINVALUE)
	{//�¶����ֵ
		query_element = awssql::LOW_TEMPH;
	}
	else if(select_element==TEMPH && (statis_way==WHOLEPOINT || statis_way==AVGVALUE) )
	{//�¶�����ֵ
		query_element = awssql::TEMPH;
	}
	else if(select_element==RAIN)
	{//����
		query_element = awssql::HOURRAIN;
	}
	else if(select_element==MAXWIND)
	{//�������
		query_element = awssql::MAX_WIND;
	}
	else if(select_element==MAXAVGWIND)
	{//������
		query_element = awssql::MAX_10_WIND;
	}
	else if(select_element==STNPRESS)
	{//��վ��ѹ
		query_element = awssql::STATION_ATMOS_PRESS;
	}


	//��ʸ���Ĳ�ѯ
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
	else //�¶Ƚ�ˮ��ѹ�Ȳ�ѯ
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

// ����ͳ�����м�¼
template<typename T>
int MeteorSearch::AnalysisAllRecords(std::map<int,T> & records)
{
	std::map<int,T> all_results;

	for(size_t i=0;i<select_stations.size();i++)
	{	//ÿһ��վ�ļ�¼ֵ����
		T per_statis_result;

		if(statis_way==WHOLEPOINT)//��������ֵ
		{
			per_statis_result = records[select_stations[i]];
		}
		else
		{//���ֵ��
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
����ѡ���ʱ��ͳ�Ʒ���
��ˮ�¶ȵȱ�����¼Ϊvalue_records
��ʸ����¼Ϊ vector_records

*/
template<typename T>
bool MeteorSearch::StatisticRecordsArray(T & origin, T & dest)
{
	dest.clear();
	typedef std::pair<CTime, T::mapped_type> V;
	V value;

	if(hour_span == HSANY)
	{//����ʱ�ε����ֵ
		value = StatisticOnePeriod<V>(origin.begin(),origin.end());
		dest[value.first] = value.second;
	}
	else
	{
		T::iterator posbegin,posend;
		for(posbegin=origin.begin(); posbegin != origin.end();posbegin= posend)
		{
			//������������ʱ��
			CTime next_time = awssql::NearTime(posbegin->first,end_hour,false);
			//���ҳ�����λ��
			posend = std::find_if(posbegin,origin.end(),pair_grater_by_time(next_time) );

			//���������������ֵ
			value = StatisticOnePeriod<V>(posbegin,posend);
			dest[value.first] = value.second;

			//if(posend == origin.end()) break;
		}
	}

	return false;
}


// ͳ��һ��ʱ�Σ������С��ƽ��ֵ��
template<typename V,typename T>
V MeteorSearch::StatisticOnePeriod(T begin , T end)
{
	T pos;
	V return_value;

	if(statis_way == MINVALUE)//��ǰʱ�ε����ֵ
	{
		pos = std::min_element(begin,end,less_pair_value<const CTime,double>);
		return_value = *pos;
	}
	else if(statis_way == MAXVALUE)//��ǰʱ�ε����ֵ
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

// ͳ��һ��ʱ�Σ��������ֵ��
template<typename V>
V MeteorSearch::StatisticOnePeriod(VectorArray::iterator begin , VectorArray::iterator end)
{
	VectorArray::iterator pos;
	V return_value;

	if(statis_way == MAXVALUE)//��ǰʱ�ε����ֵ
	{
		pos = std::max_element(begin,end,less_pair_value<const CTime,awssql::wind_vector>);
		return_value = *pos;
	}

	return return_value;
}

// ������ʾ�ĵ�һ������
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
				cur = end_time + CTimeSpan(1,0,0,0);//���ν������˳�ѭ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox("������ɴ˹��ܣ�","��ʾ");
}
