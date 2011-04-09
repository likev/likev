//存储自动站文件
//最后修改 2011年1月10日

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
	//风矢量类
	struct wind_vector
	{
		int direction;
		double size;

		wind_vector()
			:direction(-1),size(-1)
		{}
	};

	//默认无参构造函数
	aws_hour_record()
	{
		defult_set();
	}
	//通过记录字符串初始化
	aws_hour_record(int stn_number, const std::string &record_str)
	{
		init_from_str(stn_number, record_str);
	}

	//通过记录字符串初始化函数
	bool init_from_str(int stn_number, const std::string &record_str);

	//通过网站文件读取
	bool init_from_web(CTime select_time,int stn_number);

	bool is_value_valid(std::string value_str)
	{
		return loss_measure.count(value_str) && !loss_measure[value_str];
	}

	//友元函数用于输出记录
	friend std::ostream & operator <<(std::ostream & out,const aws_hour_record& record);

	//根据小时记录结构插入相应的表
	bool insert_into_mysql();

private:
	int station_number, //区站号
		visibility; // 当前时间能见度

	double temph,//当前时刻温度
		high_temph, //一小时内最高温度
		low_temph, //一小时内最低温度
		hour_rain, //小时降雨量
		station_atmos_press;//当前时刻本站气压

	wind_vector max_10_wind,//小时内10分钟平均风速的最大值
		max_wind; //小时内极大风速

	std::map<std::string,bool> loss_measure;

	CTime record_time, //观测时间
		high_temph_time, //小时内高温出现时间
		low_temph_time, //小时内低温出现时间
		max_10_wind_time,//小时内10分钟平均风速的最大值出现时间
		max_wind_time; //小时内极大风速出现时间

	std::string rainstr_minute;

private:

	//默认设置
	void defult_set()
	{
		station_number = 99999;
		temph=high_temph=low_temph=hour_rain=-9999;
	}

	//检查是否缺测
	bool check_if_valid(const std::string &str)const
	{
		if(str.find('/') != str.npos)
		{
			return false;
		}
		return true;
	}

	//读取温度
	double & read_temph_from_str(const std::string &str,double &value)
	{
		string_to(str.substr(1,3),value); 
		if(str[0] != '0')
			value = -value;
		return value /= 10;
	}
	//读取时间
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

	//处理数据库插入
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