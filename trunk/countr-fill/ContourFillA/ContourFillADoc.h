// ContourFillADoc.h : CContourFillADoc ��Ľӿ�
//


#pragma once

#include "contour_fill.h"

class CContourFillADoc : public CDocument
{
protected: // �������л�����
	CContourFillADoc();
	DECLARE_DYNCREATE(CContourFillADoc)

// ����
public:
	contour_fill::contr_set_type lines;
	std::vector<contour_fill::contr_set_type> contr_set_type;

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CContourFillADoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


