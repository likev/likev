// drawmapsDoc.h : CdrawmapsDoc ��Ľӿ�
//


#pragma once

#include "county-border.h"
#include "string-trans.h"

#define WM_READOVER WM_USER+2
class CdrawmapsDoc : public CDocument
{
protected: // �������л�����
	CdrawmapsDoc();
	DECLARE_DYNCREATE(CdrawmapsDoc)

// ����
public:

	std::string nowfile;
	volatile bool redraw;

	std::vector<county_border> borders;
	void read_border_data(std::string filename);
private:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CdrawmapsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	
};


