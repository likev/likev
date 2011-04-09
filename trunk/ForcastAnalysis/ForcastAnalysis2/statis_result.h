#include "comn.h"


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
	explicit stat_result(int days=2)
		:rain_right(days*2,0), rain_empty(days*2,0), rain_miss(days*2,0),rain_all(days*2,0)
		,min_t(days,0), min_t_high(days,0), min_t_low(days,0)
		,max_t(days,0), max_t_high(days,0), max_t_low(days,0)
	{
		avail_days = 0;
	}
};


#endif //CITY_STATIS