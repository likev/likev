
//包含文件 包含了需要的头文件 定义了洛阳地名类 声明了定义的函数和全局变量

#pragma once

#include <afxwin.h>
#include <afxinet.h>

#include <string>
#include <vector>
#include <iostream>
	
using namespace std;

class LYname
{
public:
	vector<string> a;

	LYname()
	{
		char * b[10]={"洛阳","栾川","洛宁","孟津","汝阳","嵩县","新安","伊川","偃师","宜阳"};

		a.assign(b,b+10);
	}

	void out(void)
	{
		for(size_t i=0;i<a.size();i++)
		{
			cout<<a[i]<<"   ";
		}
		cout<<endl;
	}
};


//声明函数
UINT MyThreadProc(LPVOID pParam );
bool sendmes(string message="begin", string sendto="13663880026");
bool FtpConnect(CTime& lastTime);
void dealfire(string firecity,string filename);
bool dealfile(CFtpFileFind & finder, CFtpConnection* pConnect, CTime & lastTime, CTime & nowTime);

//声明全局变量

extern HANDLE hMutex;
extern char tdquit;