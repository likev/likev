#include "stdafx.h"

#include <vector>
#include <sstream>
#include <iomanip>

#include "sglf.h"
#include "setinfo.h"



int whent(void);

void dealfhead(string &fhead)
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
		"    �������: \r\n"                                                        
		"        �¶�: \r\n"                                                        
		"-------------------------------------------------------------------\r\n"
		"  48Сʱ����:\r\n"                                                        
		"-------------------------------------------------------------------\r\n"
		"    ɭ�ֻ���:\r\n"                                                          
		"-------------------------------------------------------------------\r\n\r\n"

		" վ  ��       0-12Сʱ����   12-24Сʱ����    ����¶�      ����¶�\r\n"           
		"-------------------------------------------------------------------\r\n"
		"-------------------------------------------------------------------\r\n";

	fhead = stream.str();
}

//���24Сʱ����״�����������¶�
void dealf2(std::stringstream & fout, const vector<vector<string>  > &weth,
	             const vector<vector<double>  > &teph,int n=0)
{
	using namespace std;
		StnName names;

		for(size_t i=0;i<11;i++)
		{
			fout<<left<<setw(14)<<names.nm[i]<<setw(15)<<weth[0+n][i]<<setw(17)<<weth[1+n][i]
			<<setw(16)<<teph[0+n][i]<<setw(15)<<teph[1+n][i];
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
		"�������Ʒ���: \r\n"                                                      
		"-------------------------------------------------------------------\r\n"
		"  24Сʱ����: \r\n"                                                        
		"    �������: \r\n"                                                        
		"        �¶�: \r\n"                                                        
		"-------------------------------------------------------------------\r\n";

	return stream.str();
}
//�������ݲ�����
bool dealdata(vector<vector<string>  > &weth,
	             vector<vector<double>  > &teph)
{
	using namespace std;
	char * s[11]={"57073", "57073","57071","57076","57074",
		                "57078","57070","57065","57066","57162","57077"};

	vector<sglf> a(11);
	string str;SetInfo c;

	if(filetostr("b.txt",str)=="")
		return false;

	string m[4];double t[4];
	for(int i=0;i<11;i++)
	{
		if(!a[i].init(*(s+i),str))
		{
			return false;
		}

		m[0] = dtos(a[i].f[0][19]);m[1] = dtos(a[i].f[1][19]);
		m[2] = dtos(a[i].f[2][19]);m[3] = dtos(a[i].f[3][19]);
		t[0] = a[i].f[1][11];t[1] =  a[i].f[1][12];
		t[2] =  a[i].f[3][11];t[3] =  a[i].f[3][12];

		for(int j=0;j<4;j++)
		{
			weth[j][i] = c.weth[m[j] ];
			teph[j][i] = t[j];
		}
	}
	return true;
}

//������д���ļ�
std::string dealfile(const vector<vector<string>  > &weth,
	             const vector<vector<double>  > &teph,const int wht)
{

	using namespace std;
	stringstream stream;
	switch(wht)
	{
	case 0:
		break;
	case 1:
		dealf2(stream,weth,teph);
		break;
	case 2:
		strtofile("f.txt",dealf121());
		break;

	case 3:
		{
			dealf2(stream,weth,teph);//ǰ24Сʱ
			stream<<"\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"
				" վ  ��       24-36Сʱ����   36-48Сʱ����    ����¶�      ����¶�\r\n"           
				"-------------------------------------------------------------------\r\n"
				"-------------------------------------------------------------------\r\n";
			dealf2(stream,weth,teph,2);//��24Сʱ
			break;
		}
	default:break;
	}

	return stream.str();
}