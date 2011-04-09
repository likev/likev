#pragma once
#include "afxwin.h"

#include <comn.h>
#include <read_aws_from_mysql.h>
// MeteorSearch �Ի���

class MeteorSearch : public CDialog
{
	DECLARE_DYNAMIC(MeteorSearch)

public:
	MeteorSearch(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MeteorSearch();

// �Ի�������
	enum { IDD = IDD_METEOR_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	enum HOURSPAN{HS0808,HS2020,HSANY};
	enum ELEMENT{TEMPH,RAIN,MAXWIND,MAXAVGWIND,STNPRESS,RELATHUMID};
	enum STATISWAY{MAXVALUE,MINVALUE,AVGVALUE,WHOLEPOINT,ACCUMULATE};

	// ��ѯ��ʼ����
	CTime begin_day;
	// ��ѯ��ʼʱ��
	int begin_hour;
	// ��ѯ��������
	CTime end_day;
	// ��ѯ����ʱ��
	int end_hour;

	BOOL is_anytime_set,is_anyhour_set;

	//�ӿؼ�������Ŀ�ʼ����ʱ��
	CTime begin_time,end_time;
	//��ѡ���վ��
	std::vector<int> select_stations;
	//ѡ���ʱ���
	HOURSPAN hour_span;
	//��Ҫͳ�Ƶ�Ԫ��
	ELEMENT select_element;
	//ѡ���ͳ����
	STATISWAY statis_way;

	bool is_wind_query;

	awssql::QUERY_ELEMENT query_element;

	typedef std::map<CTime,double> ValueArray;
	typedef std::map<CTime,awssql::wind_vector > VectorArray;
	std::map<int,ValueArray> value_records;
	std::map<int,VectorArray> vector_records;

	std::vector<std::vector<std::string> > view_contents;


public:
	afx_msg void OnBnClickedButtonBeginSearch();
	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonForward();
	afx_msg void OnBnClickedCheckAllstation();
	virtual BOOL OnInitDialog();
	// ����һ��
	CButton back_button;
	// ǰ��һ��
	CButton forward_button;
	afx_msg void OnBnClickedRadioToday();
	afx_msg void OnBnClickedRadioYeasterday();
	afx_msg void OnBnClickedRadioCurmonth();
	afx_msg void OnBnClickedRadioLastmonth();
	afx_msg void OnBnClickedRadioAnytime();
	afx_msg void OnBnClickedRadio2020();
	afx_msg void OnBnClickedRadio0808();
	afx_msg void OnBnClickedRadioAnyhour();
	afx_msg void OnBnClickedRadioTemph();
	afx_msg void OnBnClickedRadioRain();
	afx_msg void OnBnClickedRadioMaxWind();
	afx_msg void OnBnClickedRadioMaxAvgWind();
	afx_msg void OnBnClickedRadioStnPress();
	afx_msg void OnBnClickedRadioRelatHumid();
	afx_msg void OnBnClickedRadioMaxValue();
	afx_msg void OnBnClickedRadioMinValue();
	afx_msg void OnBnClickedRadioAvgValue();
	afx_msg void OnBnClickedRadioHourValue();
	afx_msg void OnBnClickedRadioAccumulate();
	// ����ѡ��ı仯���ػ���ʾ����
	void ButtonShowHideWindow(void);
	// ������ѡ����ֵ������Ϊ��������
	void GetStartArgument(void);
	// ��ȡ��ʾ���ı�ͷ
	bool SetHeadTitle(std::vector<std::string> & headtitle);
	// ���ý���Ի���ı���
	void SetResultTitles(CString & title);
	// ��ȡ��ѯ��Ҫ�����м�¼
	void GetRequiredRecords(void);
	// ����ͳ�����м�¼
	template<typename T>
	int AnalysisAllRecords(std::map<int,T> & records);
	
	// ����ѡ���ʱ��ͳ�Ʒ���
	template<typename T>
	bool StatisticRecordsArray(T & origin, T & dest);
	
	// ͳ��һ��ʱ�Σ�������Сֵ��
	template<typename V,typename T>
	V StatisticOnePeriod(T begin , T end);

	//ͳ�Ʒ��ٵ����ֵ �ػ�����
	template<typename V>
	V StatisticOnePeriod(VectorArray::iterator begin , VectorArray::iterator end);
	// ������ʾ�ĵ�һ������
	template<typename T>
	int GetViewFirstCol(std::map<int,T> & records);
	//int GetViewFirstCol(void);
	afx_msg void OnBnClickedDrawresultline();
};

class pair_grater_by_time
{
	CTime time;

public:
	pair_grater_by_time (const CTime t)
		:time(t){}

	template <typename T>
	bool operator() (const std::pair<const CTime,T> & thepair)
	{
		return thepair.first > time;
	}
};