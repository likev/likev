#pragma once

#include <string>
// SelfForcast �Ի���

class SelfForcast : public CDialog
{
	DECLARE_DYNAMIC(SelfForcast)

public:
	SelfForcast(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~SelfForcast();

// �Ի�������
	enum { IDD = IDD_DLG_SelfForcast };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString file_content;
	std::string ftp_filename;

	virtual BOOL OnInitDialog();

	bool PutSelfForcast();
	afx_msg void OnBnClickedOk();
};
