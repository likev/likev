// ForcastAnalysis2.h : ForcastAnalysis2 Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CForcastAnalysis2App:
// �йش����ʵ�֣������ ForcastAnalysis2.cpp
//

class CForcastAnalysis2App : public CWinApp
{
public:
	CForcastAnalysis2App();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CForcastAnalysis2App theApp;