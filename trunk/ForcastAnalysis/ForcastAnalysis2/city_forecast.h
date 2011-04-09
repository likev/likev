#include "comn.h"
#include "city-message.h"

#ifndef CITY_FORCAST
#define CITY_FORCAST


bool israin(std::string scode);

class city_fst
{
private:

public:
	//起报时刻
	CTime time;
	//站号
	int station_num;

	//days 时次的最高最低
	std::vector<double> max_t, min_t;


	//2*days 时次是否报雨
	std::vector<bool> israin;

	explicit city_fst(int days=2)
		:israin(2*days,false)
		,max_t(days,0), min_t(days,0)
	{
		station_num = 99999;
	}

	
};

city_fst & read_city_fst(const std::string & sline, city_fst & cf);
city_fst & read_city_fst(city_fst & cf,const city_message &mess);

#endif //CITY_FORCAST