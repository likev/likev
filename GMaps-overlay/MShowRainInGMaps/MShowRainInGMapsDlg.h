// MShowRainInGMapsDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "gprs-rain-line.h"

// CMShowRainInGMapsDlg 对话框
class CMShowRainInGMapsDlg : public CDialog
{
// 构造
public:
	CMShowRainInGMapsDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MSHOWRAININGMAPS_DIALOG };

	//---数据---
	GprsRainRecord records;

	bool is_real_rain;
	
	int net_type; //网络连接方式
	std::string server,url;
	
	CTime begin_day, end_day; // 开始结束日期
	
	CTime begin_time, end_time; // 开始结束时间
	
	int interval; // 刷新时间
	CSpinButtonCtrl spin_interval;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	//任务栏图标信息
	NOTIFYICONDATA nid;
	// 隐藏到任务栏
	void HideToTray(void);

	void ChangeViewType();
	void ChangeNetType();
	void UpdateRainValue();
	
	afx_msg void OnBnClickedRadioRealrain();
	afx_msg void OnBnClickedRadioHistoryrain();
	
	afx_msg void OnBnClickedRadioInnernet();
	afx_msg void OnBnClickedRadioOutsidenet();
	afx_msg void OnBnClickedButtonSearch();
	
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// 程序运行状态
	CString status_info;
};
