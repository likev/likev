#pragma once

#define WM_CALCULATE WM_USER+1

// CCalculateThread

class CCalculateThread : public CWinThread
{
	DECLARE_DYNCREATE(CCalculateThread)

protected:
	CCalculateThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCalculateThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnCalculate(UINT wParam,LONG lParam);
};


