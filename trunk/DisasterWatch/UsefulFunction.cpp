
#include "comn.h"
#include <afxinet.h>
#include <Mmsystem.h>

#pragma comment(lib,"winmm.lib")//��������ͷ�ļ���

volatile bool close_alert=false;

//�����߳�������������
UINT MyThreadProc(LPVOID pParam ) //�����߳�
{
	while(!close_alert)
	{
		PlaySound("warn.wav",NULL,SND_SYNC|SND_FILENAME);
		Sleep(1000);
	}

	return 0;   // thread completed successfully
}

//���Ͷ��� ����tui3�ӿ�
bool send_short_message(std::string message, std::string sendto)
{
	std::string murl="http://www.tui3.com/api/send/?k=321898d573024997301345c36bc9606f&r=json&p=1";
	murl +=  "&t="+sendto+"&cn="+message+" lyqx";

	try
	{
	CInternetSession session("Mozilla/5.0 (Windows; U; Windows NT 6.0; zh-CN; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3");
	session.OpenURL(murl.c_str());
	}
	catch (CInternetException* pEx)
	{
		char error[1025];
		pEx->GetErrorMessage(error, 1024);
		//cout<<"ERROR!"<<error<<endl;
		pEx->Delete();
		return false;
	}

	return true;
}

//������ҳ
bool DownloadHttpPage(LPCTSTR pszServerName, LPCTSTR pszURL, LPCTSTR pszLocalFile)
{
	using namespace std;

	CInternetSession session(_T("Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2) Gecko/20100115 Firefox/3.6"));

	try
	{
		CString strServerName;
		INTERNET_PORT nPort = 80;
		DWORD dwRet = 0;

		CHttpConnection* pServer = session.GetHttpConnection(pszServerName, nPort);
		CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, pszURL,
												0,1,0,0,INTERNET_FLAG_RELOAD);
		pFile->SendRequest();
		pFile->QueryInfoStatusCode(dwRet);

		if (dwRet == HTTP_STATUS_OK)
		{
			char szBuff[1024]={};
			ofstream fout(pszLocalFile,ios_base::out|ios_base::binary);
			if(!fout.is_open())
			{
				//cout<<"�򿪻򴴽��ļ�"<<pszLocalFile<<"ʧ��!";
				return false;
			}

			unsigned read_size=0;
			while( (read_size = pFile->Read(szBuff, 1024)) > 0)
			{
				fout.write(szBuff,read_size);
			}
			fout.close();
		}
		delete pFile;
		delete pServer;

	}
	catch (CInternetException* pEx)
	{
		//catch errors from WinInet
		char pszError[1000];
		pEx->GetErrorMessage(pszError, 1000);
		//AfxMessageBox(pszError); //Ϊ���Զ��� ����ȡ��ʱ�ȳ���ʱ������������Ϣ
		return false;
	}
	session.Close();
	return true;
}