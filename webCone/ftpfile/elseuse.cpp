

#include "firewarning.h"

#include <Mmsystem.h>
#pragma comment(lib,"winmm.lib")//��������ͷ�ļ���

//�����߳�������������
UINT MyThreadProc(LPVOID pParam ) //�����߳�
{
	char quit=0;
	while(!quit)
	{
		if(WaitForSingleObject(hMutex,300) != WAIT_FAILED)
		{
			quit = tdquit;
			ReleaseMutex(hMutex);
		}
			
		PlaySound("warn.wav",NULL,SND_SYNC|SND_FILENAME);
		Sleep(1000);
	}

	return 0;   // thread completed successfully
}

//���Ͷ��� ���÷��Žӿ�
bool sendmes(string message, string sendto)
{
	string murl="http://sms.api.bz/fetion.php?username=13663880026&password=qxt0307";
	murl +=  "&sendto="+sendto+"&message="+message;

	try
	{
	CInternetSession session("Mozilla/5.0 (Windows; U; Windows NT 6.0; zh-CN; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3");
	session.OpenURL(murl.c_str());
	}
	catch (CInternetException* pEx)
	{
		char error[1025];
		pEx->GetErrorMessage(error, 1024);
		cout<<"ERROR!"<<error<<endl;
		pEx->Delete();
		return false;
	}

	return true;
}