#pragma once
#include "afxwin.h"

#include <comn.h>
#include <read_aws_from_mysql.h>
// MeteorSearch 对话框

class MeteorSearch : public CDialog
{
	DECLARE_DYNAMIC(MeteorSearch)

public:
	MeteorSearch(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MeteorSearch();

// 对话框数据
	enum { IDD = IDD_METEOR_SEARCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	enum HOURSPAN{HS0808,HS2020,HSANY};
	enum ELEMENT{TEMPH,RAIN,MAXWIND,MAXAVGWIND,STNPRESS,RELATHUMID};
	enum STATISWAY{MAXVALUE,MINVALUE,AVGVALUE,WHOLEPOINT,ACCUMULATE};

	// 查询开始日期
	CTime begin_day;
	// 查询开始时间
	int begin_hour;
	// 查询结束日期
	CTime end_day;
	// 查询结束时间
	int end_hour;

	BOOL is_anytime_set,is_anyhour_set;

	//从控件计算出的开始结束时间
	CTime begin_time,end_time;
	//所选择的站点
	std::vector<int> select_stations;
	//选择的时间段
	HOURSPAN hour_span;
	//需要统计的元素
	ELEMENT select_element;
	//选择的统计量
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
	// 后退一天
	CButton back_button;
	// 前进一天
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
	// 根据选项的变化隐藏或显示窗口
	void ButtonShowHideWindow(void);
	// 将所有选项数值化，作为启动参数
	void GetStartArgument(void);
	// 获取显示表格的表头
	bool SetHeadTitle(std::vector<std::string> & headtitle);
	// 设置结果对话框的标题
	void SetResultTitles(CString & title);
	// 获取查询需要的所有记录
	void GetRequiredRecords(void);
	// 分析统计所有记录
	template<typename T>
	int AnalysisAllRecords(std::map<int,T> & records);
	
	// 根据选择的时段统计分析
	template<typename T>
	bool StatisticRecordsArray(T & origin, T & dest);
	
	// 统计一个时段（最大或最小值）
	template<typename V,typename T>
	V StatisticOnePeriod(T begin , T end);

	//统计风速的最大值 特化函数
	template<typename V>
	V StatisticOnePeriod(VectorArray::iterator begin , VectorArray::iterator end);
	// 设置显示的第一列内容
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