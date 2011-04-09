//绘制指定时间段温度曲线

#pragma once

#include <comn.h>
// TemphLineDlg 对话框

class TemphLineDlg : public CDialog
{
	DECLARE_DYNAMIC(TemphLineDlg)

public:
	TemphLineDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TemphLineDlg();

// 对话框数据
	enum { IDD = IDD_TEMPH_LINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	enum {LAST3DAYS,LAST10DAYS,CURMONTH,LASTMONTH,ANYTIME};
public:

	int select_item;
	
	// 开始结束年月日
	CTime begin_day, end_day;
	// 开始结束小时
	int begin_hour, end_hour;

	//记录开始结束时间
	CTime LeftTime,RightTime;

	//所有站的最大最小值
	std::vector<double> min_values, max_values;

	//读取的站点
	std::vector<int> stations;
	//最近查询的记录
	std::map<CTime,double> mrecords;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAnyTime();
	// 选项改变
	void RadioChange(void);
	afx_msg void OnBnClickedLast3days();
	afx_msg void OnBnClickedLast10days();
	afx_msg void OnBnClickedCurmonth();
	afx_msg void OnBnClickedLastmonth();
	afx_msg void OnBnClickedDrawline();
	// 生成html文件
	int generate_html(void);

	std::string get_additional_info();
	// 获取单站的连续记录
	std::string get_records_str(int station_number);
	// 找到最近一次查询的最大和最小值
	int FindMinMaxValue(void);
};
