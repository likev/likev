// drawmapsView.h : CdrawmapsView 类的接口
//


#pragma once

#include "drawmapsDoc.h"


class CdrawmapsView : public CView
{
protected: // 仅从序列化创建
	CdrawmapsView();
	DECLARE_DYNCREATE(CdrawmapsView)

// 属性
public:
	CdrawmapsDoc* GetDocument() const;
	
public:
	double zoomvalue;
	
	county_border::point_type refer_lonlat;
	CPoint refer_coord;
	CPoint orgin_coord;

// 操作
public:
	CPoint lonlat_to_coord(county_border::point_type &point);
	county_border::point_type coord_to_lonlat(CPoint point);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CdrawmapsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg LRESULT OnReadOver(WPARAM wParam,LPARAM lParam);
	afx_msg void OnRead();
};

#ifndef _DEBUG  // drawmapsView.cpp 中的调试版本
inline CdrawmapsDoc* CdrawmapsView::GetDocument() const
   { return reinterpret_cast<CdrawmapsDoc*>(m_pDocument); }
#endif

