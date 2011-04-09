// ForcastAnalysis2View.h : CForcastAnalysis2View 类的接口
//


#pragma once


class CForcastAnalysis2View : public CView
{
protected: // 仅从序列化创建
	CForcastAnalysis2View();
	DECLARE_DYNCREATE(CForcastAnalysis2View)

// 属性
public:
	CForcastAnalysis2Doc* GetDocument() const;

// 操作
public:

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
	virtual ~CForcastAnalysis2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // ForcastAnalysis2View.cpp 中的调试版本
inline CForcastAnalysis2Doc* CForcastAnalysis2View::GetDocument() const
   { return reinterpret_cast<CForcastAnalysis2Doc*>(m_pDocument); }
#endif

