//����ָ��ʱ����¶�����

#pragma once

#include <comn.h>
// TemphLineDlg �Ի���

class TemphLineDlg : public CDialog
{
	DECLARE_DYNAMIC(TemphLineDlg)

public:
	TemphLineDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TemphLineDlg();

// �Ի�������
	enum { IDD = IDD_TEMPH_LINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	enum {LAST3DAYS,LAST10DAYS,CURMONTH,LASTMONTH,ANYTIME};
public:

	int select_item;
	
	// ��ʼ����������
	CTime begin_day, end_day;
	// ��ʼ����Сʱ
	int begin_hour, end_hour;

	//��¼��ʼ����ʱ��
	CTime LeftTime,RightTime;

	//����վ�������Сֵ
	std::vector<double> min_values, max_values;

	//��ȡ��վ��
	std::vector<int> stations;
	//�����ѯ�ļ�¼
	std::map<CTime,double> mrecords;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedAnyTime();
	// ѡ��ı�
	void RadioChange(void);
	afx_msg void OnBnClickedLast3days();
	afx_msg void OnBnClickedLast10days();
	afx_msg void OnBnClickedCurmonth();
	afx_msg void OnBnClickedLastmonth();
	afx_msg void OnBnClickedDrawline();
	// ����html�ļ�
	int generate_html(void);

	std::string get_additional_info();
	// ��ȡ��վ��������¼
	std::string get_records_str(int station_number);
	// �ҵ����һ�β�ѯ��������Сֵ
	int FindMinMaxValue(void);
};
