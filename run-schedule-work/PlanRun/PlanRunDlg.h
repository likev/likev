// PlanRunDlg.h : ͷ�ļ�
//

#pragma once
#include "afxdtctl.h"
#include "afxcmn.h"


// CPlanRunDlg �Ի���
class CPlanRunDlg : public CDialog
{
// ����
public:
	CPlanRunDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PLANRUN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	// ��Ҫִ�е�����
	CString command_line;
	afx_msg void OnDtnDatetimechangeDate(NMHDR *pNMHDR, LRESULT *pResult);
	// ����ִ�е�����
	CDateTimeCtrl plan_date;
	// ����ִ�е�ʱ��
	CDateTimeCtrl plan_time;
	// ����������б�
	CListCtrl task_list;

	NOTIFYICONDATA nid;
	void HideToTray();


public:
	afx_msg void OnBnClickedAddtolist();
	afx_msg void OnBnClickedSelectapp();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam); 
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};

