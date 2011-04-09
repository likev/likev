#pragma once

#include <comn.h>
// RainLineDlg �Ի���

class RainLineDlg : public CDialog
{
	DECLARE_DYNAMIC(RainLineDlg)

public:
	RainLineDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RainLineDlg();

// �Ի�������
	enum { IDD = IDD_RAIN_LINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	enum DrawType{ACCUMULATED,RAINBYHOUR};
	// ��ʼ����������
	CTime begin_day, end_day;
	// ��ʼ����Сʱ
	int begin_hour, end_hour;

	//��¼��ʼ����ʱ��
	CTime LeftTime,RightTime;

	//����վ�������Сֵ
	std::vector<double> min_values, max_values;

	std::string plot_title;

	DrawType draw_type;//���ƹ��̽�ˮ��Сʱ��ˮ
	bool is_lastest_rain;

	int MAX_RAIN_SPAN_HOUR;//�����ν�ˮСʱ��С��MAX_RAIN_SPAN_HOUR ʱ ��Ϊ��һ�ν�ˮ

	//��ȡ��վ��
	std::vector<int> stations;
	//�����ѯ�ļ�¼
	std::map<CTime,double> mrecords;
public:

//	afx_msg void OnBnClickedRanytime();
	afx_msg void OnBnSetfocusRanytime();
//	afx_msg void OnBnHotItemChangeRanytime(NMHDR *pNMHDR, LRESULT *pResult);
	// ��ѡ��ť��ı�
	int RadioChange(void);
	afx_msg void OnBnClickedRanytime();
	afx_msg void OnBnClickedLastestrain();
	afx_msg void OnBnClickedLast3hour();
	afx_msg void OnBnClickedLast6hour();
	afx_msg void OnBnClickedLast12hour();
	afx_msg void OnBnClickedLast24hour();
	afx_msg void OnBnClickedRtoday();
	afx_msg void OnBnClickedRyeasterday();
	afx_msg void OnBnClickedRcurmonth();
	afx_msg void OnBnClickedRlastmonth();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedDrawline();

	// ����html�ļ�
	int generate_html(void);

	std::string get_additional_info();
	// ��ȡ��վ��������¼
	std::string get_records_str(int station_number);
	// ת��Ϊ�ۼƽ�ˮֵ
	void ToAccumulatedRain(std::map<CTime,double> & records);
	// ת��ΪСʱ��ˮ
	void ToHourRain(std::map<CTime,double> & records);
	afx_msg void OnBnClickedAccumulated();
	afx_msg void OnBnClickedRainbyhour();
	// �ҵ����һ�β�ѯ��������Сֵ
	int FindMinMaxValue(void);
	// ��������һ�ν���������ʼʱ��
	void CalcLastestTime(void);
};
