// ContourFillAView.h : CContourFillAView ��Ľӿ�
//


#pragma once


class CContourFillAView : public CView
{
protected: // �������л�����
	CContourFillAView();
	DECLARE_DYNCREATE(CContourFillAView)

// ����
public:
	CContourFillADoc* GetDocument() const;

// ����
public:

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
	virtual ~CContourFillAView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ContourFillAView.cpp �еĵ��԰汾
inline CContourFillADoc* CContourFillAView::GetDocument() const
   { return reinterpret_cast<CContourFillADoc*>(m_pDocument); }
#endif

