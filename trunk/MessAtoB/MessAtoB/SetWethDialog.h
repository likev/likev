#pragma once


// CSetWethDialog �Ի���

class CSetWethDialog : public CDialog
{
	DECLARE_DYNAMIC(CSetWethDialog)

public:
	CSetWethDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetWethDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_WET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
//ʵ��

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
