// ContourFillAView.cpp : CContourFillAView 类的实现
//

#include "stdafx.h"
#include "ContourFillA.h"

#include "ContourFillADoc.h"
#include "ContourFillAView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CContourFillAView

IMPLEMENT_DYNCREATE(CContourFillAView, CView)

BEGIN_MESSAGE_MAP(CContourFillAView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CContourFillAView 构造/析构

CContourFillAView::CContourFillAView()
{
	// TODO: 在此处添加构造代码

}

CContourFillAView::~CContourFillAView()
{
}

BOOL CContourFillAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CContourFillAView 绘制

void CContourFillAView::OnDraw(CDC* pDC/**/)
{
	CContourFillADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	//绘制等值线
	for(contour_fill::contr_set_type::iterator it=pDoc->lines.begin();
		it != pDoc->lines.end(); it++)
	{
		std::vector<CPoint> Points((*it).begin(),(*it).end());

		pDC->Polyline(&Points[0],Points.size());
	}
	 

	//填色
	for(std::vector<contour_fill::contr_set_type>::iterator it=pDoc->contr_set_type.begin();
		it != pDoc->contr_set_type.end(); it++)
	{
		int i=0;
		for(contour_fill::contr_set_type::iterator it2=(*it).begin();
			it2 != (*it).end(); it2++)
		{
			i++;
			std::vector<CPoint> Points((*it2).begin(),(*it2).end());

			CRgn region;
			region.CreatePolygonRgn(&Points[0],Points.size(),ALTERNATE);

			pDC->FillRgn(&region,&CBrush(RGB((i*1000)%255,(i*1000)%255,(i*1000)%255)));
		}
		
	}

}


// CContourFillAView 打印

BOOL CContourFillAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CContourFillAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CContourFillAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CContourFillAView 诊断

#ifdef _DEBUG
void CContourFillAView::AssertValid() const
{
	CView::AssertValid();
}

void CContourFillAView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CContourFillADoc* CContourFillAView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CContourFillADoc)));
	return (CContourFillADoc*)m_pDocument;
}
#endif //_DEBUG


// CContourFillAView 消息处理程序
