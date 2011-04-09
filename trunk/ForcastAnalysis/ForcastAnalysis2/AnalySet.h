#pragma once


// AnalySet 对话框

class AnalySet : public CDialog
{
	DECLARE_DYNAMIC(AnalySet)

public:
	AnalySet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AnalySet();

// 对话框数据
	enum { IDD = IDD_ANALYSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 开始时间
	CTime begin;
	// 结束时间
	CTime end;
	// 文件夹路径
	CString folder;
	// 选中的时次
	int checked_times;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedFloderset();
};
