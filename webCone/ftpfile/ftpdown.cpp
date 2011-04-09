
#include <afxwin.h>
#include <afxinet.h>

#include <iostream>
#include <stdio.h>
using namespace std;

CString space;
void outdir(CFtpConnection* pConnect)
{   
	


}

//assumes server and file names have been initialized
void GetFtpFile(LPCTSTR pszServerName, LPCTSTR pszRemoteFile, LPCTSTR pszLocalFile)
{
// create a session object to initialize WININET library
// Default parameters mean the access method in the registry
// (that is, set by the "Internet" icon in the Control Panel)
// will be used.

CInternetSession sess("My FTP Session");

CFtpConnection* pConnect = NULL;

try
{
   // Request a connection to ftp.microsoft.com. Default
   // parameters mean that we'll try with username = ANONYMOUS
   // and password set to the machine name @ domain name
   pConnect = sess.GetFtpConnection("172.18.152.245");//"handongxue.223123.yes165.com","handongxue","271828han","luoyang","luoyang",21,1
   pConnect->SetCurrentDirectory("/Yaogan/遥感火点通报");
   CString ss;
   pConnect->GetCurrentDirectory(ss);
   cout<<ss.GetBuffer()<<endl;
   // use a file find object to enumerate files

   	CFtpFileFind finderr(pConnect);
   // start looping
   BOOL bWorking = finderr.FindFile("20090922*.txt");
   
  //		CInternetException ierror(GetLastError());
		//char ec[1000];
		//ierror.GetErrorMessage(ec,1000,0);

		//cout<<"     "<<ec<<endl;

   bool isdir = false;//是否为目录
   CString nowdir;
//bWorking=1;	   cout<<"\a"<<endl;
   while (bWorking)
   {




      bWorking = finderr.FindNextFile();
      isdir = finderr.IsDirectory();

	  CString curdirname;

	  
	  cout<<(LPCTSTR)finderr.GetFilePath();

	  if(isdir)
	  {
		  pConnect->GetCurrentDirectory(nowdir);
		  curdirname = finderr.GetFileName();
		  cout<<"     文件夹\n";

		  //pConnect->SetCurrentDirectory(finder.GetFileName());

		  //space += "     ";
		  //outdir(pConnect);	
		  //
		  //space.Delete(0,5);
		  //pConnect->SetCurrentDirectory(nowdir);

		  //pConnect->GetCurrentDirectory(curdir);
		  //cout<<"CurrentDirectory:    "<<curdir.GetBuffer()<<endl;
		  //finder.FindFile(curdirname);
	  }
	  else
	  {
		  nowdir = finderr.GetFileName();
 		  //pConnect->GetFile(nowdir,"abc\\"+nowdir);
	  }
		  cout<<endl;
   }

   outdir(pConnect);
}
catch (CInternetException* pEx)
{
   TCHAR sz[1024];
   pEx->GetErrorMessage(sz, 1024);
   _tprintf_s("ERROR!  %s\n", sz);
   pEx->Delete();
}

// if the connection is open, close it
if (pConnect != NULL) 
{
   pConnect->Close();
   delete pConnect;
}
}

int mmain()
{
	GetFtpFile("222.73.37.110","/web/index.html","hindex.html");
	system("pause");
	return 0;
}