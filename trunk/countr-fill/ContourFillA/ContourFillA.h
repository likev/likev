// ContourFillA.h : ContourFillA Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CContourFillAApp:
// �йش����ʵ�֣������ ContourFillA.cpp
//

class CContourFillAApp : public CWinApp
{
public:
	CContourFillAApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CContourFillAApp theApp;