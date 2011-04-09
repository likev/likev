#pragma once


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
	CString m_edit1;
	CString m_edit2;
	CString m_edit3;
	CString m_edit4;
	afx_msg void OnBnClickedButton1();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
