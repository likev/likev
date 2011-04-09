#include <iostream>
//#include <windows.h>
//#include <ctime>
//#include <Wininet.h>
// //#include <afxwin.h>
//#pragma comment(lib, "wininet.lib")
//
using namespace std;
//int main()
//{
//	cout<<"begin..."<<endl;
//	
//	HINTERNET Hnet = InternetOpen("MYREAD",INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
//
//   INTERNET_PROXY_INFO szBuf;
// DWORD dwSize = sizeof(szBuf);
//InternetQueryOption(Hnet, INTERNET_OPTION_PROXY, &szBuf, &dwSize); 
//
//	clock_t t=clock();
//	
//	for(int a=0;a<100;a++)
//	{
//        while(clock()-t<1*CLOCKS_PER_SEC)
//		{
//		}
//		t=clock();
//	
//		cout<<a<<"   "<<endl;
//		
//	}
//}
#include <stdio.h>
#include <afxwin.h>
#include <afxinet.h>

#include <Wininet.h>
#include <Sensapi.h>

#pragma comment(lib, "Sensapi.lib")

void f1()
{
	INTERNET_PER_CONN_OPTION_LIST    List;
INTERNET_PER_CONN_OPTION         Option[5];
unsigned long                    nSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);

Option[0].dwOption = INTERNET_PER_CONN_AUTOCONFIG_URL;
Option[1].dwOption = INTERNET_PER_CONN_AUTODISCOVERY_FLAGS;
Option[2].dwOption = INTERNET_PER_CONN_FLAGS;
Option[3].dwOption = INTERNET_PER_CONN_PROXY_BYPASS;
Option[4].dwOption = INTERNET_PER_CONN_PROXY_SERVER;

List.dwSize = sizeof(INTERNET_PER_CONN_OPTION_LIST);
List.pszConnection = NULL;
List.dwOptionCount = 5;
List.dwOptionError = 0;
List.pOptions = Option;

if(!InternetQueryOption(NULL, INTERNET_OPTION_PER_CONNECTION_OPTION, &List, &nSize))
   printf("InternetQueryOption failed! (%d)\n", GetLastError());
   if(Option[0].Value.pszValue != NULL)
   printf("%s\n", Option[0].Value.pszValue);

if((Option[2].Value.dwValue & PROXY_TYPE_AUTO_PROXY_URL) == PROXY_TYPE_AUTO_PROXY_URL)
  printf("PROXY_TYPE_AUTO_PROXY_URL\n");

if((Option[2].Value.dwValue & PROXY_TYPE_AUTO_DETECT) == PROXY_TYPE_AUTO_DETECT)
   printf("PROXY_TYPE_AUTO_DETECT\n");

INTERNET_VERSION_INFO      Version;
nSize = sizeof(INTERNET_VERSION_INFO);

InternetQueryOption(NULL, INTERNET_OPTION_VERSION, &Version, &nSize);

if(Option[0].Value.pszValue != NULL)
   GlobalFree(Option[0].Value.pszValue);

if(Option[3].Value.pszValue != NULL)
{
    cout<<Option[3].Value.pszValue<<endl;
	GlobalFree(Option[3].Value.pszValue);
}

if(Option[4].Value.pszValue != NULL)
{
	cout<<Option[4].Value.pszValue<<endl;
   GlobalFree(Option[4].Value.pszValue);
}

}

//int main()
//{
//	f1();
//
//	CInternetSession session("HttpClient");
//	char *url = "http://www.baidu.com";
//	
//
//	//INTERNET_PROXY_INFO proxyinfo;
//
//	//proxyinfo.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
//
//	//proxyinfo.lpszProxy ="172.18.172.251:80";
//
//	//proxyinfo.lpszProxyBypass = NULL;
//
//	//session.SetOption(INTERNET_OPTION_PROXY,(LPVOID)&proxyinfo,
//
//	//	sizeof(INTERNET_PROXY_INFO));
//
//	INTERNET_PROXY_INFO proxyinfo2;
//		proxyinfo2.dwAccessType = INTERNET_OPEN_TYPE_PROXY;
//
//	proxyinfo2.lpszProxy ="172.18.172.251:80";
//
//	proxyinfo2.lpszProxyBypass = NULL;
//	DWORD infolen=sizeof(INTERNET_PROXY_INFO);
//
//	if(session.QueryOption(INTERNET_OPTION_PROXY,(LPVOID)&proxyinfo2,(LPDWORD)&infolen))
//		cout<<"ok\n";
//
// 
//
//
//	  CStdioFile* file1= session.OpenURL(url);
//    CHttpFile* pfile = (CHttpFile *)file1;
//	DWORD dwStatusCode;
//	pfile -> QueryInfoStatusCode(dwStatusCode);
//	if(dwStatusCode == HTTP_STATUS_OK)
//	{
//		CString content;
//		CString data;
//		while (pfile -> ReadString(data))
//		{
//			content  += data + "\r\n";
//		}
//		content.TrimRight();
//		printf(" %s\n " ,(LPCTSTR)content);
//	}
//	pfile -> Close();
//	delete pfile;
//	session.Close();
//
//	return   0 ;
//}

void Fun_InternetGetConnectedState()
{
 
//#define INTERNET_CONNECTION_MODEM           1
//#define INTERNET_CONNECTION_LAN             2
//#define INTERNET_CONNECTION_PROXY           4
//#define INTERNET_CONNECTION_MODEM_BUSY      8
 
DWORD   flags;//上网方式
BOOL   m_bOnline=TRUE;//是否在线 
m_bOnline=InternetGetConnectedState(&flags,0);  
if(m_bOnline)//在线  
{  
   if ((flags & INTERNET_CONNECTION_MODEM) ==INTERNET_CONNECTION_MODEM)
   {
    cout<<"在线：拨号上网\n";
   }
   if ((flags & INTERNET_CONNECTION_LAN) ==INTERNET_CONNECTION_LAN)
   {
    cout<<"在线：通过局域网\n";
   }
   if ((flags & INTERNET_CONNECTION_PROXY) ==INTERNET_CONNECTION_PROXY)
   {
    cout<<"在线：代理\n";
   }
   if ((flags & INTERNET_CONNECTION_MODEM_BUSY) ==INTERNET_CONNECTION_MODEM_BUSY)
   {
    cout<<"MODEM被其他非INTERNET连接占用\n";
   }
}
else
   cout<<"不在线\n";
}
void Fun_IsNetworkAlive()
{
 
DWORD   flags;//上网方式
BOOL   m_bOnline=TRUE;//是否在线 
m_bOnline=IsNetworkAlive(&flags);  
if(m_bOnline)//在线  
{  
   if ((flags & NETWORK_ALIVE_LAN) ==NETWORK_ALIVE_LAN)
   {
    cout<<"在线：NETWORK_ALIVE_LAN\n";
   }
   if ((flags & NETWORK_ALIVE_WAN) ==NETWORK_ALIVE_WAN)
   {
    cout<<"在线：NETWORK_ALIVE_WAN\n";
   }
   if ((flags & NETWORK_ALIVE_AOL) ==NETWORK_ALIVE_AOL)
   {
    cout<<"在线：NETWORK_ALIVE_AOL\n";
   }
}
else
   cout<<"不在线\n";
}
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
int nRetCode = 0;
// initialize MFC and print and error on failure
if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
{
   // TODO: change error code to suit your needs
   cerr << _T("Fatal Error: MFC initialization failed") << endl;
   nRetCode = 1;
}
else
{
   // TODO: code your application''s behavior here.
//   CString strHello;
//   strHello.LoadString(IDS_HELLO);
//   cout << (LPCTSTR)strHello << endl;


	if(InternetCheckConnection("http://www.baidu.com/",1,0))
		cout<<"InternetCheckConnection :1"<<endl;
	else
		cout<<"InternetCheckConnection :0"<<endl;


	DWORD ConnectState=0,StateSize=sizeof(DWORD);

	if(InternetQueryOption(NULL,INTERNET_OPTION_CONNECTED_STATE,&ConnectState,(LPDWORD)&StateSize))
		cout<<"InternetQueryOption :"<<ConnectState<<endl;

   int i=0;
   while (TRUE)
   {
    cout << "请选择测试的方式：\n"
     << "1. InternetGetConnectedState\n"
     << "2. IsNetworkAlive"
     << endl;
    cin >> i;
    switch(i)
    {
    case 1:
     Fun_InternetGetConnectedState();
     break;
    case 2:
     Fun_IsNetworkAlive();
     break;
    default:
     cout << "错误！\n";
    }
    cout << endl;
   }
}
return nRetCode;
}