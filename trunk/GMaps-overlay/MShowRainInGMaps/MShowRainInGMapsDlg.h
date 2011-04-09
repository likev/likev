// MShowRainInGMapsDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "gprs-rain-line.h"

// CMShowRainInGMapsDlg �Ի���
class CMShowRainInGMapsDlg : public CDialog
{
// ����
public:
	CMShowRainInGMapsDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MSHOWRAININGMAPS_DIALOG };

	//---����---
	GprsRainRecord records;

	bool is_real_rain;
	
	int net_type; //�������ӷ�ʽ
	std::string server,url;
	
	CTime begin_day, end_day; // ��ʼ��������
	
	CTime begin_time, end_time; // ��ʼ����ʱ��
	
	int interval; // ˢ��ʱ��
	CSpinButtonCtrl spin_interval;
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
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	//������ͼ����Ϣ
	NOTIFYICONDATA nid;
	// ���ص�������
	void HideToTray(void);

	void ChangeViewType();
	void ChangeNetType();
	void UpdateRainValue();
	
	afx_msg void OnBnClickedRadioRealrain();
	afx_msg void OnBnClickedRadioHistoryrain();
	
	afx_msg void OnBnClickedRadioInnernet();
	afx_msg void OnBnClickedRadioOutsidenet();
	afx_msg void OnBnClickedButtonSearch();
	
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	// ��������״̬
	CString status_info;
};
