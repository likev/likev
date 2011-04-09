//�����Զ�վСʱ���ݼ�¼�����ݿ⽻���Ĳ���
//����޸� 2010 8 6 18:15

#include "aws_hour_database.h"

void deal_all_proc()
{
	std::vector<aws_hour_record> records;

	CTime last_time,curtime;
	bool insert_success=true;

	GetLastReadTime(last_time);
	curtime = last_time + CTimeSpan(0,1,0,0);

	//���ϴ����������ݿ�ʱ���ʼ 
	while(curtime<=CTime::GetCurrentTime())
	{
		//��ȡ��ǰʱ�εĸ�վ��¼
		if(!get_aws_hrcods_from_file(curtime,records))
		{
			//break;//���ٴ�������ʱ��
			curtime += CTimeSpan(0,1,0,0);//��ǰʱ��û���ļ� ������һʱ��
			continue;
		}

		//�����ݲ������ݿ�
		for(std::vector<aws_hour_record>::iterator it=records.begin();
			it != records.end(); it++)
		{
			//������Ч ����ʧ��ʱ
			if(it->is_value_valid("record_time") && !it->insert_into_mysql())
			{
				insert_success = false;
				break;
			}
		}

		if(insert_success) 
		{
			last_time = curtime;
		}
		else
		{
			break;
		}

		curtime += CTimeSpan(0,1,0,0);
	}

	SetLastReadTime(last_time);
}

bool get_aws_hrcods_from_file(const CTime &curtime,	std::vector<aws_hour_record> &records)
{
	using namespace std;

	char path_buf[1024];
	DWORD result1 = GetPrivateProfileString("filepath","path",".\\",path_buf,1000,"./iimsetup.ini");

	char numbers_buf[1024];
	DWORD result2 = GetPrivateProfileString("station","numbers",NULL,numbers_buf,1000,"./iimsetup.ini");

	string numbers_str = numbers_buf;
	istringstream ssin(numbers_str);

	vector<int> station_numbers;
	int number;

	while(ssin>>number)
	{
		station_numbers.push_back(number);
	}

	string contents,content;

	bool findfile = false;
	for(int i=0;i<9;i++)
	{
		string minute = "0"+to_string(i);
		if(filetostr(path_buf+awshrecord_filename(curtime,minute),content))
		{
			contents += content;
			findfile = true;
		}
	}
	if(!findfile) return false;
	
	records.clear();
	for(size_t i=0;i<station_numbers.size();i++)
	{
		records.push_back(aws_hour_record(station_numbers[i],contents));
		cout<<records[i]<<endl;
	}

	return findfile;
}



// ���ö�ȡʱ��
void SetLastReadTime(CTime last_time)
{
	WritePrivateProfileString("lasttime","year",last_time.Format("%Y"),"./iimsetup.ini");
	WritePrivateProfileString("lasttime","month",last_time.Format("%#m"),"./iimsetup.ini");
	WritePrivateProfileString("lasttime","day",last_time.Format("%#d"),"./iimsetup.ini");
	WritePrivateProfileString("lasttime","hour",last_time.Format("%#H"),"./iimsetup.ini");
}

void GetLastReadTime(CTime &last_time)
{
	int year,month,day,hour;
	year = GetPrivateProfileInt("lasttime","year",-1,"./iimsetup.ini");
	month= GetPrivateProfileInt("lasttime","month",-1,"./iimsetup.ini");
	day  = GetPrivateProfileInt("lasttime","day",-1,"./iimsetup.ini");
	hour = GetPrivateProfileInt("lasttime","hour",-1,"./iimsetup.ini");


	if(year<0 || month<0 || day<0 || hour<0)
	{
		last_time = CTime::GetCurrentTime()-CTimeSpan(2,10,0,0);
		SetLastReadTime(last_time);
	}
	else
	{
		last_time = CTime(year,month,day,hour,0,0);
	}
}