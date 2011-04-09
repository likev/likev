#pragma once

#include <string>
// SelfForcast 对话框

class SelfForcast : public CDialog
{
	DECLARE_DYNAMIC(SelfForcast)

public:
	SelfForcast(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~SelfForcast();

// 对话框数据
	enum { IDD = IDD_DLG_SelfForcast };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString file_content;
	std::string ftp_filename;

	virtual BOOL OnInitDialog();

	bool PutSelfForcast();
	afx_msg void OnBnClickedOk();
};
