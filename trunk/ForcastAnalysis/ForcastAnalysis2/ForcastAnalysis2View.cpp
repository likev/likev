// ForcastAnalysis2View.cpp : CForcastAnalysis2View ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CForcastAnalysis2View ����/����

CForcastAnalysis2View::CForcastAnalysis2View()
{
	// TODO: �ڴ˴���ӹ������

}

CForcastAnalysis2View::~CForcastAnalysis2View()
{
}

BOOL CForcastAnalysis2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CForcastAnalysis2View ����

void CForcastAnalysis2View::OnDraw(CDC* /*pDC*/)
{
	CForcastAnalysis2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CForcastAnalysis2View ��ӡ

BOOL CForcastAnalysis2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CForcastAnalysis2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CForcastAnalysis2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CForcastAnalysis2View ���

#ifdef _DEBUG
void CForcastAnalysis2View::AssertValid() const
{
	CView::AssertValid();
}

void CForcastAnalysis2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CForcastAnalysis2Doc* CForcastAnalysis2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CForcastAnalysis2Doc)));
	return (CForcastAnalysis2Doc*)m_pDocument;
}
#endif //_DEBUG


// CForcastAnalysis2View ��Ϣ�������
