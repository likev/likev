#pragma once


// SelectDateSimple 对话框

class SelectDateSimple : public CDialog
{
	DECLARE_DYNAMIC(SelectDateSimple)

public:
	SelectDateSimple(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SelectDateSimple();

// 对话框数据
	enum { IDD = IDD_SELECT_DATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 选择的日期
	CTime date;
};
