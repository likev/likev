// drawmaps.h : drawmaps Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CdrawmapsApp:
// �йش����ʵ�֣������ drawmaps.cpp
//

class CdrawmapsApp : public CWinApp
{
public:
	CdrawmapsApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CdrawmapsApp theApp;