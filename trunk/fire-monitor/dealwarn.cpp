#include "firewarning.h"

//发现火警时处理
void dealfire(string firecity,string filename)
{
	string firemes=firecity+"有火警,请查看  火警文件为: "+filename;
	cout<<"\n         "<<firemes<<endl;

	cout<<"正在发送短信...     ";

	if(sendmes(firemes,"13663880026,13698835392") )
		cout<<"短信已发出"<<endl;
	else
		cout<<"发送失败"<<endl;

	tdquit=0;//全局char 控制线程关闭

	CWinThread * hthread = AfxBeginThread(MyThreadProc,NULL);
	cout<<"\n   按任意键停止声音... ";

	WaitForSingleObject(hMutex,INFINITE);
	cin>>tdquit;
	ReleaseMutex(hMutex);

	WaitForSingleObject(hthread->m_hThread,INFINITE);//等待线程结束
}

bool dealfile(CFtpFileFind & finder, CFtpConnection* pConnect, CTime & lastTime, CTime & nowTime)
{

	LYname lynames;		
	CString curdirname, warnline;
	CTime tempTime;

	if (finder.GetLastWriteTime(tempTime))//可以访问修改时间
	{
		if(tempTime>lastTime)
		{
			//新文件 做处理

			if(tempTime>nowTime)
				nowTime=tempTime;

			char * filename = finder.GetFileName().GetBuffer();
			cout<<"发现新文件"<<filename<<"   正在查看洛阳地区是否有火警......"<<endl;

			CInternetFile *ftpFile=pConnect->OpenFile(filename );

			while(ftpFile->ReadString(warnline))
			{
				for(size_t i=0;i<lynames.a.size();i++)
				{
					string firecity=lynames.a[i];
					if(warnline.Find(firecity.c_str() ) > -1)
					{
						dealfire(firecity,filename);
					}
				}
			}
			ftpFile->Close();
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}

	return true;//发现新文件并做处理
}