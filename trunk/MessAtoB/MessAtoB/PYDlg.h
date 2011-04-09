#pragma once


// CPYDlg 对话框

class CPYDlg : public CDialog
{
	DECLARE_DYNAMIC(CPYDlg)

public:
	CPYDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPYDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 喷药指数文本内容
	CString py_edit_content;
	afx_msg void OnBnClickedOk();
};
