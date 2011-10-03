
//火警监测主文件

#include "firewarning.h"

HANDLE hMutex=CreateMutex(NULL,FALSE,NULL);
char tdquit=0;

int main()
{
	LYname s;
	CTime lastTime;

	cout<<"火点监测程序2.1  许方璐于2011年10月3日\n\n"
		     "发现问题或者有好的意见请在网站 grow.sinaapp.com 上面留言\n"
			 "-----------------------------------------------------------------\n\n";

	//dealfire("测 试","bas txt");
	//return 0;

	while(1)
	{
		cout<<"正在检测......   当前时间:"<<CTime::GetCurrentTime().Format("%c").GetBuffer()<<endl<<endl;
		if(FtpConnect(lastTime))
		{
			Sleep(1000*60*10); //10分钟检测一次
		}
		else
		{
			cout<<"登录服务器失败 将在1分钟后重新登录"<<endl;
			cout<<"-----------------------------------------------------------------\n\n";
			Sleep(1000*60);//1分钟后重新检测
		}
	}
}

