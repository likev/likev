
//火警监测主文件

#include "firewarning.h"

HANDLE hMutex=CreateMutex(NULL,FALSE,NULL);
char tdquit=0;

int main()
{
	LYname s;
	CTime lastTime;

	cout<<"火点监测程序  许方璐于2009年9月23日\n\n"
		     "发现问题或者有好的意见请在网站xufanglu.cn上面留言\n"
			 "-----------------------------------------------------------------\n\n";
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

