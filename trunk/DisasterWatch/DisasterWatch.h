// DisasterWatch.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CDisasterWatchApp:
// �йش����ʵ�֣������ DisasterWatch.cpp
//

class CDisasterWatchApp : public CWinApp
{
public:
	CDisasterWatchApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDisasterWatchApp theApp;