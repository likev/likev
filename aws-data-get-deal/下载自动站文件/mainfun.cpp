/*
	最后修改时间：2010 6 18 11:05 by xufanglu
*/

#include <comn.h>
#include "mainfun.h"
#include "getfile.h"
#include "string-trans.h"

int main(int argc, char* argv[])
{
	using namespace std;
	
	vector<string> command;

	for(int i=1;i<argc;i++)
	{
		command.push_back(argv[i]);
	}

	if(command.size()>0)
	{
		if(command[0] == "-h" || command[0]== "/?")
		{
			print_help();
			return 0;
		}

		bool findh=false, finds=false,findb=false,finde=false;
		string station="57071";

		vector<string>::iterator pos;
		pos=find(command.begin(),command.end(),"-s");

		if(pos != command.end())
		{
			finds=true;
			station = *(pos+1);
		}

		CTime tend=CTime::GetCurrentTime(), tbegin=tend - CTimeSpan(1,0,0,0);


		pos=find(command.begin(),command.end(),"-b");

		if(pos != command.end())
		{
			findb=true;
			tbegin =  GetTime(pos);
		}

		pos=find(command.begin(),command.end(),"-e");

		if(pos != command.end())
		{
			finde=true;
			tend =  GetTime(pos);
		}

		if(finds || findb || finde)
		{
			get_files_by_time(station,tbegin,tend);
			return 0;
		}

	}

	while(true)
	{
		getfile();
	}
	return 0;
}


void print_help()
{
	using namespace std;

	cout<<"命令行参数：\n"
		  "-h or /? //help 输出帮助信息\n"
		  "-s [station] //输入区站号,默认为57071\n"
		  "-b [year] [month] [day] [hour]  //输入开始(begin)时间\n"
		  "-e [year] [month] [day] [hour]  //输入结束(end)时间\n";
}

CTime GetTime(std::vector<std::string>::iterator pos)
{
	int year,month=1,day=1,hour=0;

	year = string_to(*(pos+1),year);
	month= string_to(*(pos+2),month);
	day  = string_to(*(pos+3),day);
	hour = string_to(*(pos+4),hour);

	return CTime(year,month,day,hour,0,0);
}