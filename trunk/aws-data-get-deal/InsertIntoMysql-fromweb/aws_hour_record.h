//�洢�Զ�վ�ļ�
//����޸� 2011��1��10��

#ifndef READ_AWS_FILE
#define READ_AWS_FILE

#include <comn.h>
#include <string-trans.h>

#include <mysql.h>

#ifdef _DEBUG
#pragma comment(lib,"D:/Program Files/MySQL/MySQL Server 5.1/lib/debug/libmysql.lib")
#else
#pragma comment(lib,"D:/Program Files/MySQL/MySQL Server 5.1/lib/opt/mysqlclient.lib")
#endif

class aws_hour_record
{
public:
	//��ʸ����
	struct wind_vector
	{
		int direction;
		double size;

		wind_vector()
			:direction(-1),size(-1)
		{}
	};

	//Ĭ���޲ι��캯��
	aws_hour_record()
	{
		defult_set();
	}
	//ͨ����¼�ַ�����ʼ��
	aws_hour_record(int stn_number, const std::string &record_str)
	{
		init_from_str(stn_number, record_str);
	}

	//ͨ����¼�ַ�����ʼ������
	bool init_from_str(int stn_number, const std::string &record_str);

	//ͨ����վ�ļ���ȡ
	bool init_from_web(CTime select_time,int stn_number);

	bool is_value_valid(std::string value_str)
	{
		return loss_measure.count(value_str) && !loss_measure[value_str];
	}

	//��Ԫ�������������¼
	friend std::ostream & operator <<(std::ostream & out,const aws_hour_record& record);

	//����Сʱ��¼�ṹ������Ӧ�ı�
	bool insert_into_mysql();

private:
	int station_number, //��վ��
		visibility; // ��ǰʱ���ܼ���

	double temph,//��ǰʱ���¶�
		high_temph, //һСʱ������¶�
		low_temph, //һСʱ������¶�
		hour_rain, //Сʱ������
		station_atmos_press;//��ǰʱ�̱�վ��ѹ

	wind_vector max_10_wind,//Сʱ��10����ƽ�����ٵ����ֵ
		max_wind; //Сʱ�ڼ������

	std::map<std::string,bool> loss_measure;

	CTime record_time, //�۲�ʱ��
		high_temph_time, //Сʱ�ڸ��³���ʱ��
		low_temph_time, //Сʱ�ڵ��³���ʱ��
		max_10_wind_time,//Сʱ��10����ƽ�����ٵ����ֵ����ʱ��
		max_wind_time; //Сʱ�ڼ�����ٳ���ʱ��

	std::string rainstr_minute;

private:

	//Ĭ������
	void defult_set()
	{
		station_number = 99999;
		temph=high_temph=low_temph=hour_rain=-9999;
	}

	//����Ƿ�ȱ��
	bool check_if_valid(const std::string &str)const
	{
		if(str.find('/') != str.npos)
		{
			return false;
		}
		return true;
	}

	//��ȡ�¶�
	double & read_temph_from_str(const std::string &str,double &value)
	{
		string_to(str.substr(1,3),value); 
		if(str[0] != '0')
			value = -value;
		return value /= 10;
	}
	//��ȡʱ��
	CTime & read_time_from_str(const std::string &str, CTime & time)
	{
		int hourspan=0,minute=0;

		string_to(str.substr(2,2),minute);

		//int current_UTC_hour = (record_time-CTimeSpan(0,8,0,0)).GetHour(),
		//	record_UTC_hour = string_to<int>(str.substr(0,2));
		
		if(minute)
		{
			hourspan = -1;
		}

		time = record_time + CTimeSpan(0,hourspan,minute,0);

		return time;
	}

	//�������ݿ����
	template<typename T>
	std::string format_value(T value, bool is_valid)
	{
		if(is_valid)
		{
			return to_string(value)+", ";
		}
		else
		{
			return "NULL, ";
		}
	}

	std::string format_time(const CTime &time, bool is_loss_measure);

	std::string get_sql_query(bool is_replace=false);
};

std::string awshrecord_filename(CTime curtime,std::string minute="05");

#endif /* read_aws_file */