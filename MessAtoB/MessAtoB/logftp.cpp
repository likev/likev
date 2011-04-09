

#include "stdafx.h"
#include "usefun.h"
#include <fstream>

//登录ftp服务器  打开指定目录 查找新文件
//assumes server and file names have been initialized
bool FtpConnect(const int forcast_type)
{

	try
	{
		//cout<<"正在登陆服务器......"<<endl;
		
		CInternetSession sess("My FTP Session");//"65.19.143.3","likev@xufanglu.cn","271828han",21,1
		
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.5","luoyang","luoyang");//登录

		if(pConnect)
		{
			//AfxMessageBox("登录服务器成功 正在查找新文件......");
			//cout<<\n\n";
		}
		else
		{//异常处理
		}

		

		CTimeSpan ts(1, 0, 0, 0);
		CTime ct1=CTime::GetCurrentTime();//当前日期
		CTime ct2=ct1 - ts;
		
		//获得本地时间当前日期字符串
		CString tdate=ct1.Format("%Y%m%d"),  ldate=ct2.Format("%Y%m%d");

		CString ftpfn;//要下载的文件名

		switch(forcast_type)
		{
		case 1:
			{
				//早间县区预报20日6时 ：   			
				ftpfn= "Z_SEVP_C_BFLB_"+ldate+"223500_P_RFFC-SPCC-"+tdate+"0000-16812.TXT";
				break;
			}
		case 2:
			{//12121预报19日10时：   
				ftpfn = "Z_SEVP_C_BFLB_"+tdate+"022000_P_RFFC-SPCC-"+tdate+"0000-16812.TXT";
				break;
			}
		case 3:
			{
				//下午县区预报19日16时 ：   
				ftpfn= "Z_SEVP_C_BFLB_"+tdate+"082000_P_RFFC-SPCC-"+tdate+"1200-16812.TXT";
				break;
			}
		default:return false;
		}
		
		

		pConnect->SetCurrentDirectory("/");
		CFtpFileFind finder(pConnect);
		
		
		// start looping
		//当前目录查找		
		if(!finder.FindFile(ftpfn))
		{
			/*bWorking = finder.FindNextFile();*/
			pConnect->SetCurrentDirectory("/ok");

			if(!finder.FindFile(ftpfn))//ok目录查找
			{
				return false;
			}
		}

		CInternetFile *pIf = pConnect->OpenFile(ftpfn);
		CFile Lf("b.txt",CFile::modeCreate|CFile::modeWrite);
		char pBuf[1000]; UINT rnum=0;
		while(rnum = pIf->Read(pBuf,1000))
		{
			Lf.Write(pBuf,rnum);
		}
		pIf->Close();
		Lf.Close();

		if (pConnect != NULL) 
		{
			pConnect->Close();
			delete pConnect;
		}

		return true;
	}
	catch (CInternetException* pEx)
	{
		char error[1025];
		pEx->GetErrorMessage(error, 1024);
		////cout<<"ERROR!"<<error<<endl;
		//AfxMessageBox("Error: "+CString(error));
		pEx->Delete();
		return false;
	}

	return true;
}