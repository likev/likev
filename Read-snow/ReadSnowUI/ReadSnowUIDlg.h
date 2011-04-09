// ReadSnowUIDlg.h : 头文件
//

#pragma once
#include "snowLib/DealSnowData.h"

// CReadSnowUIDlg 对话框
class CReadSnowUIDlg : public CDialog
{
// 构造
public:
	CReadSnowUIDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_READSNOWUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonQuery();
	// 将数据写入文件
	bool WriteDataToFile(void);
	// 起始时刻
	CString beginHour;
	// 结束时刻
	CString endHour;
	// 开始日期
	CTime beginDay;
	// 结束日期
	CTime endDay;
	// 最初选择洛阳
	int selectRagion;

	std::vector<std::string> luoyangStationID,luoyangStationName,
							 henanStationID,henanStationName;

	void InitDataFromFile();

	int getSelectHour(CString hourString)const;

};
