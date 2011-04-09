// readhttp2.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include <fstream>
#include <string>

#include <afxwin.h>
#include <afxinet.h>

using namespace std;

bool f1(string url,string fname)
{
	ofstream fout(fname.c_str());
	
    //初始化 WinInet。	
	CInternetSession session("HttpClient");                          

	//连接到 HTTP 服务器,打开 HTTP 请求,返回 CHttpFile 对象。
    CHttpFile* pfile = (CHttpFile *)session.OpenURL(url.c_str());
	if(!pfile)
		return false;

	//状态码
	DWORD dwStatusCode;
	pfile -> QueryInfoStatusCode(dwStatusCode);
	cout<<"dwStatusCode  "<<dwStatusCode<<endl;
	if(dwStatusCode == HTTP_STATUS_OK)
	{
		CString content;
		CString data;

		int i=0;string sline;
		while (pfile -> ReadString(data))
		{
			sline=data.TrimLeft().TrimRight().GetBuffer();
			data.ReleaseBuffer();

			fout<<sline<<endl;
		}
	}
	else
		return false;

	pfile -> Close();
	delete pfile;

	fout.close();
	session.Close();

	return true;
}

int main()
{	
	string url = "http://www.google.com",  fname="g.html";
	if(f1(url,fname))
		cout<<"success"<<endl;



	return   0 ;
}
