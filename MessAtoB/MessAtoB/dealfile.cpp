
#include "comn.h"
#include "setinfo.h"

int whent(void);

using std::string;
using std::vector;

void begin_head(string &fhead)
{

	using namespace std;
	stringstream stream;

	CTime ct1=CTime::GetCurrentTime();//当前日期

	stream<<"	                      县   区   预   报\r\n"
		<<"                                     "<<ct1.Format("%Y年%m月%d日%H时制作").GetBuffer()
	<<"\r\n-------------------------------------------------------------------\r\n"
		"-------------------------------------------------------------------\r\n"
		"天气形势分析: \r\n"                                                      
		"-------------------------------------------------------------------\r\n"
		"  24小时天气: \r\n"                                                        
		"    风向风速: 偏 风2-3级\r\n"                                                        
		"        温度: 最高温度：       最低温度：\r\n"                                                        
		"-------------------------------------------------------------------\r\n"
		"  48小时天气:\r\n"                                                        
		"-------------------------------------------------------------------\r\n"
		"    森林火险: 2\r\n"                                                          
		"-------------------------------------------------------------------\r\n\r\n"

		" 站  点       0-12小时天气   12-24小时天气    最高温度      最低温度\r\n"           
		"-------------------------------------------------------------------\r\n"
		"-------------------------------------------------------------------\r\n";

	fhead = stream.str();
}

//输出24小时天气状况，最高最低温度
void dealf2(std::stringstream & fout, const vector<vector<string>  > &all_weather_str,
	             const vector<vector<double>  > &all_temph_value,int n=0)
{
	using namespace std;
		StnName names;

		for(size_t i=0;i<11;i++)
		{
			fout<<left<<setw(14)<<names.nm[i]<<setw(15)<<all_weather_str[0+n][i]<<setw(17)<<all_weather_str[1+n][i]
			<<setw(16)<<all_temph_value[0+n][i]<<setw(15)<<all_temph_value[1+n][i];
			fout<<"\r\n-------------------------------------------------------------------\r\n";
		}
}

std::string dealf121()
{
	std::stringstream stream;

	CTime ct1=CTime::GetCurrentTime();//当前日期

	stream<<"	                      县   区   预   报\r\n"
		"                                     "<<ct1.Format("%Y年%m月%d日%H时制作").GetBuffer()
	<<"\r\n-------------------------------------------------------------------\r\n"
		"  24小时天气: \r\n"                                                        
		"    风向风速: 偏 风2-3级\r\n"                                                        
		"        温度: 最高温度：   最低温度：\r\n"                                                        
		"-------------------------------------------------------------------\r\n";

	return stream.str();
}

//将数据写入文件
std::string dealfile(const vector<vector<string>  > &all_weather_str,
	             const vector<vector<double>  > &all_temph_value,const int forcast_type)
{

	using namespace std;
	stringstream stream;
	switch(forcast_type)
	{
	case 0:
		break;
	case 1:
		dealf2(stream,all_weather_str,all_temph_value);
		break;
	case 2:
		strtofile("f.txt",dealf121());
		break;

	case 3:
		{
			dealf2(stream,all_weather_str,all_temph_value);//前24小时
			stream<<"\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"
				" 站  点       24-36小时天气   36-48小时天气    最高温度      最低温度\r\n"           
				"-------------------------------------------------------------------\r\n"
				"-------------------------------------------------------------------\r\n";
			dealf2(stream,all_weather_str,all_temph_value,2);//后24小时
			break;
		}
	default:break;
	}

	return stream.str();
}