// AutoGetAwsFile.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "AutoGetAwsFile.h"
#include "AutoGetAwsFileDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAutoGetAwsFileApp

BEGIN_MESSAGE_MAP(CAutoGetAwsFileApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CAutoGetAwsFileApp ����

CAutoGetAwsFileApp::CAutoGetAwsFileApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CAutoGetAwsFileApp ����

CAutoGetAwsFileApp theApp;


// CAutoGetAwsFileApp ��ʼ��

BOOL CAutoGetAwsFileApp::InitInstance()
{
	CWinApp::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CAutoGetAwsFileDlg dlg;
	m_pMainWnd = &dlg;
	/*
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	*/
	dlg.Create(CAutoGetAwsFileDlg::IDD);
	dlg.ShowWindow(SW_HIDE);
	dlg.RunModalLoop();

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
