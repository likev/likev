// MessAtoB.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMessAtoBApp:
// �йش����ʵ�֣������ MessAtoB.cpp
//

class CMessAtoBApp : public CWinApp
{
public:
	CMessAtoBApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMessAtoBApp theApp;