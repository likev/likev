#pragma once

#include <string>
// ShortForcast �Ի���

class ShortForcast : public CDialog
{
	DECLARE_DYNAMIC(ShortForcast)

public:
	ShortForcast(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ShortForcast();

// �Ի�������
	enum { IDD = IDD_DLG_ShortForcast };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString forcast_content,file_path;

	virtual BOOL OnInitDialog();

	bool PutShortForcast();
	afx_msg void OnBnClickedOk();
};
