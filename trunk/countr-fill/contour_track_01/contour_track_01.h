// contour_track_01.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ccontour_track_01App:
// �йش����ʵ�֣������ contour_track_01.cpp
//

class Ccontour_track_01App : public CWinApp
{
public:
	Ccontour_track_01App();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ccontour_track_01App theApp;