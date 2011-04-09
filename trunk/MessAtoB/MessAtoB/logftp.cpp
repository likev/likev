

#include "stdafx.h"
#include "usefun.h"
#include <fstream>

//��¼ftp������  ��ָ��Ŀ¼ �������ļ�
//assumes server and file names have been initialized
bool FtpConnect(const int forcast_type)
{

	try
	{
		//cout<<"���ڵ�½������......"<<endl;
		
		CInternetSession sess("My FTP Session");//"65.19.143.3","likev@xufanglu.cn","271828han",21,1
		
		CFtpConnection* pConnect =  sess.GetFtpConnection("172.18.152.5","luoyang","luoyang");//��¼

		if(pConnect)
		{
			//AfxMessageBox("��¼�������ɹ� ���ڲ������ļ�......");
			//cout<<\n\n";
		}
		else
		{//�쳣����
		}

		

		CTimeSpan ts(1, 0, 0, 0);
		CTime ct1=CTime::GetCurrentTime();//��ǰ����
		CTime ct2=ct1 - ts;
		
		//��ñ���ʱ�䵱ǰ�����ַ���
		CString tdate=ct1.Format("%Y%m%d"),  ldate=ct2.Format("%Y%m%d");

		CString ftpfn;//Ҫ���ص��ļ���

		switch(forcast_type)
		{
		case 1:
			{
				//�������Ԥ��20��6ʱ ��   			
				ftpfn= "Z_SEVP_C_BFLB_"+ldate+"223500_P_RFFC-SPCC-"+tdate+"0000-16812.TXT";
				break;
			}
		case 2:
			{//12121Ԥ��19��10ʱ��   
				ftpfn = "Z_SEVP_C_BFLB_"+tdate+"022000_P_RFFC-SPCC-"+tdate+"0000-16812.TXT";
				break;
			}
		case 3:
			{
				//��������Ԥ��19��16ʱ ��   
				ftpfn= "Z_SEVP_C_BFLB_"+tdate+"082000_P_RFFC-SPCC-"+tdate+"1200-16812.TXT";
				break;
			}
		default:return false;
		}
		
		

		pConnect->SetCurrentDirectory("/");
		CFtpFileFind finder(pConnect);
		
		
		// start looping
		//��ǰĿ¼����		
		if(!finder.FindFile(ftpfn))
		{
			/*bWorking = finder.FindNextFile();*/
			pConnect->SetCurrentDirectory("/ok");

			if(!finder.FindFile(ftpfn))//okĿ¼����
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