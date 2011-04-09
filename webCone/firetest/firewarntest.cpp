#include <afxwin.h>
#include <afxinet.h>
#include <Mmsystem.h>

#include <iostream>
#include <stdio.h>

#include "firewarntest.h"

#pragma comment(lib,"winmm.lib")//��������ͷ�ļ���

HANDLE hMutex=CreateMutex(NULL,FALSE,NULL);
char tdquit=0;

UINT MyThreadProc(LPVOID pParam ) //�����߳�
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


		cout<<"���ڵ�½������......"<<endl;
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.245");//������¼

		if(pConnect) 
			cout<<"��¼�������ɹ� ���ڲ������ļ�......"<<endl;

		pConnect->SetCurrentDirectory("/Yaogan/ң�л��ͨ��");

		// use a file find object to enumerate files

		CString nowdate=CTime::GetCurrentTime().Format("%Y%m%d");//��ñ���ʱ�䵱ǰ�����ַ���

		CTime tempTime;

		BOOL isdir = false;//�Ƿ�ΪĿ¼
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

			cout<<finder.GetFileName().GetBuffer()<<"����޸�ʱ�䣺  "<<tm1.Format("%c").GetBuffer()<<endl;
			cout<<"����ʱ��   "<<tm2.Format("%c").GetBuffer()<<endl;
			cout<<"����ȡʱ��  "<<tm3.Format("%c").GetBuffer()<<endl;


/*			if (finder.GetLastWriteTime(tempTime))//���Է����޸�ʱ��
			{
				if(tempTime>lastTime)
				{
					//���ļ� ������

					cout<<"�������ļ�"<<finder.GetFileName().GetBuffer()<<"   ���ڲ鿴���������Ƿ��л�......"<<endl;

					CInternetFile *ftpFile=pConnect->OpenFile(finder.GetFileName() );
					
					while(ftpFile->ReadString(warnline))
					{
						for(size_t i=0;i<lynames.a.size();i++)
						{
							const char * firecity=lynames.a[i].c_str();
							if(warnline.Find(firecity) > -1)
							{
								cout<<"\n         "<<firecity<<"�л�,��鿴"<<endl;

								cout<<"\n   �������ֹͣ����... ";
																
								int tparam=1;
								CWinThread * hthread = AfxBeginThread(MyThreadProc, (LPVOID)(&tparam));

								if(cin.get())
									tparam=0;//�����߳�
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

		cout<<"���μ����� ����10���Ӻ����µ�¼Ftp�������鿴"<<endl;

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

	//cout<<"��������  �����2009��9��22��\n\n"
	//	     "������������кõ����������վxufanglu.cn��������\n"
	//		 "-------------------------------------------------------------\n\n";
	//while(1)
	//{
	//	cout<<"���ڼ��......   ��ǰʱ��:"<<CTime::GetCurrentTime().Format("%c").GetBuffer()<<endl;
	//	if(GetFtpFile(lastTime))
	//	{
	//		Sleep(1000*60*10); //10���Ӽ��һ��
	//	}
	//	else
	//	{
	//		cout<<"��¼������ʧ�� ����1���Ӻ����µ�¼"<<endl;
	//		Sleep(1000*60);//1���Ӻ����¼��
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

