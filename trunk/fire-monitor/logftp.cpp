

#include "firewarning.h"

//登录ftp服务器  打开指定目录 查找新文件
//assumes server and file names have been initialized
bool FtpConnect(CTime& lastTime)
{

	try
	{
		cout<<"正在登陆服务器......"<<endl;
		
		CInternetSession sess("My FTP Session");
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.243");//匿名登录

		if(pConnect) 
			cout<<"登录服务器成功 正在查找新文件......\n\n";
		else
		{//异常处理
		}

		pConnect->SetCurrentDirectory("/Yaogan/遥感火点通报");

		CString nowdate=CTime::GetCurrentTime().Format("%Y%m%d");//获得本地时间当前日期字符串

		CFtpFileFind finder(pConnect);

		CTime nowTime=lastTime;		
		
		// start looping
		BOOL bWorking = finder.FindFile(nowdate+"*.txt");  //
		
		while (bWorking)//处理每一个查找到的文件
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

		cout<<"\n本次监测结束 将在10分钟后重新登录Ftp服务器查看\n"
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