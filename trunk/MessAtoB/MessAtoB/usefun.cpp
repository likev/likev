//程序中用到的功能函数定义
#include "stdafx.h"
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

std::string & filetostr(std::string file,std::string & str)
{
	std::ifstream fin(file.c_str());
	if(!fin.is_open())
	{
		return str;
	}

	str="";
	std::string temp;
	while(std::getline(fin,temp))
	{
		str += temp+"\r\n";
	}

	fin.close();
	return str;
}

bool strtofile(std::string file,const std::string & str)
{
	std::ofstream fout(file.c_str());
	if(!fout.is_open())
	{
		return false;
	}

	fout<<str;

	fout.close();
	return true;
}

std::string dtos(double a, int l)
{
	using namespace std;

	string m;
	stringstream stream;

	stream<<fixed<<setprecision(l)<<a;

	stream>>m;

	return m;
}

int whent(void)
{
	CTime ct1=CTime::GetCurrentTime();//当前日期
	int cth = ct1.GetHour();

	if(cth<4)
	{
		return 0;//不需要县区预报
	}
	else if(cth<9)
	{
		return 1;//早间预报
	}
	else if(cth<14)
	{
		return 2;//12121预报
	}
	else
	{
		return 3;//下午预报
	}
}