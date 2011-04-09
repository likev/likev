// generate-lineDlg.h : 头文件
//

#pragma once


// CgeneratelineDlg 对话框
class CgeneratelineDlg : public CDialog
{
// 构造
public:
	CgeneratelineDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GENERATELINE_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	int ShowMinMaxTemph(int hour);
	afx_msg void OnBnClickedButtonMeteorStatisA();
	afx_msg void OnBnClickedButton7();
	// 累计降水量查询
	int AccumRainfall(int hour);
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButtonMeteorStatisB();
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
};
