// MeteorSearchB.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "generate-line.h"
#include "MeteorSearchB.h"
#include "ShowSearchResult.h"
#include <map-useful.h>

// MeteorSearchB �Ի���

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


// MeteorSearchB ��Ϣ�������
void MeteorSearchB::OnBnClickedButtonBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	this->begin_day -= CTimeSpan(1,0,0,0);
	this->end_day   -= CTimeSpan(1,0,0,0);

	UpdateData(FALSE);
}

void MeteorSearchB::OnBnClickedButtonForward()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	this->begin_day += CTimeSpan(1,0,0,0);
	this->end_day   += CTimeSpan(1,0,0,0);

	UpdateData(FALSE);
}

void MeteorSearchB::OnBnClickedRadioAnyHour()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ButtonShowHideWindow();

}

// ����ѡ��ı仯���ػ���ʾ����
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

// ������ѡ����ֵ������Ϊ��������
void MeteorSearchB::GetStartArgument(void)
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

	//��ȡѡ���Ҫ��
	select_element.clear();
	head_titles.clear();
	head_titles.push_back("��վ��");
	for(int i=IDC_CHECK_HIGH_TEMPH; i <= IDC_CHECK_ACCU_RAIN; i++)
	{
		if(!((CButton *)GetDlgItem(i))->GetCheck()) continue;

		switch(i)
		{//HIGH_TEMPH,LOW_TEMPH,MAX_WIND,MAX_10WIND,HIGH_STN_PRESS,LOW_STN_PRESS,ACCU_RAIN
		case IDC_CHECK_HIGH_TEMPH:
			select_element.push_back(HIGH_TEMPH); 
			head_titles.push_back("�������");
			break;
		case IDC_CHECK_LOW_TEMPH:
			select_element.push_back(LOW_TEMPH); 
			head_titles.push_back("�������");
			break;
		case IDC_CHECK_MAX_WIND:
			select_element.push_back(MAX_WIND);
			head_titles.push_back("�������");
			break;
		case IDC_CHECK_MAX_10WIND:
			select_element.push_back(MAX_10WIND);
			head_titles.push_back("������");
			break;
		case IDC_CHECK_HIGH_STN_PRESS:
			select_element.push_back(HIGH_STN_PRESS);
			head_titles.push_back("�����ѹ");
			break;
		case IDC_CHECK_LOW_STN_PRESS:
			select_element.push_back(LOW_STN_PRESS);
			head_titles.push_back("�����ѹ");
			break;
		case IDC_CHECK_ACCU_RAIN:
			select_element.push_back(ACCU_RAIN);
			head_titles.push_back("�ۼƽ�ˮ��");
			break;
		default:
			break;
		}

	}

}


void MeteorSearchB::OnBnClickedRadioToday()
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

void MeteorSearchB::OnBnClickedRadioYeasterday()
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

void MeteorSearchB::OnBnClickedRadioCurmonth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	end_day = CTime::GetCurrentTime();
	begin_day = end_day - CTimeSpan(end_day.GetDay()-1,0,0,0);

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearchB::OnBnClickedRadioLastmonth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTime CurTime = CTime::GetCurrentTime();
	end_day = CurTime - CTimeSpan(CurTime.GetDay(),0,0,0);
	begin_day = CTime(end_day.GetYear(),end_day.GetMonth(),1,0,0,0);

	UpdateData(FALSE);

	ButtonShowHideWindow();
}

void MeteorSearchB::OnBnClickedCheckAllstation()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL isset = ((CButton *)GetDlgItem(IDC_CHECK_ALLSTATION))->GetCheck();

	for(int i=IDC_CHECK_YIYANG; i <= IDC_CHECK_SONGXIAN; i++)
	{
		((CButton *)GetDlgItem(i))->SetCheck(isset);
	}
}

void MeteorSearchB::OnBnClickedCheckSelectAll()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	BOOL isset = ((CButton *)GetDlgItem(IDC_CHECK_SELECT_ALL))->GetCheck();

	for(int i=IDC_CHECK_HIGH_TEMPH; i <= IDC_CHECK_ACCU_RAIN; i++)
	{
		((CButton *)GetDlgItem(i))->SetCheck(isset);
	}
}

BOOL MeteorSearchB::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
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
	// �쳣: OCX ����ҳӦ���� FALSE
}

void MeteorSearchB::OnBnClickedButtonBeginSearch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	GetStartArgument();

	ShowSearchResult show_result;
	
	CString time_str = begin_time.Format("(%Y-%m-%d %H")+end_time.Format("---%Y-%m-%d %Hʱ)");
	show_result.title = "��վ��Ҫ���ۺϲ�ѯ"+time_str;
	show_result.headtitles = head_titles;
	
	view_contents.resize(head_titles.size());
	
	GetViewContent();
	show_result.contents = view_contents;

	if(show_result.DoModal() == IDCANCEL )
	{
	}
}

// ��ȡ��Ҫ��ʾ������
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

// ͳ��һ��ʱ�Σ������Сֵ��
template<typename T>
std::string MeteorSearchB::StatisticOnePeriod(T& map, STATISWAY statis_way)
{
	//std::map<int,int>::mapped_type
	T::iterator begin=map.begin(),end=map.end(), pos;
	std::string return_value;

	if(statis_way == MINVALUE)//ʱ�ε����ֵ
	{
		pos = std::min_element(begin,end,less_pair_value<const CTime,T::mapped_type>);
		return_value = to_string(pos->second).c_str() + pos->first.Format("   %Y-%m-%d %H:%M:%S");
	}
	else if(statis_way == MAXVALUE)//ʱ�ε����ֵ
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

//����Ҫ�ص��ۼ�ֵ
template<typename T>
std::string MeteorSearchB::StatisticAccumulate(T& map)
{
	std::pair<CTime,T::mapped_type> accumulate_value;
	accumulate_value = std::accumulate(map.begin(),map.end(),accumulate_value,add_pair_value<const CTime,T::mapped_type>);

	std::string return_value = to_string(accumulate_value.second);

	return return_value;
}
