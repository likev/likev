
//�����ļ� ��������Ҫ��ͷ�ļ� ���������������� �����˶���ĺ�����ȫ�ֱ���

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
		char * b[10]={"����","�ﴨ","����","�Ͻ�","����","����","�°�","����","��ʦ","����"};

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


//��������
UINT MyThreadProc(LPVOID pParam );
bool sendmes(string message="begin", string sendto="13663880026");
bool FtpConnect(CTime& lastTime);
void dealfire(string firecity,string filename);
bool dealfile(CFtpFileFind & finder, CFtpConnection* pConnect, CTime & lastTime, CTime & nowTime);

//����ȫ�ֱ���

extern HANDLE hMutex;
extern char tdquit;