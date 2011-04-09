
#include "comn.h"

#include "getfile.h"
/*
	����޸�ʱ�䣺2010 6 18 11:26 by xufanglu
*/

#include "http-deal.h"

void getfile(void)
{
	using namespace std;

	string station_num;
	vector<string> stations;
	
	bool run=true;
	cout<<"(����վ������ 57071 57074 end�������):  ";
	while(run)
	{
		cin>>station_num;

		if(station_num != "end")
		{
			stations.push_back(station_num);
		}
		else
		{
			run = false;
		}
	}

	CTime begin,end;
	int year,month,day,hour;

	cout<<"���뿪ʼʱ��(��ʽΪyear month day hour):  ";cin>>year>>month>>day>>hour;
	begin = CTime(year,month,day,hour,0,0);
	cout<<"�������ʱ��(��ʽΪyear month day hour):  ";cin>>year>>month>>day>>hour;
	end   = CTime(year,month,day,hour,0,0);

	//��������վ������
	for(vector<string>::iterator it=stations.begin();
		it != stations.end(); it++)
	{
		get_files_by_time(*it,begin,end);
	}
}

//���ص�վ������
void get_files_by_time(std::string station_num, CTime begin,CTime end)
{
	using namespace std;
	string server="172.18.152.6", weburl,
		   url="/timedata.asp?StationNum="+station_num+"&selecttime=";

	while(begin <= end)
	{
		string selecttime = begin.Format("%Y%m%d%H").GetBuffer();
		weburl = url + selecttime;

		//show current select time
		cout<<"\r                                                    ";
		cout<<"\r reading  "<<selecttime;


		//begin download 

		string localfile = "webfiles/"+station_num+"--"+selecttime+".txt";

		DownloadHttpPage(server.c_str(), weburl.c_str(), localfile.c_str());

		begin +=  CTimeSpan(0,1,0,0);
	}
}


