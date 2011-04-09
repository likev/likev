#pragma once

#include <comn.h>
#include <read_aws_from_mysql.h>

// MeteorSearchB �Ի���

class MeteorSearchB : public CDialog
{
	DECLARE_DYNAMIC(MeteorSearchB)

public:
	MeteorSearchB(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MeteorSearchB();

// �Ի�������
	enum { IDD = IDD_METEOR_SEARCH_B };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	enum HOURSPAN{HS0808,HS2020,HSANY};
	enum ELEMENT{HIGH_TEMPH,LOW_TEMPH,MAX_WIND,MAX_10WIND,HIGH_STN_PRESS,LOW_STN_PRESS,ACCU_RAIN};
	enum STATISWAY{MAXVALUE,MINVALUE,ACCUMULATE};

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
	//ѡ���ͳ����
	STATISWAY statis_way;
	
	//��Ҫͳ�Ƶ�Ԫ��
	std::vector<ELEMENT> select_element;
	std::vector<std::string> head_titles;

	bool is_wind_query;

	awssql::QUERY_ELEMENT query_element;

	std::vector<std::vector<std::string> > view_contents;

public:
	// ����orǰ��һ��
	CButton back_button, forward_button;

	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonForward();
	afx_msg void OnBnClickedRadioAnyHour();
	
	// ����ѡ��ı仯���ػ���ʾ����
	void ButtonShowHideWindow(void);
	// ������ѡ����ֵ������Ϊ��������
	void GetStartArgument(void);

//	afx_msg void OnBnClickedMaxwind();
	afx_msg void OnBnClickedRadioToday();
	afx_msg void OnBnClickedRadioYeasterday();
	afx_msg void OnBnClickedRadioCurmonth();
	afx_msg void OnBnClickedRadioLastmonth();
	afx_msg void OnBnClickedCheckAllstation();
	afx_msg void OnBnClickedCheckSelectAll();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBeginSearch();
	// ��ȡ��Ҫ��ʾ������
	void GetViewContent(void);

	template<typename T>
	std::string StatisticOnePeriod(T& map, STATISWAY statis_way);

	template<typename T>
	std::string StatisticAccumulate(T& map);
};
