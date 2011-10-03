
#include "comn.h"
#include <afxinet.h>
#include <Mmsystem.h>

#pragma comment(lib,"winmm.lib")//导入声音头文件库

volatile bool close_alert=false;

//单独线程用于连续报警
UINT MyThreadProc(LPVOID pParam ) //报警线程
{
	while(!close_alert)
	{
		PlaySound("warn.wav",NULL,SND_SYNC|SND_FILENAME);
		Sleep(1000);
	}

	return 0;   // thread completed successfully
}

//发送短信 调用tui3接口
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

//下载网页
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
				//cout<<"打开或创建文件"<<pszLocalFile<<"失败!";
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
		//AfxMessageBox(pszError); //为了自动化 当读取超时等出错时不弹出错误信息
		return false;
	}
	session.Close();
	return true;
}