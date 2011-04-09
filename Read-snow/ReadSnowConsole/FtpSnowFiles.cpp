#include "FtpSnowFiles.h"


void FtpSnowFiles::LoginToFtp()
{
	//CInternetSession sess("My FTP Session");//"65.19.143.3","likev@xufanglu.cn","271828han",21,1

	ftpConnect =  mySession.GetFtpConnection("172.18.152.5","dsbwdown","dsbw2004");//登录

	if(!ftpConnect) return;
		
	isLogin = true;
	//AfxMessageBox("登录服务器成功 正在查找新文件......");
	log_to_file("ftplog.txt","login dsbwdown@172.18.172.5 success...");
	
	ftpConnect->SetCurrentDirectory("/baowen/snow");
	log_to_file("ftplog.txt","set current directory: /baowen/snow");
}

bool FtpSnowFiles::DownFileFromGivenTime(CTime givenTime)
{
	if(!isLogin)
	{
		LoginToFtp();

		if(!isLogin)
		{//不能成功登陆
			log_to_file("ftplog.txt","login failure");
			return false;
		}
	}

	CString localFileName = givenTime.Format("%Y%m%d%H_SNOW.TXT");
	givenTime -= CTimeSpan(0,8,0,0);

	CString findFileName = givenTime.Format("Z_SURF_C_BEZZ_%Y%m%d%H*_O_SNOW-TEMP.TXT");

	log_to_file("ftplog.txt",("will find file"+findFileName).GetBuffer(0));

	CFtpFileFind finder(ftpConnect);
	
	BOOL isFind = finder.FindFile(findFileName);

	
	if(!isFind)
	{
		log_to_file("ftplog.txt","can't find file...");
		return false;
	}

	
	
	finder.FindNextFile();
	CString ftpFileName = finder.GetFileName();
	
	log_to_file("ftplog.txt",("find file "+ftpFileName).GetBuffer(0));

	CInternetFile *pFtpfile = ftpConnect->OpenFile(ftpFileName);
	CFile local_file("snow/"+localFileName,CFile::modeCreate|CFile::modeWrite);
	
	char pBuf[1000]; UINT rnum=0;
	
	while(rnum = pFtpfile->Read(pBuf,1000))
	{
		local_file.Write(pBuf,rnum);
	}
	pFtpfile->Close();
	local_file.Close();

	return true;
}