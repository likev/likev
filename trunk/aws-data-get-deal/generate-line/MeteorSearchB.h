#pragma once

#include <comn.h>
#include <read_aws_from_mysql.h>

// MeteorSearchB 对话框

class MeteorSearchB : public CDialog
{
	DECLARE_DYNAMIC(MeteorSearchB)

public:
	MeteorSearchB(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MeteorSearchB();

// 对话框数据
	enum { IDD = IDD_METEOR_SEARCH_B };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	enum HOURSPAN{HS0808,HS2020,HSANY};
	enum ELEMENT{HIGH_TEMPH,LOW_TEMPH,MAX_WIND,MAX_10WIND,HIGH_STN_PRESS,LOW_STN_PRESS,ACCU_RAIN};
	enum STATISWAY{MAXVALUE,MINVALUE,ACCUMULATE};

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
	//选择的统计量
	STATISWAY statis_way;
	
	//需要统计的元素
	std::vector<ELEMENT> select_element;
	std::vector<std::string> head_titles;

	bool is_wind_query;

	awssql::QUERY_ELEMENT query_element;

	std::vector<std::vector<std::string> > view_contents;

public:
	// 后退or前进一天
	CButton back_button, forward_button;

	afx_msg void OnBnClickedButtonBack();
	afx_msg void OnBnClickedButtonForward();
	afx_msg void OnBnClickedRadioAnyHour();
	
	// 根据选项的变化隐藏或显示窗口
	void ButtonShowHideWindow(void);
	// 将所有选项数值化，作为启动参数
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
	// 获取需要显示的内容
	void GetViewContent(void);

	template<typename T>
	std::string StatisticOnePeriod(T& map, STATISWAY statis_way);

	template<typename T>
	std::string StatisticAccumulate(T& map);
};
