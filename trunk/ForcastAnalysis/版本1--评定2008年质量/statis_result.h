#include "comn.h"
#include "city_forecast.h"

#ifndef CITY_STATIS
#define CITY_STATIS

class stat_result
{
public:
	int avail_days;
	std::vector<int> min_t, min_t_high, min_t_low,
		             max_t, max_t_high, max_t_low;

	std::vector<int> rain_all;
	std::vector<int> rain_right, rain_empty, rain_miss;

//默认降水为4个时次 最高最低各为2个时次
	stat_result()
		:rain_right(4,0), rain_empty(4,0), rain_miss(4,0),rain_all(4,0)
		,min_t(2,0), min_t_high(2,0), min_t_low(2,0)
		,max_t(2,0), max_t_high(2,0), max_t_low(2,0)
	{
		avail_days = 0;
	}
};

bool stat_day(std::string worker, CTime when, std::map<int, stat_result> & statis_result);

#endif //CITY_STATIS