// generate-line.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CgeneratelineApp:
// �йش����ʵ�֣������ generate-line.cpp
//

class CgeneratelineApp : public CWinApp
{
public:
	CgeneratelineApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CgeneratelineApp theApp;