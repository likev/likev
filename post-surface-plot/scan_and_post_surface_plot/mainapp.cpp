//#include <afxwin.h>         // MFC 核心和标准组件

#include <iostream>
#include <afxinet.h>
#include <string>
#include <fstream>
#include <sstream>

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
	using namespace std;

	CInternetSession session("Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2) Gecko/20100115 Firefox/3.6");

	try
	{
		INTERNET_PORT nPort = 80;
		DWORD dwRet = 0;

		CHttpConnection* pServer = session.GetHttpConnection(hostName.c_str(), nPort);
		CHttpFile* pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, pathName.c_str());

		CString strHeaders = "Content-Type: application/x-www-form-urlencoded"; // 请求头
		pFile->SendRequest(strHeaders,(LPVOID)postData.c_str(),postData.size());
		pFile->QueryInfoStatusCode(dwRet);

		
		if (dwRet == HTTP_STATUS_OK)
		{
			CString result, newline;
			
			while(pFile->ReadString(newline))
			{
				result += newline+"\r\n";
			}

			display_post_result(result.GetBuffer());
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

std::string& deal_plot_file(const std::string &orgine_name, std::string &result)
{
	std::ifstream fin(orgine_name.c_str());
	if(!fin.is_open())
	{
		display_post_result("打开文件"+orgine_name+"失败！");
	}
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

	return result;
}

void get_file_info(const std::string &orgine_name)
{
	CFileFind finder;
	BOOL bWorking = finder.FindFile(orgine_name.c_str());

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		CTime ftime;

		std::cout<<"\nGetFileName: "<<finder.GetFileName()
			<<"\nGetFilePath: "<<finder.GetFilePath()
			<<"\nGetFileTitle: "<<finder.GetFileTitle()
			<<"\nGetFileURL: "<<finder.GetFileURL()
			<<"\nIsDirectory: "<<finder.IsDirectory();
		

		finder.GetCreationTime(ftime);
		std::cout<<"\nGetCreationTime:"<<ftime.Format("[%Y-%m-%d %H:%M:%S]");
		
		finder.GetLastWriteTime(ftime);
		std::cout<<"\nGetLastWriteTime: "<<ftime.Format("[%Y-%m-%d %H:%M:%S]");
		
		finder.GetLastAccessTime(ftime);
		std::cout<<"\nGetLastAccessTime:"<<ftime.Format("[%Y-%m-%d %H:%M:%S]");

		std::cout<<std::endl;
	}

}

int main(void)
{
	std::cout<<"ok!";
	//PostHttpPage("current.sinaapp.com","post.php","ad=de dd \n  mied&ed=ad dd \n dde");
	
	std::string result;
	//deal_plot_file("Z:/surface/plot/11110908.000",result);

	//display_post_result(result);
	get_file_info("Z:/surface/plot");
	get_file_info("Z:/surface/plot/11110911.000");
}