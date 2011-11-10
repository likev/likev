//#include <afxwin.h>         // MFC 核心和标准组件

#include <iostream>
#include <afxinet.h>

#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "filename-time.h"

void display_post_result(std::string result)
{
	std::cout<<result<<std::endl;

	std::ofstream fout("log-info.txt",std::ios_base::out|std::ios_base::app);
	if(!fout.is_open())
	{
		std::cout<<"打开或创建文件log-info.txt失败!";
		return;
	}
	CTime now = CTime::GetCurrentTime();

	fout<<now.Format("[%Y-%m-%d %H:%M:%S]: \r\n")<<result<<std::endl;
}

bool PostHttpPage(const std::string& hostName, const std::string& pathName, const std::string& postData)
{

	CInternetSession session("Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2) Gecko/20100115 Firefox/3.6");

	session.SetOption(INTERNET_OPTION_SEND_TIMEOUT, 60*1000);
	session.SetOption(INTERNET_OPTION_RECEIVE_TIMEOUT, 60*1000);

	try
	{
		INTERNET_PORT nPort = 80;
		DWORD dwRet = 0;

		CHttpConnection* pServer = session.GetHttpConnection(hostName.c_str(), nPort);
		CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, pathName.c_str());

		CString strHeaders = "Content-Type: application/x-www-form-urlencoded"; // 请求头
		
		display_post_result("posting data...");
		
		pFile->SendRequest(strHeaders,(LPVOID)postData.c_str(),postData.size());
		pFile->QueryInfoStatusCode(dwRet);

		
		if (dwRet == HTTP_STATUS_OK)
		{
			CString result, newline;
			
			while(pFile->ReadString(newline))
			{
				result += newline+"\r\n";
			}

			display_post_result(("back:"+result).GetBuffer());
		}
		else
		{
			display_post_result("post 失败！");
			return false;
		}
		delete pFile;
		delete pServer;

	}
	catch (CInternetException* pEx)
	{
		//catch errors from WinInet
		TCHAR pszError[200];
		pEx->GetErrorMessage(pszError, 200);
		
		display_post_result(pszError);
		return false;
	}
	session.Close();

	return true;
}

bool deal_plot_file(std::string orgine_name, std::string &result)
{
	std::ifstream fin(orgine_name.c_str());
	if(!fin.is_open())
	{
		display_post_result("打开文件"+orgine_name+"失败！");
		return false;
	}
	
	display_post_result("dealing "+orgine_name+"...");

	result = "";
	std::string linestr, number;

	std::istringstream stringin;
	while(std::getline(fin,linestr))
	{
		stringin.clear();
		stringin.str(linestr);
		if(stringin>>number)
		{
			if(number.size() == 5)
			{
				result += number;
				stringin>>number>>number>>number>>number;

				while(stringin>>number)
				{
					result += ' ' + number;
				}
				//result += "\r\n";

			}
			else
			{
				result += linestr + "\r\n";
			}
		}
	}

	return true;
}

CTime get_last_time()
{
	int year,month,day,hour,minute,second;

	year   = GetPrivateProfileInt("lastest","year",1970,"./scan.ini");
	month  = GetPrivateProfileInt("lastest","month",1,"./scan.ini");
	day    = GetPrivateProfileInt("lastest","day",2,"./scan.ini");
	hour   = GetPrivateProfileInt("lastest","hour",0,"./scan.ini");
	minute = GetPrivateProfileInt("lastest","minute",0,"./scan.ini");
	second = GetPrivateProfileInt("lastest","second",0,"./scan.ini");

	return CTime(year,month,day,hour,minute,second);
}

bool set_latest_time(const CTime &latest)
{
	BOOL year,month,day,hour,minute,second;

	year   = WritePrivateProfileString("lastest","year",latest.Format("%Y"),"./scan.ini");
	month  = WritePrivateProfileString("lastest","month",latest.Format("%#m"),"./scan.ini");
	day    = WritePrivateProfileString("lastest","day",latest.Format("%#d"),"./scan.ini");
	hour   = WritePrivateProfileString("lastest","hour",latest.Format("%#H"),"./scan.ini");
	minute = WritePrivateProfileString("lastest","minute",latest.Format("%#M"),"./scan.ini");
	second = WritePrivateProfileString("lastest","second",latest.Format("%#S"),"./scan.ini");

	return year && month && day && hour && minute && second;
}

std::string get_plot_dir()
{
	char dir_buf[1024] ;
	DWORD result = GetPrivateProfileString("path","plotdir","Z:/surface/plot/",dir_buf,1000,"./scan.ini");
	
	return dir_buf;
}

bool deal_file_list(std::vector<FilenameTime> &file_list)
{
	std::sort(file_list.begin(), file_list.end(), time_less_than);
	
	std::string result;
	//
	for(size_t i=0; i != file_list.size(); i++)
	{
		deal_plot_file(file_list[i].get_name(), result);

		bool is_post_success = 
			PostHttpPage("current.sinaapp.com","update-mysql-from-post.php","app-content="+result);
		
		if(!is_post_success) 
		{
			display_post_result("post maybe failure...");
			return false;
		}
		else
		{
			set_latest_time(file_list[i].get_time());
			
			display_post_result("wait 2 minute...");
			Sleep(2*1000*60);
			display_post_result("continue next file find...");
		}
	}

	return true;
}

bool scan_plot_dir()
{
	CTime last_time = get_last_time();
	
	CFileFind finder;

	std::string dir = get_plot_dir();
	if('\\' != dir[dir.size()-1 ] && '/' != dir[dir.size()-1 ] )
	{
		dir += '/';
	}
	
	std::replace(dir.begin(),dir.end(),'\\','/');

	BOOL bWorking = finder.FindFile( (dir+ "*.000").c_str() );

	CTime ftime;

	std::vector<FilenameTime> file_list;

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		
		if(finder.GetLastWriteTime(ftime) 
			&& ftime > last_time )
		{
			file_list.push_back(FilenameTime(finder.GetFilePath().GetBuffer(), ftime));
		}
	}

	bool all_success = deal_file_list(file_list);
	
	return all_success;
}

int main(void)
{
	std::cout<<"version 1.4  2011-11-10\n"
		<<"-------------------------------------\n";
	while(true)
	{
		scan_plot_dir();

		display_post_result("wait 5 minute...");
		Sleep(5*1000*60);
		display_post_result("continue next plot dir scan...");
	}

}