// ForcastAnalysis2Doc.h : CForcastAnalysis2Doc 类的接口
//


#pragma once

#include <comn.h>
#include "city-message.h"
#include "statis_result.h"
#include "city_forecast.h"

class CForcastAnalysis2Doc : public CDocument
{
protected: // 仅从序列化创建
	CForcastAnalysis2Doc();
	DECLARE_DYNCREATE(CForcastAnalysis2Doc)

// 属性
public:

	//所有站点
	std::vector<int> station_nums;

	//总的统计结果
	std::map<int, stat_result> statistics;
	//每一天各站的数据
	std::vector<city_message> city_mess_day;
	std::vector<city_fst> perday_fst;

	//需要统计的开始和结束时间
	CTime stat_begin, stat_end;
	//当前分析的时间
	CTime cur_time;

	//需要统计的数据所在文件夹
	CString stat_floder;


// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CForcastAnalysis2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAnalyset();
	// 分析处理启动
	void BeginAnaly(void);
	// 读取选取时间段的城镇报
	bool ReadCityMessages(void);
	//处理每一天
	void PerdayDeal(void);

	//统计每一天数据
	void PerdayStat(void);
	// 读取需要分析的站点号
	bool ReadStationNums(void);
	// 统计单个县的各时次预报
	void PerCityStat(int station_number);
};


