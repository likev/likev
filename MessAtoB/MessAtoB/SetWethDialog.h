#pragma once

#include<vector>

// CSetWethDialog 对话框

class CSetWethDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetWethDialog)

public:
	CSetWethDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetWethDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_WET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
//实现

	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CString weather12;
	CString weather24;
	CString weather36;
	CString weather48;
//	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

public:
	enum ForcastPeriod{PERIOD12,PERIOD24,PERIOD36,PERIOD48};
	ForcastPeriod forcast_period;
	bool is_forcast48;
	std::vector<std::vector<int> > ischeck; 

	afx_msg void OnEnSetfocusEdit1();
	afx_msg void OnEnSetfocusEdit2();
	afx_msg void OnEnSetfocusEdit3();
	afx_msg void OnEnSetfocusEdit4();
	afx_msg void OnBnClickedButtonApl();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedCheckAll();
private:
	// 选择全部
	BOOL is_select_all;
	
public:
	afx_msg void OnBnClickedOk();
};
