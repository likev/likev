#pragma once

#include <comn.h>
#include "afxcmn.h"
// ShowSearchResult �Ի���

class ShowSearchResult : public CDialog
{
	DECLARE_DYNAMIC(ShowSearchResult)

public:
	ShowSearchResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ShowSearchResult();

// �Ի�������
	enum { IDD = IDD_SHOW_RESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	CString title;
	typedef std::vector<std::string> StringArray;

	StringArray headtitles;
	std::vector<StringArray> contents;

	virtual BOOL OnInitDialog();
	// ��ʾ���б�
	CListCtrl show_list;
	bool have_init;//�Ƿ��ʼ��
	int column_width;//Ĭ�ϳ�ʼ�п�
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedSaveastext();
};
