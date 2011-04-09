// PlanRunDlg.h : 头文件
//

#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"


// CPlanRunDlg 对话框
class CPlanRunDlg : public CDialog
{
// 构造
public:
	CPlanRunDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_PLANRUN_DIALOG };

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
	afx_msg void OnBnClickedCancel();
	// 需要执行的命令
	CString command_line;
	afx_msg void OnDtnDatetimechangeDate(NMHDR *pNMHDR, LRESULT *pResult);
	// 命令执行的日期
	CDateTimeCtrl plan_date;
	// 命令执行的时间
	CDateTimeCtrl plan_time;
	// 所有任务的列表
	CListCtrl task_list;

	NOTIFYICONDATA nid;
	void HideToTray();


public:
	afx_msg void OnBnClickedAddtolist();
	afx_msg void OnBnClickedSelectapp();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam); 
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};

