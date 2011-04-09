// drawmapsDoc.cpp : CdrawmapsDoc ���ʵ��
//

#include "stdafx.h"
#include "drawmaps.h"

#include "drawmapsDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CdrawmapsDoc

IMPLEMENT_DYNCREATE(CdrawmapsDoc, CDocument)

BEGIN_MESSAGE_MAP(CdrawmapsDoc, CDocument)
	ON_COMMAND(ID_FILE_OPEN, &CdrawmapsDoc::OnFileOpen)
END_MESSAGE_MAP()


// CdrawmapsDoc ����/����

CdrawmapsDoc::CdrawmapsDoc()
{
	// TODO: �ڴ����һ���Թ������
	redraw = false;


}

CdrawmapsDoc::~CdrawmapsDoc()
{
}

BOOL CdrawmapsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CdrawmapsDoc ���л�

void CdrawmapsDoc::Serialize(CArchive& ar)
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


// CdrawmapsDoc ���

#ifdef _DEBUG
void CdrawmapsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CdrawmapsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CdrawmapsDoc ����
void CdrawmapsDoc::read_border_data(std::string filename)
{
	std::string filecontent;
	filetostr(filename,filecontent,1);

	str_trim(filecontent);

	std::istringstream ssin(filecontent);

	borders.clear();
	size_t i=0;
	while(!ssin.eof())
	{
		county_border bd;
		borders.push_back(bd);
		
		ssin>>borders[i].location>>borders[i].name;

		size_t n=0;
		ssin>>n;

		county_border::point_type point;
		for(size_t j=0;j<n;j++)
		{
			if(ssin>>point)
				borders[i].line.push_back(point);
			else
				break;
		}

		i++;
	}

}

DWORD WINAPI threadFunc(LPVOID pParam)
{
	CdrawmapsDoc * pDoc = (CdrawmapsDoc * )pParam;

	pDoc->read_border_data(pDoc->nowfile);
	pDoc->redraw = true;
	
	/*pDoc->UpdateAllViews(NULL);*/ //Ϊʲô���У�
	POSITION pos = pDoc->GetFirstViewPosition();
   if (pos != NULL)
   {
      CView* pView = pDoc->GetNextView(pos);
      pView->Invalidate();
   }

	//PostMessage(pDoc->,WM_READOVER,NULL,NULL);

	return 0;
}

void CdrawmapsDoc::OnFileOpen()
{
	// TODO: �ڴ���������������
	CFileDialog fd(true);
	if(fd.DoModal() == IDOK)
	{
		//if(nowfile == fd.GetPathName().GetBuffer())
		//{
			redraw = false;
		//	return;
		//}
		
		nowfile = fd.GetPathName().GetBuffer();

		CreateThread(NULL,0,threadFunc,this,0,NULL);
		//read_border_data(nowfile);

		//UpdateAllViews(NULL);
	}
}

