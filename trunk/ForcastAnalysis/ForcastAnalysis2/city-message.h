#pragma once

#include <string>
#include <vector>

using std::vector;  using std::string;

//�洢���򱨵���վ��Ԥ������
class city_message
{	
public:
	int stn,fcn,ele; //վ�� ʱ���� Ҫ����
	double lon,lat,h;//���� γ�� �߶�

	//�Ը����ʹ洢���� ����ͳ�Ʒ���
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
