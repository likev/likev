#pragma once

#include <string>
#include <vector>

using std::vector;  using std::string;

//存储城镇报单个站的预报数据
class city_message
{	
public:
	int stn,fcn,ele; //站号 时次数 要素数
	double lon,lat,h;//经度 纬度 高度

	//以浮点型存储数据 便于统计分析
	vector<vector<double> > data;

	city_message()
	{
		stn=99999;
		fcn=ele=0;
		lon=lat=h=0;
	}
	city_message(string snum, const string& sfile)
	{
		init(snum,sfile);
	}
	bool init(string snum, const string& sfile);
};


class coordnt
{
public:
	double lon,lat;

	coordnt()
	{
		lon=lat=0;
	}

	coordnt(double a,double b)
	{
		lon = a;
		lat = b;
	}
};
