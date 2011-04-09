// DisasterWatchDlg.h : 头文件
//

#pragma once
#include "comn.h"
#include "string-trans.h"
#include "afxwin.h"

// CDisasterWatchDlg 对话框
class CDisasterWatchDlg : public CDialog
{
// 构造
public:
	CDisasterWatchDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_DISASTERWATCH_DIALOG };

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
public:
	afx_msg void OnBnClickedCheckAlert();
	afx_msg void OnBnClickedCheckSendMessage();
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);

	//任务栏图标信息
	NOTIFYICONDATA nid;
	// 隐藏到任务栏
	void HideToTray(void);

	// 开机自动运行
	void AutoRunAfterStart(void);

	// 是否自动报警
	BOOL auto_alert;
	// 自动发送短消息
	BOOL auto_send_message;

	int interval;
	std::string last_disaster_id;

	std::vector<std::string> all_stations, all_mobile_phone;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void BeginAllProc();
	bool CheckNewDisaster();
	void ReadNewDisaster();




	// 灾情描述
	CEdit disa_view;
	
	CString viewtext;
};
