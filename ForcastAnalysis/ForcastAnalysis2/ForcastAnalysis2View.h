// ForcastAnalysis2View.h : CForcastAnalysis2View ��Ľӿ�
//


#pragma once


class CForcastAnalysis2View : public CView
{
protected: // �������л�����
	CForcastAnalysis2View();
	DECLARE_DYNCREATE(CForcastAnalysis2View)

// ����
public:
	CForcastAnalysis2Doc* GetDocument() const;

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
	virtual ~CForcastAnalysis2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ForcastAnalysis2View.cpp �еĵ��԰汾
inline CForcastAnalysis2Doc* CForcastAnalysis2View::GetDocument() const
   { return reinterpret_cast<CForcastAnalysis2Doc*>(m_pDocument); }
#endif

