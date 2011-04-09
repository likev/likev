

#include "stdafx.h"
#include <string>

//发送短信 调用飞信接口
bool sendmes(std::string message, std::string sendto)
{
	std::string murl="http://sms.api.bz/fetion.php?username=13663880026&password=qxt0307";
	murl +=  "&sendto="+sendto+"&message="+message;

	try
	{
	CInternetSession session("Mozilla/5.0 (Windows; U; Windows NT 6.0; zh-CN; rv:1.9.1.3) Gecko/20090824 Firefox/3.5.3");
	session.OpenURL(murl.c_str());
	}
	catch (CInternetException* pEx)
	{
		char error[1025];
		pEx->GetErrorMessage(error, 1024);
		AfxMessageBox("Error: "+CString(error));
		pEx->Delete();
		return false;
	}

	return true;
}