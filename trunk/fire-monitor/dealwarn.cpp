#include "firewarning.h"

//���ֻ�ʱ����
void dealfire(string firecity,string filename)
{
	string firemes=firecity+"�л�,��鿴  ���ļ�Ϊ: "+filename;
	cout<<"\n         "<<firemes<<endl;

	cout<<"���ڷ��Ͷ���...     ";

	if(sendmes(firemes,"13663880026,13698835392") )
		cout<<"�����ѷ���"<<endl;
	else
		cout<<"����ʧ��"<<endl;

	tdquit=0;//ȫ��char �����̹߳ر�

	CWinThread * hthread = AfxBeginThread(MyThreadProc,NULL);
	cout<<"\n   �������ֹͣ����... ";

	WaitForSingleObject(hMutex,INFINITE);
	cin>>tdquit;
	ReleaseMutex(hMutex);

	WaitForSingleObject(hthread->m_hThread,INFINITE);//�ȴ��߳̽���
}

bool dealfile(CFtpFileFind & finder, CFtpConnection* pConnect, CTime & lastTime, CTime & nowTime)
{

	LYname lynames;		
	CString curdirname, warnline;
	CTime tempTime;

	if (finder.GetLastWriteTime(tempTime))//���Է����޸�ʱ��
	{
		if(tempTime>lastTime)
		{
			//���ļ� ������

			if(tempTime>nowTime)
				nowTime=tempTime;

			char * filename = finder.GetFileName().GetBuffer();
			cout<<"�������ļ�"<<filename<<"   ���ڲ鿴���������Ƿ��л�......"<<endl;

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

	return true;//�������ļ���������
}