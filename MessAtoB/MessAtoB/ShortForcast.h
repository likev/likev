#pragma once

#include <string>
// ShortForcast 对话框

class ShortForcast : public CDialog
{
	DECLARE_DYNAMIC(ShortForcast)

public:
	ShortForcast(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ShortForcast();

// 对话框数据
	enum { IDD = IDD_DLG_ShortForcast };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString forcast_content,file_path;

	virtual BOOL OnInitDialog();

	bool PutShortForcast();
	afx_msg void OnBnClickedOk();
};
