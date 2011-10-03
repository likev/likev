

#include "firewarning.h"

//��¼ftp������  ��ָ��Ŀ¼ �������ļ�
//assumes server and file names have been initialized
bool FtpConnect(CTime& lastTime)
{

	try
	{
		cout<<"���ڵ�½������......"<<endl;
		
		CInternetSession sess("My FTP Session");
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.243");//������¼

		if(pConnect) 
			cout<<"��¼�������ɹ� ���ڲ������ļ�......\n\n";
		else
		{//�쳣����
		}

		pConnect->SetCurrentDirectory("/Yaogan/ң�л��ͨ��");

		CString nowdate=CTime::GetCurrentTime().Format("%Y%m%d");//��ñ���ʱ�䵱ǰ�����ַ���

		CFtpFileFind finder(pConnect);

		CTime nowTime=lastTime;		
		
		// start looping
		BOOL bWorking = finder.FindFile(nowdate+"*.txt");  //
		
		while (bWorking)//����ÿһ�����ҵ����ļ�
		{
			bWorking = finder.FindNextFile();
			dealfile(finder, pConnect, lastTime, nowTime);
		}
		lastTime=nowTime;

		if (pConnect != NULL) 
		{
			pConnect->Close();
			delete pConnect;
		}

		cout<<"\n���μ����� ����10���Ӻ����µ�¼Ftp�������鿴\n"
			     "------------------------------------------------------------------\n\n";

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