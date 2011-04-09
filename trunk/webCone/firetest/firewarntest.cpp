#include <afxwin.h>
#include <afxinet.h>
#include <Mmsystem.h>

#include <iostream>
#include <stdio.h>

#include "firewarntest.h"

#pragma comment(lib,"winmm.lib")//导入声音头文件库

HANDLE hMutex=CreateMutex(NULL,FALSE,NULL);
char tdquit=0;

UINT MyThreadProc(LPVOID pParam ) //报警线程
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

//UINT MyThreadProc(LPVOID pParam )
//{
//	clock_t ct=clock();
//	int *p=(int *)pParam;
//	while(*p)
//	{
//		cout<<"\a\a\a";
//
//		while(clock()-ct<3*CLOCKS_PER_SEC)
//		{
//
//		}
//		ct = clock();
//	}
//	return 0;   // thread completed successfully
//}

//assumes server and file names have been initialized
bool GetFtpFile(CTime& lastTime)
{
	LYname lynames;

	try
	{

		CInternetSession sess("My FTP Session");


		cout<<"正在登陆服务器......"<<endl;
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.245");//匿名登录

		if(pConnect) 
			cout<<"登录服务器成功 正在查找新文件......"<<endl;

		pConnect->SetCurrentDirectory("/Yaogan/遥感火点通报");

		// use a file find object to enumerate files

		CString nowdate=CTime::GetCurrentTime().Format("%Y%m%d");//获得本地时间当前日期字符串

		CTime tempTime;

		BOOL isdir = false;//是否为目录
		CString curdirname, warnline;

		CFtpFileFind finder(pConnect);
		// start looping

		BOOL bWorking = finder.FindFile(nowdate+"*.txt");  //

		while (bWorking)
		{

			bWorking = finder.FindNextFile();
			CTime tm1,tm2,tm3;

			finder.GetLastWriteTime(tm1);
			finder.GetCreationTime(tm2);
			finder.GetLastAccessTime(tm3);

			cout<<finder.GetFileName().GetBuffer()<<"最后修改时间：  "<<tm1.Format("%c").GetBuffer()<<endl;
			cout<<"创建时间   "<<tm2.Format("%c").GetBuffer()<<endl;
			cout<<"最后存取时间  "<<tm3.Format("%c").GetBuffer()<<endl;


/*			if (finder.GetLastWriteTime(tempTime))//可以访问修改时间
			{
				if(tempTime>lastTime)
				{
					//新文件 做处理

					cout<<"发现新文件"<<finder.GetFileName().GetBuffer()<<"   正在查看洛阳地区是否有火警......"<<endl;

					CInternetFile *ftpFile=pConnect->OpenFile(finder.GetFileName() );
					
					while(ftpFile->ReadString(warnline))
					{
						for(size_t i=0;i<lynames.a.size();i++)
						{
							const char * firecity=lynames.a[i].c_str();
							if(warnline.Find(firecity) > -1)
							{
								cout<<"\n         "<<firecity<<"有火警,请查看"<<endl;

								cout<<"\n   按任意键停止声音... ";
																
								int tparam=1;
								CWinThread * hthread = AfxBeginThread(MyThreadProc, (LPVOID)(&tparam));

								if(cin.get())
									tparam=0;//结束线程
							}
						}
					}
					ftpFile->Close();

					lastTime = tempTime;
				}
				else
				{
					continue;
				}
			}

			
			else
			{
				return false;
			}
			
			*/
			cout<<endl;
		}

		if (pConnect != NULL) 
		{
			pConnect->Close();
			delete pConnect;
		}

		cout<<"本次监测结束 将在10分钟后重新登录Ftp服务器查看"<<endl;

		return true;
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


void fun(void)
{
	tdquit=0;
								
	CWinThread * hthread = AfxBeginThread(MyThreadProc,NULL);
	WaitForSingleObject(hMutex,INFINITE);
	cin>>tdquit;
	ReleaseMutex(hMutex);

	WaitForSingleObject(hthread->m_hThread,INFINITE);

}

int main()
{
	//LYname s;
	//CTime lastTime;

	//cout<<"火点监测程序  许方璐于2009年9月22日\n\n"
	//	     "发现问题或者有好的意见请在网站xufanglu.cn上面留言\n"
	//		 "-------------------------------------------------------------\n\n";
	//while(1)
	//{
	//	cout<<"正在检测......   当前时间:"<<CTime::GetCurrentTime().Format("%c").GetBuffer()<<endl;
	//	if(GetFtpFile(lastTime))
	//	{
	//		Sleep(1000*60*10); //10分钟检测一次
	//	}
	//	else
	//	{
	//		cout<<"登录服务器失败 将在1分钟后重新登录"<<endl;
	//		Sleep(1000*60);//1分钟后重新检测
	//	}
	//}
	int i=0;
	while(++i)
	{
		
		cout<<"-----------------------"<<i<<"-------------------------\n\n";
		system("pause");
fun();

	}

}

