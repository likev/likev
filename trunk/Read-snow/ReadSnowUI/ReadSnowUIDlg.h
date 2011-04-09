// ReadSnowUIDlg.h : ͷ�ļ�
//

#pragma once
#include "snowLib/DealSnowData.h"

// CReadSnowUIDlg �Ի���
class CReadSnowUIDlg : public CDialog
{
// ����
public:
	CReadSnowUIDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_READSNOWUI_DIALOG };

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
	afx_msg void OnBnClickedButtonQuery();
	// ������д���ļ�
	bool WriteDataToFile(void);
	// ��ʼʱ��
	CString beginHour;
	// ����ʱ��
	CString endHour;
	// ��ʼ����
	CTime beginDay;
	// ��������
	CTime endDay;
	// ���ѡ������
	int selectRagion;

	std::vector<std::string> luoyangStationID,luoyangStationName,
							 henanStationID,henanStationName;

	void InitDataFromFile();

	int getSelectHour(CString hourString)const;

};
