#pragma once


// AnalySet �Ի���

class AnalySet : public CDialog
{
	DECLARE_DYNAMIC(AnalySet)

public:
	AnalySet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~AnalySet();

// �Ի�������
	enum { IDD = IDD_ANALYSET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��ʼʱ��
	CTime begin;
	// ����ʱ��
	CTime end;
	// �ļ���·��
	CString folder;
	// ѡ�е�ʱ��
	int checked_times;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedFloderset();
};
