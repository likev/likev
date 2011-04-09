
#include "comn.h"
#include "setinfo.h"

int whent(void);

using std::string;
using std::vector;

void begin_head(string &fhead)
{

	using namespace std;
	stringstream stream;

	CTime ct1=CTime::GetCurrentTime();//��ǰ����

	stream<<"	                      ��   ��   Ԥ   ��\r\n"
		<<"                                     "<<ct1.Format("%Y��%m��%d��%Hʱ����").GetBuffer()
	<<"\r\n-------------------------------------------------------------------\r\n"
		"-------------------------------------------------------------------\r\n"
		"�������Ʒ���: \r\n"                                                      
		"-------------------------------------------------------------------\r\n"
		"  24Сʱ����: \r\n"                                                        
		"    �������: ƫ ��2-3��\r\n"                                                        
		"        �¶�: ����¶ȣ�       ����¶ȣ�\r\n"                                                        
		"-------------------------------------------------------------------\r\n"
		"  48Сʱ����:\r\n"                                                        
		"-------------------------------------------------------------------\r\n"
		"    ɭ�ֻ���: 2\r\n"                                                          
		"-------------------------------------------------------------------\r\n\r\n"

		" վ  ��       0-12Сʱ����   12-24Сʱ����    ����¶�      ����¶�\r\n"           
		"-------------------------------------------------------------------\r\n"
		"-------------------------------------------------------------------\r\n";

	fhead = stream.str();
}

//���24Сʱ����״�����������¶�
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

	CTime ct1=CTime::GetCurrentTime();//��ǰ����

	stream<<"	                      ��   ��   Ԥ   ��\r\n"
		"                                     "<<ct1.Format("%Y��%m��%d��%Hʱ����").GetBuffer()
	<<"\r\n-------------------------------------------------------------------\r\n"
		"  24Сʱ����: \r\n"                                                        
		"    �������: ƫ ��2-3��\r\n"                                                        
		"        �¶�: ����¶ȣ�   ����¶ȣ�\r\n"                                                        
		"-------------------------------------------------------------------\r\n";

	return stream.str();
}

//������д���ļ�
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
			dealf2(stream,all_weather_str,all_temph_value);//ǰ24Сʱ
			stream<<"\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"
				" վ  ��       24-36Сʱ����   36-48Сʱ����    ����¶�      ����¶�\r\n"           
				"-------------------------------------------------------------------\r\n"
				"-------------------------------------------------------------------\r\n";
			dealf2(stream,all_weather_str,all_temph_value,2);//��24Сʱ
			break;
		}
	default:break;
	}

	return stream.str();
}