#include "city_forecast.h"

bool israin(std::string scode)
{
	if( (scode>"02" && scode<"13")

		||(scode>"20" && scode<"25")
		||(scode == "19") 
		||(scode > "30")  )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool israin(double scode)
{
	if( (scode>2 && scode<13)

		||(scode>20 && scode<25)
		|| beql(scode,19.0) 
		||(scode > 30)  )
	{
		return true;
	}
	else
	{
		return false;
	}
}

city_fst & read_city_fst(const std::string & sline, city_fst & cf)
{
	using namespace std;
	
	istringstream ssin(sline);
	ssin>>cf.station_num;

	string weth24,wind24,temp24, weth48,wind48,temp48;

	ssin>>weth24>>wind24>>temp24>>weth48>>wind48>>temp48;

	cf.israin[0] = israin(weth24.substr(1,2));
	cf.israin[1] = israin(weth24.substr(3,2));
	cf.israin[2] = israin(weth48.substr(1,2));
	cf.israin[3] = israin(weth48.substr(3,2));

	istringstream ssin2(temp24.substr(1,2)), ssin3(temp48.substr(1,2));

	ssin2>>cf.min_t[0]; ssin3>>cf.min_t[1];
	ssin2.clear();ssin3.clear();

	ssin2.str(temp24.substr(3,2)); ssin3.str(temp48.substr(3,2));
	ssin2>>cf.max_t[0]; ssin3>>cf.max_t[1];
	ssin2.clear();ssin3.clear();

	return cf;
}

city_fst & read_city_fst(city_fst & cf,const city_message &mess)
{
	cf.israin.clear();
	cf.max_t.clear();
	cf.min_t.clear();

	cf.station_num = mess.stn;

	for(int i=0;i<mess.fcn;i++)
	{
		cf.israin.push_back(israin(mess.data[i][19]));
	}
	
	for(int i=1;i<mess.fcn;i+=2)
	{
		cf.max_t.push_back(mess.data[i][11]);
		cf.min_t.push_back(mess.data[i][12]);
	}

	return cf;
}