// drawmapsView.h : CdrawmapsView ��Ľӿ�
//


#pragma once

#include "drawmapsDoc.h"


class CdrawmapsView : public CView
{
protected: // �������л�����
	CdrawmapsView();
	DECLARE_DYNCREATE(CdrawmapsView)

// ����
public:
	CdrawmapsDoc* GetDocument() const;
	
public:
	double zoomvalue;
	
	county_border::point_type refer_lonlat;
	CPoint refer_coord;
	CPoint orgin_coord;

// ����
public:
	CPoint lonlat_to_coord(county_border::point_type &point);
	county_border::point_type coord_to_lonlat(CPoint point);

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CdrawmapsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg LRESULT OnReadOver(WPARAM wParam,LPARAM lParam);
	afx_msg void OnRead();
};

#ifndef _DEBUG  // drawmapsView.cpp �еĵ��԰汾
inline CdrawmapsDoc* CdrawmapsView::GetDocument() const
   { return reinterpret_cast<CdrawmapsDoc*>(m_pDocument); }
#endif

