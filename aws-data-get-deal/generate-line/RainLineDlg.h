#pragma once

#include <comn.h>
// RainLineDlg 对话框

class RainLineDlg : public CDialog
{
	DECLARE_DYNAMIC(RainLineDlg)

public:
	RainLineDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~RainLineDlg();

// 对话框数据
	enum { IDD = IDD_RAIN_LINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	enum DrawType{ACCUMULATED,RAINBYHOUR};
	// 开始结束年月日
	CTime begin_day, end_day;
	// 开始结束小时
	int begin_hour, end_hour;

	//记录开始结束时间
	CTime LeftTime,RightTime;

	//所有站的最大最小值
	std::vector<double> min_values, max_values;

	std::string plot_title;

	DrawType draw_type;//绘制过程降水或小时降水
	bool is_lastest_rain;

	int MAX_RAIN_SPAN_HOUR;//当两次降水小时差小于MAX_RAIN_SPAN_HOUR 时 认为是一次降水

	//读取的站点
	std::vector<int> stations;
	//最近查询的记录
	std::map<CTime,double> mrecords;
public:

//	afx_msg void OnBnClickedRanytime();
	afx_msg void OnBnSetfocusRanytime();
//	afx_msg void OnBnHotItemChangeRanytime(NMHDR *pNMHDR, LRESULT *pResult);
	// 单选按钮组改变
	int RadioChange(void);
	afx_msg void OnBnClickedRanytime();
	afx_msg void OnBnClickedLastestrain();
	afx_msg void OnBnClickedLast3hour();
	afx_msg void OnBnClickedLast6hour();
	afx_msg void OnBnClickedLast12hour();
	afx_msg void OnBnClickedLast24hour();
	afx_msg void OnBnClickedRtoday();
	afx_msg void OnBnClickedRyeasterday();
	afx_msg void OnBnClickedRcurmonth();
	afx_msg void OnBnClickedRlastmonth();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDrawline();

	// 生成html文件
	int generate_html(void);

	std::string get_additional_info();
	// 获取单站的连续记录
	std::string get_records_str(int station_number);
	// 转化为累计降水值
	void ToAccumulatedRain(std::map<CTime,double> & records);
	// 转化为小时降水
	void ToHourRain(std::map<CTime,double> & records);
	afx_msg void OnBnClickedAccumulated();
	afx_msg void OnBnClickedRainbyhour();
	// 找到最近一次查询的最大和最小值
	int FindMinMaxValue(void);
	// 计算出最近一次降雨量的起始时间
	void CalcLastestTime(void);
};
