// DisasterWatchDlg.h : ͷ�ļ�
//

#pragma once
#include "comn.h"
#include "string-trans.h"
#include "afxwin.h"

// CDisasterWatchDlg �Ի���
class CDisasterWatchDlg : public CDialog
{
// ����
public:
	CDisasterWatchDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DISASTERWATCH_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
	afx_msg void OnBnClickedCheckAlert();
	afx_msg void OnBnClickedCheckSendMessage();
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);

	//������ͼ����Ϣ
	NOTIFYICONDATA nid;
	// ���ص�������
	void HideToTray(void);

	// �����Զ�����
	void AutoRunAfterStart(void);

	// �Ƿ��Զ�����
	BOOL auto_alert;
	// �Զ����Ͷ���Ϣ
	BOOL auto_send_message;

	int interval;
	std::string last_disaster_id;

	std::vector<std::string> all_stations, all_mobile_phone;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void BeginAllProc();
	bool CheckNewDisaster();
	void ReadNewDisaster();




	// ��������
	CEdit disa_view;
	
	CString viewtext;
};
