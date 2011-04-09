//从自动站数据库中读取记录

#include "read_aws_from_mysql.h"

//自动站数据库查询命名空间
namespace awssql
{
	
	//风速转化为字符串
	std::string to_string(const awssql::wind_vector & wind)
	{
		return wind.to_string();
	}

	CTime comb_day_time(CTime daytime,CTime time)
	{
		int hourspan=0;

		if(daytime.GetHour() != time.GetHour())
			hourspan = -1;

		daytime += CTimeSpan(0,hourspan,time.GetMinute(),time.GetSecond());

		return daytime;
	}

	CTime NearTime(CTime cur, int hour, bool before)
	{
		CTime relate = CTime(cur.GetYear(),cur.GetMonth(),cur.GetDay(),hour,0,0);
		if(cur.GetHour() >= hour)
		{
			if(before)
			{
				return relate;
			}
			else
			{
				return relate+CTimeSpan(1,0,0,0);
			}
		}
		else
		{
			if(before)
			{
				return relate-CTimeSpan(1,0,0,0);
			}
			else
			{
				return relate;
			}
		}
	}


	//读取风矢量序列
	int get_records(int station_number, int type, std::map<CTime,wind_vector> &records, CTime begin,CTime end)
	{
		using namespace std;
		//select record_time, high_temph ,high_temph_time from perhour57065 (record_time,temph,high_temph,low_temph,high_temph_time,low_temph_time,hourrain,rainstr_perminute) 
		//where record_time between (begin,end)
		string str;
		switch(type)
		{
		case awssql::MAX_10_WIND:
			str = "max_10_wind_time,max_10_wind_value,max_10_wind_direction";break;
		case awssql::MAX_WIND:
			str = "max_wind_time,max_wind_value,max_wind_direction";break;
		default:break;
		}

		std::string SELECT_QUERY = "SELECT record_time,"+str+" from perhour"+::to_string(station_number)
			+" WHERE record_time BETWEEN "+(begin.Format(" '%Y-%m-%d %H:00:00' ")+end.Format(" and '%Y-%m-%d %H:00:00' ;")).GetBuffer();

		MYSQL mysql,*sock;    //定义数据库连接的句柄，它被用于几乎所有的MySQL函数
		MYSQL_RES *res;       //查询结果集，结构类型
		//MYSQL_FIELD *fd ;     //包含字段信息的结构
		MYSQL_ROW row ;       //存放一行查询结果的字符串数组

		mysql_init(&mysql);
		sock = mysql_real_connect(&mysql,"172.18.172.200","root","271828","meteor_records",0,NULL,0);

		if(!sock) 
		{
			cout<<mysql_error(&mysql)<<endl;
			return -1;
		}

		mysql_query(sock,SELECT_QUERY.c_str());
		res=mysql_store_result(sock);

		unsigned num_cols =mysql_num_fields(res);
		int num_rows = mysql_num_rows(res);

		records.clear();//清空数据

		while(row = mysql_fetch_row(res))
		{
			bool isvalid=true;
			//判断此行数据是否有效
			for(unsigned i=0;i<num_cols;i++)
			{
				if(!row[i]) 
				{
					isvalid=false;
					break;
				}
			}

			if(!isvalid) continue;

			CTime record_time, ele_time;
			wind_vector value;

			record_time = CStringToCTime(row[0],0);
			ele_time = CStringToCTime(row[1],1);
			record_time = comb_day_time(record_time,ele_time);

			string_to(row[2],value.size);
			string_to(row[3],value.direction);

			records[record_time] = value;
		}

		mysql_free_result(res);
		mysql_close(sock);

		return num_rows;
	}

	//读取风矢量序列
	int get_records(int station_number, int type, std::map<CTime,wind_vector> &records, CTime begin)
	{
		return get_records(station_number,type,records,begin,begin);
	}
} //namespace awssql end