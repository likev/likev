/*
	����޸�ʱ�䣺2010 6 18 10:52 by xufanglu
*/

#include "aws_hour_database.h"


//��һ��վ��������¼�������ݿ�
void insert_one_station(int station_num, CTime begin, CTime end)
{
	// [begin,end]
	while(begin <= end)
	{
		aws_hour_record ahr;
		ahr.init_from_web(begin,station_num);
		std::cout<<ahr<<std::endl;

		//�������ݿ�
		ahr.insert_into_mysql();

		std::string inserttime = begin.Format("%Y-%m-%d %H");

		//show current select time
		std::cout<<"\r                                                    ";
		std::cout<<"\r have insert  "<<inserttime;

		begin += CTimeSpan(0,1,0,0);
	}
}


int main()
{
	using namespace std;

	//deal_all_proc();

	char * ss[]={"57065","57066","57070","57071","57074","57076","57077","57078","57162"};
	vector<string> stations(ss,ss+9);

	CTime last_time, begin,end;

	bool insert_success=true;

	GetLastReadTime(last_time);

	begin = last_time + CTimeSpan(0,1,0,0);
	end   = CTime::GetCurrentTime();

	int station_num;
	//��������վ������
	for(vector<string>::iterator it=stations.begin();
		it != stations.end(); it++)
	{
		string_to(*it, station_num); 
		insert_one_station(station_num, begin, end);
	}

	SetLastReadTime(end);

	return 0;
}
