#ifndef _FTP_SNOW_FILES
#define _FTP_SNOW_FILES

#include "comn.h"
#include "afxinet.h"
#include "useful-func.h"

class FtpSnowFiles
{
	CInternetSession mySession;
	CFtpConnection* ftpConnect;
	bool isLogin;


	void LoginToFtp();

	bool DownFileFromGivenTime(CTime givenTime);

public:
	FtpSnowFiles()
		:mySession("My FTP Session"),ftpConnect(NULL), isLogin(false)
	{};

	bool DownGivenTimeFile(CTime givenTime)
	{
		try
		{
			DownFileFromGivenTime(givenTime);
		}
		catch (CInternetException* pEx)
		{
			char error[1025];
			pEx->GetErrorMessage(error, 1024);
			log_to_file("ftplog.txt","ERROR: "+std::string()+error);
			//AfxMessageBox("Error: "+CString(error));
			pEx->Delete();
			return false;
		}

		return true;
	}

public:
	~FtpSnowFiles()
	{
		//É¾³ýFTPÁ¬½Ó
		if(ftpConnect)
		{
			ftpConnect->Close();
			delete ftpConnect;
			log_to_file("ftplog.txt","close ftp");
		}
	};

};

#endif //_FTP_SNOW_FILES