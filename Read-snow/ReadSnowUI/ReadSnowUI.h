// ReadSnowUI.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReadSnowUIApp:
// �йش����ʵ�֣������ ReadSnowUI.cpp
//

class CReadSnowUIApp : public CWinApp
{
public:
	CReadSnowUIApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReadSnowUIApp theApp;