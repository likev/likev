// ForcastAnalysis2Doc.h : CForcastAnalysis2Doc ��Ľӿ�
//


#pragma once

#include <comn.h>
#include "city-message.h"
#include "statis_result.h"
#include "city_forecast.h"

class CForcastAnalysis2Doc : public CDocument
{
protected: // �������л�����
	CForcastAnalysis2Doc();
	DECLARE_DYNCREATE(CForcastAnalysis2Doc)

// ����
public:

	//����վ��
	std::vector<int> station_nums;

	//�ܵ�ͳ�ƽ��
	std::map<int, stat_result> statistics;
	//ÿһ���վ������
	std::vector<city_message> city_mess_day;
	std::vector<city_fst> perday_fst;

	//��Ҫͳ�ƵĿ�ʼ�ͽ���ʱ��
	CTime stat_begin, stat_end;
	//��ǰ������ʱ��
	CTime cur_time;

	//��Ҫͳ�Ƶ����������ļ���
	CString stat_floder;


// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CForcastAnalysis2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAnalyset();
	// ������������
	void BeginAnaly(void);
	// ��ȡѡȡʱ��εĳ���
	bool ReadCityMessages(void);
	//����ÿһ��
	void PerdayDeal(void);

	//ͳ��ÿһ������
	void PerdayStat(void);
	// ��ȡ��Ҫ������վ���
	bool ReadStationNums(void);
	// ͳ�Ƶ����صĸ�ʱ��Ԥ��
	void PerCityStat(int station_number);
};


