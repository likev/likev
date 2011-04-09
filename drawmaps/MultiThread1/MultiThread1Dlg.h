// MultiThread1Dlg.h : ͷ�ļ�
//

#pragma once
#include "CalculateThread.h"
#define WM_DISPLAY WM_USER+2

// CMultiThread1Dlg �Ի���
class CMultiThread1Dlg : public CDialog
{
// ����
public:
	CMultiThread1Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MULTITHREAD1_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CCalculateThread* m_pCalculateThread;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// �߳���Ŀ
	volatile unsigned int thread_number;
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnDisplay(WPARAM wParam,LPARAM lParam);
};
