// MultiThread1Dlg.h : 头文件
//

#pragma once
#include "CalculateThread.h"
#define WM_DISPLAY WM_USER+2

// CMultiThread1Dlg 对话框
class CMultiThread1Dlg : public CDialog
{
// 构造
public:
	CMultiThread1Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MULTITHREAD1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	CCalculateThread* m_pCalculateThread;

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
	// 线程数目
	volatile unsigned int thread_number;
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnDisplay(WPARAM wParam,LPARAM lParam);
};
