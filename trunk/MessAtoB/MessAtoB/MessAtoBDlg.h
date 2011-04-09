// MessAtoBDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <string>

using std::vector;using std::string;


// CMessAtoBDlg 对话框
class CMessAtoBDlg : public CDialog
{
// 构造
public:
	CMessAtoBDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MESSATOB_DIALOG };

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
	afx_msg void OnBnClickedChe();
	// 文本文件内容
	CEdit m_text;
//	afx_msg void OnClose();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();

	//数据维护

	vector<vector<string>  > weth;
	vector<vector<double>  > teph;
	const int wht;
	string fhead,fstr;



	afx_msg void OnBnClickedButton1();
//	afx_msg void OnEnChangeEdit1();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
