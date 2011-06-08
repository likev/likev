//���Զ�վ���ݿ��ж�ȡ��¼

#ifndef READ_FROM_MYSQL
#define READ_FROM_MYSQL

#include <comn.h>
#include <string-trans.h>
#include <mysql.h>

#ifdef _DEBUG
#pragma comment(lib,"D:/Program Files/MySQL/MySQL Server 5.1/lib/debug/libmysql.lib")
#else
#pragma comment(lib,"D:/Program Files/MySQL/MySQL Server 5.1/lib/opt/mysqlclient.lib")
#endif

//�Զ�վ���ݿ��ѯ�����ռ�
namespace awssql
{
	//�����ѯ����
	enum QUERY_ELEMENT{TEMPH,HIGH_TEMPH,LOW_TEMPH,HOURRAIN,RAINSTR_PERMINUTE,MAX_10_WIND,MAX_WIND,STATION_ATMOS_PRESS,VISIBILITY};

	//��ʸ����
	struct wind_vector
	{
		int direction;
		double size;

		wind_vector()
			:direction(-1),size(-1)
		{}

		bool operator < (const wind_vector& right)const
		{
			return size < right.size;
		}
		bool operator > (const wind_vector& right)const
		{
			return size > right.size;
		}
		bool operator == (const wind_vector& right)const
		{
			return size == right.size;
		}
		bool operator != (const wind_vector& right)const
		{
			return size != right.size;
		}

		std::string to_string()const
		{
			return ::to_string(size)+"   "+::to_string(direction);
		}
	};

	std::string to_string(const awssql::wind_vector & wind);

	CTime comb_day_time(CTime daytime,CTime time);
	CTime NearTime(CTime cur, int hour, bool before=true);

	/*��ȡָ��ʱ��ε� �¶�/����¶�/��ˮ��
	records Ϊʱ�����ֵ�Ĺ������� �洢��ѯ���
	*/
	template <typename T>
	int get_records(int station_number,int type, std::map<CTime,T> &records, CTime begin,CTime end)
	{
		using namespace std;
		//select record_time, high_temph ,high_temph_time from perhour57065 (record_time,temph,high_temph,low_temph,high_temph_time,low_temph_time,hourrain,rainstr_perminute) 
		//where record_time between (begin,end)
		string str;
		switch(type)
		{
		case awssql::TEMPH:
			str = "temph";break;
		case awssql::HIGH_TEMPH:
			str = "high_temph,high_temph_time";break;
		case awssql::LOW_TEMPH:
			str = "low_temph,low_temph_time";break;
		case awssql::HOURRAIN:
			str = "hourrain";break;
		case awssql::RAINSTR_PERMINUTE:
			str = "rainstr_perminute";break;
		case awssql::STATION_ATMOS_PRESS:
			str = "station_atmos_press";break;
		case awssql::VISIBILITY:
			str = "visibility";break;
		default:break;
		}

		std::string SELECT_QUERY = "SELECT record_time,"+str+" from perhour"+::to_string(station_number)
			+" WHERE record_time BETWEEN "+(begin.Format(" '%Y-%m-%d %H:00:00' ")+end.Format(" and '%Y-%m-%d %H:00:00' ;")).GetBuffer();

		MYSQL mysql,*sock;    //�������ݿ����ӵľ�����������ڼ������е�MySQL����
		MYSQL_RES *res;       //��ѯ��������ṹ����
		//MYSQL_FIELD *fd ;     //�����ֶ���Ϣ�Ľṹ
		MYSQL_ROW row ;       //���һ�в�ѯ������ַ�������

		mysql_init(&mysql);
		sock = mysql_real_connect(&mysql,"172.18.172.200","root","271828","meteor_records",0,NULL,0);

		if(!sock) 
		{
			cout<<mysql_error(&mysql)<<endl;
			return -1;
		}

		mysql_query(sock,SELECT_QUERY.c_str());
		res=mysql_store_result(sock);

		int num_cols =mysql_num_fields(res);
		int num_rows = mysql_num_rows(res);

		records.clear();//�������

		while(row = mysql_fetch_row(res))
		{
			bool isvalid=true;
			//�жϴ��������Ƿ���Ч
			for(int i=0;i<num_cols;i++)
			{
				if(!row[i]) 
				{
					isvalid=false;
					break;
				}
			}

			if(!isvalid) continue;

			CTime record_time, ele_time;
			T value;

			record_time = CStringToCTime(row[0],0);
			string_to(row[1],value);

			if(num_cols == 3)
			{
				ele_time = CStringToCTime(row[2],1);
				record_time = comb_day_time(record_time,ele_time);
			}

			records[record_time] = value;
		}

		mysql_free_result(res);
		mysql_close(sock);

		return num_rows;
	}

	/*
	ģ�庯������ ����ڵ���ʱ�εĲ�ѯ����������ʱ��εĲ�ѯ����
	*/
	template <typename T>
	int get_records(int station_number, int type, std::map<CTime,T> &records,CTime begin)
	{
		return get_records(station_number,type,records,begin,begin);
	}

	//��ȡ��ʸ������
	int get_records(int station_number, int type, std::map<CTime,wind_vector> &records, CTime begin,CTime end);

	//��ȡ��ʸ������
	int get_records(int station_number, int type, std::map<CTime,wind_vector> &records, CTime begin);

} //namespace awssql end

#endif /*read_from_mysql*/