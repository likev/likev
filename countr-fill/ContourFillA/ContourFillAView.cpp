// ContourFillAView.cpp : CContourFillAView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CContourFillAView ����/����

CContourFillAView::CContourFillAView()
{
	// TODO: �ڴ˴���ӹ������

}

CContourFillAView::~CContourFillAView()
{
}

BOOL CContourFillAView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CContourFillAView ����

void CContourFillAView::OnDraw(CDC* pDC/**/)
{
	CContourFillADoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	//���Ƶ�ֵ��
	for(contour_fill::contr_set_type::iterator it=pDoc->lines.begin();
		it != pDoc->lines.end(); it++)
	{
		std::vector<CPoint> Points((*it).begin(),(*it).end());

		pDC->Polyline(&Points[0],Points.size());
	}
	 

	//��ɫ
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


// CContourFillAView ��ӡ

BOOL CContourFillAView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CContourFillAView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CContourFillAView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CContourFillAView ���

#ifdef _DEBUG
void CContourFillAView::AssertValid() const
{
	CView::AssertValid();
}

void CContourFillAView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CContourFillADoc* CContourFillAView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CContourFillADoc)));
	return (CContourFillADoc*)m_pDocument;
}
#endif //_DEBUG


// CContourFillAView ��Ϣ�������
