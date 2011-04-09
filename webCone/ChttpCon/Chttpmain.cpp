
#include <afxwin.h>
#include <string>
#include <iostream>

#include <afxinet.h>
#include <Rasdlg.h>

#pragma comment(lib,"Rasdlg.lib")
//
//#include <windows.h>
//#include <Wininet.h>
//#include <strsafe.h>

using namespace std;

void test()
{

	CInternetSession session("Mozilla/5.0 (Windows; U; Windows NT 6.0; zh-CN; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3");
	try
	{
	//		INTERNET_PROXY_INFO proxyinfo;

	//proxyinfo.dwAccessType = INTERNET_OPEN_TYPE_PROXY;

	//proxyinfo.lpszProxy ="172.18.172.251:80";

	//proxyinfo.lpszProxyBypass = NULL;

	//session.SetOption(INTERNET_OPTION_PROXY,(LPVOID)&proxyinfo,sizeof(INTERNET_PROXY_INFO));

	// const int nTimeOut = 3000;
 //session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, nTimeOut); //重试之间的等待延时
 //session.SetOption(INTERNET_OPTION_CONNECT_RETRIES, 5);   //重试次数
		//session.OpenURL("http://handongxue.223123.yes165.com/requestInfo.php?a=b");,wPort,0,1,0,0,INTERNET_FLAG_TRANSFER_ASCII
		//cout<<"OK\n";
		INTERNET_PORT wPort=80;
		CHttpConnection *chc = session.GetHttpConnection("handongxue.223123.yes165.com");
		CHttpFile * pHttpFile = chc->OpenRequest(CHttpConnection::HTTP_VERB_GET,"/requestInfo.php?a=b");
		
		pHttpFile->SendRequest();


		cout<<(pHttpFile->GetFileURL()).GetBuffer()<<endl;
		cout<<(pHttpFile->GetFileURL()).GetBuffer()<<endl;
		CString sl;
		string s;int i=0;

		DWORD dwStateCode;

        pHttpFile->QueryInfoStatusCode(dwStateCode);

		DWORD ecode=GetLastError();

		CInternetException ierror(ecode);
		char ec[1000];
		ierror.GetErrorMessage(ec,1000,0);

		cout<<ecode<<"     "<<ec<<endl;
		ierror.ReportError();

		cout<<"dwStateCode  "<<dwStateCode<<endl;

		while(pHttpFile->ReadString(sl))
		{
			s=sl.GetBuffer();
			sl.ReleaseBuffer();
			cout<<s<<endl;
		}

	}
	catch(CInternetException* a)
	{
    
		char c[1000];
		a->ReportError();
		a->GetErrorMessage(c,1000,0);
		cout<<a->m_dwError<<endl;
		cout<<GetLastError()<<endl;
		cout<<c<<endl;
	}




}



int mmain()
{
	test();
	return 0;
}