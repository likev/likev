#pragma once


// CPYDlg �Ի���

class CPYDlg : public CDialog
{
	DECLARE_DYNAMIC(CPYDlg)

public:
	CPYDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPYDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_PY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ҩָ���ı�����
	CString py_edit_content;
	afx_msg void OnBnClickedOk();
};
