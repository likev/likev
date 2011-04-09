#include "http-deal.h"
#include <iostream>
#include <fstream>
#include <string>

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
		CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, 
			                                    pszURL,0,1,0,0,INTERNET_FLAG_RELOAD );//��ʹ�û�������
		pFile->SendRequest();
		pFile->QueryInfoStatusCode(dwRet);

		if (dwRet == HTTP_STATUS_OK)
		{
			char szBuff[1024]={};
			ofstream fout(pszLocalFile,ios_base::out|ios_base::binary);
			if(!fout.is_open())
			{
				cout<<"�򿪻򴴽��ļ�"<<pszLocalFile<<"ʧ��!";
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
		TCHAR pszError[64];
		pEx->GetErrorMessage(pszError, 64);
		//_tprintf_s(_T("%63s"), pszError);
		return false;
	}
	session.Close();
	return true;
}

void PostHttpPage(LPCTSTR pszServerName, LPCTSTR pszURL, std::string optional, LPCTSTR pszLocalFile)
{
	using namespace std;

	CInternetSession session(_T("Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2) Gecko/20100115 Firefox/3.6"));

	try
	{
		CString strServerName;
		INTERNET_PORT nPort = 80;
		DWORD dwRet = 0;

		CHttpConnection* pServer = session.GetHttpConnection(pszServerName, nPort);
		CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, pszURL);

		CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded"); // ����ͷ
		pFile->SendRequest(strHeaders,(LPVOID)optional.c_str(),optional.size());
		pFile->QueryInfoStatusCode(dwRet);

		if (dwRet == HTTP_STATUS_OK)
		{
			char szBuff[1024]={};
			ofstream fout(pszLocalFile,ios_base::out|ios_base::binary);
			if(!fout.is_open())
			{
				cout<<"�򿪻򴴽��ļ�"<<pszLocalFile<<"ʧ��!";
				return;
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
		TCHAR pszError[64];
		pEx->GetErrorMessage(pszError, 64);
		_tprintf_s(_T("%63s"), pszError);
	}
	session.Close();
}

//�ж��Ƿ�����
int Fun_InternetGetConnectedState()
{
	//#define INTERNET_CONNECTION_MODEM           1
	//#define INTERNET_CONNECTION_LAN             2
	//#define INTERNET_CONNECTION_PROXY           4
	//#define INTERNET_CONNECTION_MODEM_BUSY      8

	DWORD   flags;//������ʽ
	BOOL   m_bOnline=TRUE;//�Ƿ�����  

	m_bOnline=InternetGetConnectedState(&flags,0);  
	if(m_bOnline)//����  
	{  
		if ((flags & INTERNET_CONNECTION_MODEM) ==INTERNET_CONNECTION_MODEM)
		{
			//std::cout<<"���ߣ���������\n";
			return 1;
		}
		if ((flags & INTERNET_CONNECTION_LAN) ==INTERNET_CONNECTION_LAN)
		{
			//std::cout<<"���ߣ�ͨ��������\n";
			return 2;
		}
		if ((flags & INTERNET_CONNECTION_PROXY) ==INTERNET_CONNECTION_PROXY)
		{
			//std::cout<<"���ߣ�����\n";
			return 3;
		}
		if ((flags & INTERNET_CONNECTION_MODEM_BUSY) ==INTERNET_CONNECTION_MODEM_BUSY)
		{
			//std::cout<<"MODEM��������INTERNET����ռ��\n";
			return 4;
		}
	}
	else
	{
		//std::cout<<"������\n";
		return 0;
	}
	return 0;
}