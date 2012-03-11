#include <afxinet.h> //定义了MFC CInternetSession类等

#include "download-webpage.h"

#include <iostream>
#include <string>

std::string DownHttpPage(const std::string& hostName, const std::string& pathName, const std::string& postData)
{
	using namespace std;
 
	CInternetSession session("your app agent name");
	std::string result = "";
 
	try
	{
		INTERNET_PORT nPort = 80;
		DWORD dwRet = 0;
 
		CHttpConnection* pServer = session.GetHttpConnection(hostName.c_str(), nPort);
		CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, 
												pathName.c_str(),
												0,//referer
												1,//context
												0,//acceptTypes
												0,//version
												INTERNET_FLAG_RELOAD);
 
		CString strHeaders = "Content-Type: application/x-www-form-urlencoded"; // 请求头
 
		//开始发送请求
 
		pFile->SendRequest(strHeaders,(LPVOID)postData.c_str(),postData.size());
		pFile->QueryInfoStatusCode(dwRet);
 
 
		if (dwRet == HTTP_STATUS_OK)
		{
			CString newline;
 
			while(pFile->ReadString(newline))
			{//循环读取每行内容
				result += newline+"\r\n";
			}
 
			//std::cout<<result<<std::endl;//显示返回内容
		}

		delete pFile;
		delete pServer;
 
	}
	catch (CInternetException* pEx)
	{
		//catch errors from WinInet
		TCHAR pszError[200];
		pEx->GetErrorMessage(pszError, 200);
 
		std::cout<<pszError<<std::endl;//显示异常信息
		return "";
	}
	session.Close();
 
	return result;
}