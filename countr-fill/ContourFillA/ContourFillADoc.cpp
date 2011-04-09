// ContourFillADoc.cpp : CContourFillADoc 类的实现
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


// CContourFillADoc 构造/析构

CContourFillADoc::CContourFillADoc()
{
	// TODO: 在此添加一次性构造代码
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

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CContourFillADoc 序列化

void CContourFillADoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CContourFillADoc 诊断

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


// CContourFillADoc 命令
