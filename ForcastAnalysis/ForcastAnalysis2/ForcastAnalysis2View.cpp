// ForcastAnalysis2View.cpp : CForcastAnalysis2View 类的实现
//

#include "stdafx.h"
#include "ForcastAnalysis2.h"

#include "ForcastAnalysis2Doc.h"
#include "ForcastAnalysis2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CForcastAnalysis2View

IMPLEMENT_DYNCREATE(CForcastAnalysis2View, CView)

BEGIN_MESSAGE_MAP(CForcastAnalysis2View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CForcastAnalysis2View 构造/析构

CForcastAnalysis2View::CForcastAnalysis2View()
{
	// TODO: 在此处添加构造代码

}

CForcastAnalysis2View::~CForcastAnalysis2View()
{
}

BOOL CForcastAnalysis2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CForcastAnalysis2View 绘制

void CForcastAnalysis2View::OnDraw(CDC* /*pDC*/)
{
	CForcastAnalysis2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CForcastAnalysis2View 打印

BOOL CForcastAnalysis2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CForcastAnalysis2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CForcastAnalysis2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CForcastAnalysis2View 诊断

#ifdef _DEBUG
void CForcastAnalysis2View::AssertValid() const
{
	CView::AssertValid();
}

void CForcastAnalysis2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CForcastAnalysis2Doc* CForcastAnalysis2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CForcastAnalysis2Doc)));
	return (CForcastAnalysis2Doc*)m_pDocument;
}
#endif //_DEBUG


// CForcastAnalysis2View 消息处理程序
