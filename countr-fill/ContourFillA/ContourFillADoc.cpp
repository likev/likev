// ContourFillADoc.cpp : CContourFillADoc ���ʵ��
//

#include "stdafx.h"
#include "ContourFillA.h"

#include "ContourFillADoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CContourFillADoc

IMPLEMENT_DYNCREATE(CContourFillADoc, CDocument)

BEGIN_MESSAGE_MAP(CContourFillADoc, CDocument)
END_MESSAGE_MAP()


// CContourFillADoc ����/����

CContourFillADoc::CContourFillADoc()
{
	// TODO: �ڴ����һ���Թ������
	lines=readdata();
	contour_fill(lines,0,0,450,350).get_fill_contours(contr_set_type);

}

CContourFillADoc::~CContourFillADoc()
{
}

BOOL CContourFillADoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CContourFillADoc ���л�

void CContourFillADoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CContourFillADoc ���

#ifdef _DEBUG
void CContourFillADoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CContourFillADoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CContourFillADoc ����
