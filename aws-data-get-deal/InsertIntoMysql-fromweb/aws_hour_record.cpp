#include "aws_hour_record.h"

//通过记录字符串初始化函数
bool aws_hour_record::init_from_str(int stn_number, const std::string &record_str)
{
	defult_set();

	station_number = stn_number;
	loss_measure["station_number"] = false;

	std::string stn_number_str; 
	to_string(stn_number,stn_number_str);

	size_t find_begin = record_str.find(stn_number_str);
	if(find_begin == record_str.npos )
	{
		return false;
	}

	size_t find_end = record_str.find("=",find_begin);

	std::string station_record_str = record_str.substr(find_begin,find_end-find_begin);

	std::vector<std::string> vec_str,vec_line_str;
	str_split(station_record_str,"\n",vec_str);

	//对第2条记录分隔
	str_split(vec_str[1]," ",vec_line_str);

	//读取记录时间
	int year=-1,month=-1,day=-1,hour=-1;
	string_to(vec_line_str[0].substr(0,4),year);
	string_to(vec_line_str[0].substr(4,2),month);
	string_to(vec_line_str[0].substr(6,2),day);
	string_to(vec_line_str[0].substr(8,2),hour);

	if(year>=0 && month>=0 && day>=0 && hour>=0)
	{
		record_time = CTime(year,month,day,hour,0,0)+CTimeSpan(0,8,0,0);
		loss_measure["record_time"] = false;
	}

	if(check_if_valid(vec_line_str[16]) )
	{
		read_time_from_str(vec_line_str[16],high_temph_time);
		loss_measure["high_temph_time"] = false;
	}

	if(check_if_valid(vec_line_str[18]) )
	{
		read_time_from_str(vec_line_str[18],low_temph_time);
		loss_measure["low_temph_time"] = false;
	}

	//读取降水
	if(check_if_valid(vec_line_str[14]) )
	{
		string_to(vec_line_str[13],hour_rain);
		hour_rain /= 10;
		loss_measure["hour_rain"] = false;
	}
	
	//读取温度
	if(check_if_valid(vec_line_str[14]) )
	{
		read_temph_from_str(vec_line_str[14],temph);
		loss_measure["temph"] = false;
	}

	if(check_if_valid(vec_line_str[15]))
	{
		read_temph_from_str(vec_line_str[15],high_temph);
		loss_measure["high_temph"] = false;
	}

	if(check_if_valid(vec_line_str[17]))
	{
		read_temph_from_str(vec_line_str[17],low_temph);
		loss_measure["low_temph"] = false;
	}

	if(check_if_valid(vec_line_str[5]) && check_if_valid(vec_line_str[6]) )
	{//最大10分钟风速
		string_to(vec_line_str[5],max_10_wind.direction);
		max_10_wind.size = string_to<int>(vec_line_str[6])/10.0;

		loss_measure["max_10_wind"] = false;
	}

	if(check_if_valid(vec_line_str[7]))
	{//最大10分钟风速出现时间
		read_time_from_str(vec_line_str[7],max_10_wind_time);

		loss_measure["max_10_wind_time"] = false;
	}

	if(check_if_valid(vec_line_str[10]) && check_if_valid(vec_line_str[11]) )
	{//极大风速
		string_to(vec_line_str[10],max_wind.direction);
		max_wind.size = string_to<int>(vec_line_str[11])/10.0;

		loss_measure["max_wind"] = false;
	}

	if(check_if_valid(vec_line_str[12]))
	{//极大风速出现时间
		read_time_from_str(vec_line_str[12],max_wind_time);

		loss_measure["max_wind_time"] = false;
	}

	if(check_if_valid(vec_line_str[24]))
	{
		station_atmos_press = string_to<int>(vec_line_str[24])/10.0;
		loss_measure["station_atmos_press"] = false;
	}
	
	if(check_if_valid(vec_line_str[49]))
	{
		visibility = string_to<int>(vec_line_str[49]);
		loss_measure["visibility"] = false;
	}
	

	//读取小时内每分钟降水字符串
	if(vec_str.size()>2)
	{
		rainstr_minute = vec_str[2];
		loss_measure["rainstr_minute"] = false;
	}


	return true;
}

//通过web文件获取值
std::string read_value(CTime select_time,int station_num,std::string element)
{
	using namespace std;
	string path = "webfiles/";
	string filename = path + to_string(station_num) + select_time.Format("--%Y%m%d%H.txt").GetBuffer();

	string filecontent;
	filetostr(filename,filecontent);

	size_t isfind = filecontent.find(element);

	if(isfind == filecontent.npos)
		return "";

	size_t wordbegin = filecontent.find("center>",isfind) + 7,
		   wordend   = filecontent.find("</td>",wordbegin);

	string value_str = filecontent.substr(wordbegin,wordend-wordbegin);
	//if(!value_str.size())
	//	return 9999;

	//int value=0;
	//string_to(value_str, value);

	return value_str;

}

//通过网站文件读取
bool aws_hour_record::init_from_web(CTime select_time,int stn_number)
{
	using std::string;
	
	record_time = select_time;
	loss_measure["record_time"] = false;

	station_number = stn_number;
	loss_measure["stn_number"] = false;
	
	string value_str;
	
	value_str = read_value(select_time,stn_number,"干球温度");
	if(value_str.size())
	{
		string_to(value_str,temph); 
		temph /= 10;

		if(temph>-30 && temph<50) loss_measure["temph"] = false;
	}

	value_str = read_value(select_time,stn_number,"雨量");
	if(value_str.size())
	{
		string_to(value_str,hour_rain); 
		hour_rain /= 10;
		loss_measure["hour_rain"] = false;
	}

	value_str = read_value(select_time,stn_number,"最高温度");
	if(value_str.size())
	{
		string_to(value_str,high_temph); 
		high_temph /= 10;
		if(high_temph>-30 && high_temph<50) loss_measure["high_temph"] = false;
	}



	value_str = read_value(select_time,stn_number,"最高温度出现时间");
	if(value_str.size())
	{
		value_str.erase(2,1);
		read_time_from_str(value_str,high_temph_time);
		loss_measure["high_temph_time"] = false;
	}

	value_str = read_value(select_time,stn_number,"最低温度");
	if(value_str.size())
	{
		string_to(value_str,low_temph); 
		low_temph /= 10;
		if(low_temph>-30 && low_temph<40) loss_measure["low_temph"] = false;
	}

	value_str = read_value(select_time,stn_number,"最低温度出现时间");
	if(value_str.size())
	{
		value_str.erase(2,1);
		read_time_from_str(value_str,low_temph_time);
		loss_measure["low_temph_time"] = false;
	}
	
	value_str = read_value(select_time,stn_number,"本站气压");
	if(value_str.size())
	{
		string_to(value_str,station_atmos_press); 
		station_atmos_press /= 10;
		if(station_atmos_press>500) loss_measure["station_atmos_press"] = false;
	}

	value_str = read_value(select_time,stn_number,"最大风速");
	if(value_str.size())
	{
		string_to(value_str,max_10_wind.size); 
		max_10_wind.size /= 10;
	}

	value_str = read_value(select_time,stn_number,"最大风速的风向");
	if(value_str.size())
	{
		string_to(value_str,max_10_wind.direction);
		loss_measure["max_10_wind"] = false;
	}

	value_str = read_value(select_time,stn_number,"最大风速出现的时间");
	if(value_str.size())
	{
		value_str.erase(2,1);
		read_time_from_str(value_str,max_10_wind_time);
		loss_measure["max_10_wind_time"] = false;
	}

	value_str = read_value(select_time,stn_number,"极大风速");
	if(value_str.size())
	{
		string_to(value_str,max_wind.size); 
		max_wind.size /= 10;
	}

	value_str = read_value(select_time,stn_number,"极大风速的风向");
	if(value_str.size())
	{
		string_to(value_str,max_wind.direction);
		loss_measure["max_wind"] = false;
	}
	
	value_str = read_value(select_time,stn_number,"极大风速出现的时间");
	if(value_str.size())
	{
		value_str.erase(2,1);
		read_time_from_str(value_str,max_wind_time);
		loss_measure["max_wind_time"] = false;
	}

	return true;
}

std::ostream & operator <<(std::ostream & out,const aws_hour_record& record)
{
	using namespace std;
	out<<"    station: "<<record.station_number<<endl;
	out<<"record time: "<<record.record_time.Format("%Y-%m-%d %H:%M:%S")<<endl;
	out<<"       rain: "<<record.hour_rain<<endl;
	out<<"      temph: "<<record.temph<<endl;
	out<<"  low_temph: "<<record.low_temph<<"   time:"<<record.low_temph_time.Format("%H:%M")<<endl;
	out<<" high_temph: "<<record.high_temph<<"   time:"<<record.high_temph_time.Format("%H:%M")<<endl;
	out<<"max_10_wind: "<<"size "<<record.max_10_wind.size<<"   direction "<<record.max_10_wind.direction<<"  time "<<record.max_10_wind_time.Format("%H:%M")<<endl;
	out<<"   max_wind: "<<"size "<<record.max_wind.size<<"   direction "<<record.max_wind.direction<<"  time "<<record.max_wind_time.Format("%H:%M")<<endl;
	out<<"  station_P: "<<record.station_atmos_press<<endl;
	return out;
}

std::string awshrecord_filename(CTime curtime,std::string minute)
{
	curtime -= CTimeSpan(0,8,0,0);
	std::string name = "Z_SURF_C_BEZZ_"+curtime.Format("%Y%m%d%H")+minute.c_str()+"20_O_AWS_FTM.TXT";

	return name;
}

std::string aws_hour_record::format_time(const CTime &time, bool is_valid)
{
	if(is_valid)
	{
		return std::string(time.Format(" '%Y-%m-%d %H:%M:%S' , "));
	}
	else
	{
		return "NULL, ";
	}
}



//获取插入数据的SQL语句
std::string aws_hour_record::get_sql_query(bool is_replace)
{
	//insert into perhour57065 (record_time,temph,high_temph,low_temph,high_temph_time,low_temph_time,hourrain,rainstr_perminute) 
	//values('2010-3-5 2:00:00',10.3,11,10,' ', ' ', 10,'00000')

	std::string SELECT_QUERY = "INSERT";
	if(is_replace) SELECT_QUERY = "REPLACE";

	SELECT_QUERY += " INTO perhour"+to_string(station_number)
		+" (record_time,temph,high_temph,low_temph,high_temph_time,low_temph_time,hourrain,rainstr_perminute,"
		  " max_10_wind_value, max_10_wind_direction,max_10_wind_time,"
		  " max_wind_value, max_wind_direction,max_wind_time,"
		  " station_atmos_press,visibility )\n"
		" VALUES ( "

		+ format_time(record_time,is_value_valid("record_time"))
		+ format_value(temph, is_value_valid("temph"))
		+ format_value(high_temph, is_value_valid("high_temph"))
		+ format_value(low_temph, is_value_valid("low_temph"))
		+ format_time(high_temph_time,is_value_valid("high_temph_time"))
		+ format_time(low_temph_time, is_value_valid("low_temph_time"))
		+ format_value(hour_rain, is_value_valid("hour_rain"))
		+ "'" + rainstr_minute + "', "
		+ format_value(max_10_wind.size,is_value_valid("max_10_wind"))
		+ format_value(max_10_wind.direction,is_value_valid("max_10_wind"))
		+ format_time(max_10_wind_time,is_value_valid("max_10_wind_time"))
		+ format_value(max_wind.size,is_value_valid("max_wind"))
		+ format_value(max_wind.direction,is_value_valid("max_wind"))
		+ format_time(max_wind_time,is_value_valid("max_wind_time"))
		+ format_value(station_atmos_press,is_value_valid("station_atmos_press"))
		+ format_value(visibility,is_value_valid("visibility"))
		+" )";

	std::string::size_type pos=SELECT_QUERY.rfind(",");
	SELECT_QUERY.erase(pos,1);//删除最后一个逗号

	return SELECT_QUERY;
}

//根据小时记录结构插入相应的表
bool aws_hour_record::insert_into_mysql()
{
	using namespace std;
	bool returnvalue=true;

	char hostname[100],inserttype[100];
	GetPrivateProfileString("type","hostname","localhost",hostname,100,"./iimsetup.ini");
	GetPrivateProfileString("type","inserttype","insert",inserttype,100,"./iimsetup.ini");

	MYSQL mysql,*sock;    //定义数据库连接的句柄，它被用于几乎所有的MySQL函数

	mysql_init(&mysql);
	sock = mysql_real_connect(&mysql,hostname,"root","271828","meteor_records",0,NULL,0);

	if(!sock) 
	{
		cout<<mysql_error(&mysql)<<endl;
		return false;
	}

	bool is_replace = (inserttype == string("replace"));
	string SELECT_QUERY=get_sql_query(is_replace);

	if(mysql_query(sock,SELECT_QUERY.c_str()))
	{
		unsigned error_code = mysql_errno(&mysql);

		if(error_code != 1062)//已经存在
		{
			cout<<mysql_error(&mysql)<<endl;
			returnvalue = false;
		}
	}

	mysql_close(sock);

	return returnvalue;
}