// drawmapsView.cpp : CdrawmapsView ���ʵ��
//

#include "stdafx.h"
#include "drawmaps.h"


#include "drawmapsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdrawmapsView

IMPLEMENT_DYNCREATE(CdrawmapsView, CView)

BEGIN_MESSAGE_MAP(CdrawmapsView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_MOUSEWHEEL()
	ON_MESSAGE(WM_READOVER,OnReadOver)
	ON_COMMAND(ID_Read, &CdrawmapsView::OnRead)
END_MESSAGE_MAP()

// CdrawmapsView ����/����

CdrawmapsView::CdrawmapsView()
{
	// TODO: �ڴ˴���ӹ������
	zoomvalue = 20;
	
	refer_lonlat = county_border::point_type(70,60);
	refer_coord = CPoint(0,0) ;
	orgin_coord = CPoint(10,10);

}

CdrawmapsView::~CdrawmapsView()
{
}

BOOL CdrawmapsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CdrawmapsView ����

void CdrawmapsView::OnDraw(CDC* pDC)
{
	CdrawmapsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	if(!pDoc->redraw) 
	{
		return;
	}

	CString zvalue;
	zvalue.Format("zoom = %f",zoomvalue);
	pDC->TextOutA(600,20,zvalue);

	for(size_t i=0; i< pDoc->borders.size(); i++)
	{
		std::vector<county_border::point_type> nowline=pDoc->borders[i].line;

		for(size_t j=0;j!=nowline.size();j++)
		{
			lonlat_to_coord(nowline[j]);
		}

		std::vector<CPoint> pts(nowline.begin(), nowline.end());
		
		pDC->Polyline(&pts.front(),pts.size());

		//��������
		if(zoomvalue >50)
		{
			county_border::point_type point = pDoc->borders[i].location;
			std::swap(point.x,point.y);
			CPoint loc =  lonlat_to_coord(point);

			std::string name = pDoc->borders[i].name;
			pDC->TextOut(loc.x,loc.y,name.c_str(),name.size());
		}
	}
}

CPoint CdrawmapsView::lonlat_to_coord(county_border::point_type &point)
{
	point.x = (point.x - refer_lonlat.x)*zoomvalue + refer_coord.x;

	point.y = (refer_lonlat.y - point.y)*zoomvalue + refer_coord.y;

	return point;
}

county_border::point_type CdrawmapsView::coord_to_lonlat(CPoint point)
{
	

	return county_border::point_type();
}

// CdrawmapsView ��ӡ

BOOL CdrawmapsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CdrawmapsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CdrawmapsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CdrawmapsView ���

#ifdef _DEBUG
void CdrawmapsView::AssertValid() const
{
	CView::AssertValid();
}

void CdrawmapsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CdrawmapsDoc* CdrawmapsView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CdrawmapsDoc)));
	return (CdrawmapsDoc*)m_pDocument;
}
#endif //_DEBUG


// CdrawmapsView ��Ϣ�������

BOOL CdrawmapsView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	zoomvalue += zDelta/48.0;

	Invalidate();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

LRESULT CdrawmapsView::OnReadOver(WPARAM wParam,LPARAM lParam)
{
	Invalidate();
	return 0;
}


void CdrawmapsView::OnRead()
{
	//CreateThread(NULL,0,threadFunc,this,0,NULL);
}
