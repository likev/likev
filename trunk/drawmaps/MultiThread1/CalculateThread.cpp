// CalculateThread.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultiThread1.h"
#include "CalculateThread.h"
 #include "MultiThread1Dlg.h"

// CCalculateThread

IMPLEMENT_DYNCREATE(CCalculateThread, CWinThread)

CCalculateThread::CCalculateThread()
{
}

CCalculateThread::~CCalculateThread()
{
}

BOOL CCalculateThread::InitInstance()
{
	// TODO: �ڴ�ִ���������̳߳�ʼ��
	return TRUE;
}

int CCalculateThread::ExitInstance()
{
	// TODO: �ڴ�ִ���������߳�����
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CCalculateThread, CWinThread)
			
	ON_THREAD_MESSAGE(WM_CALCULATE,OnCalculate)
		
	
END_MESSAGE_MAP()


// CCalculateThread ��Ϣ�������
void CCalculateThread::OnCalculate(UINT wParam,LONG lParam)
{	
	int nTmpt=0;	
	for(int i=0;i<=(int)wParam;i++)	
	{	
		nTmpt=nTmpt+i;	
	}	
	Sleep(500);    

	//(CMultiThread1Dlg *)GetMainWnd()->

	::PostMessage((HWND)(GetMainWnd()->GetSafeHwnd()),WM_DISPLAY,nTmpt,NULL);	
}
