// PlanRun.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPlanRunApp:
// �йش����ʵ�֣������ PlanRun.cpp
//

class CPlanRunApp : public CWinApp
{
public:
	CPlanRunApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPlanRunApp theApp;