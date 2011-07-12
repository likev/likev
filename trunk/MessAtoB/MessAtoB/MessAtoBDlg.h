// MessAtoBDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include <vector>
#include <string>
#include "Sglf.h"

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

	//站点信息
	std::vector<std::string> station_names;

	//城镇报转化为县区预报
	afx_msg void OnBnClickedChe();
	// 文本文件内容
	CEdit m_text;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();

	enum ForcastType{SMALLHOURS,MORNING,AM12121,AFTERNOON};
	//数据维护

	std::vector<std::vector<std::string>  > all_weather_str;
	std::vector<std::vector<double>  > all_temph_value;
	ForcastType forcast_type;
	std::string fhead,fstr;

	ForcastType GetForcastType();

	afx_msg void OnBnClickedButton1();
	afx_msg void OnSize(UINT nType, int cx, int cy);

	bool FtpDownCzbFile();
	bool is_czb_down_success;

	//处理数据并储存
	std::vector<Sglf> station_forcasts;
	bool read_trans_data();
	void begin_head(std::string &fhead);
	std::string generate121str();
	std::string generate_forcast_str();
	
	//输出24小时天气状况，最高最低温度
	void output_weather(std::stringstream & fout, int n=0);

	//获取喷药级别
	int GetPYGrade(const Sglf &station_forcast);
	afx_msg void OnBnClickedGeneratePy();
	afx_msg void OnBnClickedButtonSelfforcast();
	// 获取当前时次城镇报的文件名
	std::string GetFtpFilename(void);
	afx_msg void OnBnClickedButtonShortforcast();
};
