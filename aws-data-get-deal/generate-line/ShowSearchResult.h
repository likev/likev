#pragma once

#include <comn.h>
#include "afxcmn.h"
// ShowSearchResult 对话框

class ShowSearchResult : public CDialog
{
	DECLARE_DYNAMIC(ShowSearchResult)

public:
	ShowSearchResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ShowSearchResult();

// 对话框数据
	enum { IDD = IDD_SHOW_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	CString title;
	typedef std::vector<std::string> StringArray;

	StringArray headtitles;
	std::vector<StringArray> contents;

	virtual BOOL OnInitDialog();
	// 显示的列表
	CListCtrl show_list;
	bool have_init;//是否初始化
	int column_width;//默认初始列宽
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedSaveastext();
};
