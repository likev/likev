// PlanClock.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

void plan_run(CTime time,std::string command_line,int minutes_span=5)
{
	using std::cout;
	using std::endl; 

	cout<<"\n\n";
	while(true)
	{
		if(CTime::GetCurrentTime() > time)
		{
			PROCESS_INFORMATION proif;
			STARTUPINFO stif = {sizeof(stif)};

			BOOL res = ::CreateProcess(NULL,LPSTR(command_line.c_str()),NULL,NULL,FALSE,0,NULL,NULL,&stif,&proif);		
		
			Sleep(minutes_span*60*1000);
		}
		
		cout<<"\r                                      \r";
		cout<<CTime::GetCurrentTime().Format("��ǰʱ�䣺%H:%M:%S");
		Sleep(1000);
	}
}

void plan_time_set(CTime &time)
{
	using std::cout;
	using std::cin;
	using std::endl;

	int year=0,month=0,day=0,hour=0,minute=0;
	
	cout<<"��������ʱ��(�� 3 15   7 0): ";

	cin>>month>>day>>hour>>minute;

	time = CTime(2010,month,day,hour,minute,0);
	cout<<"�趨��ʱ��Ϊ��"<<time.Format("%Y��%m��%d�� %Hʱ%M��");

}

int _tmain(int argc, _TCHAR* argv[])
{
	std::string cmd_line = "D:\\Program Files\\TTPlayer\\TTPlayer.exe 'E:\\Musics\\�ֿ��� - ����.mp3'";

	CTime plan_time;

	plan_time_set(plan_time);

	plan_run(plan_time,cmd_line,5);

	return 0;
}

