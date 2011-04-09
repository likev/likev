#ifndef ANGELTRANS
#define ANGELTRANS

#include "comn.h"
#include "string-trans.h"


class Angle
{
private:
	double decimal;
	int degrees,minutes;
	double seconds;
	
	double angle_to_decimal()
	{
		return degrees + minutes/60.0 + seconds/3600.0;
	}
public:
	Angle()
	{
		degrees = minutes = 0;
		seconds = 0;
		decimal = 0;
	}
	Angle(double dec)
	{
		degrees=int(dec);
		dec -= degrees;
		dec *= 60;
		minutes=int(dec);
		dec -= minutes;
		dec *= 60;

		seconds=dec;
	}
	Angle(std::string s)
	{
		str_trim(s);

		//degrees=minutes=seconds=0;
	}
	Angle(int d,int m,double s)
	{
		degrees = d;
		minutes = m;
		seconds = s;

		decimal = angle_to_decimal();
	}
	
	double get_decimal()
	{
		return decimal;
	}
	
	std::string get_angle_string()
	{
		std::ostringstream ostr;
		ostr<<degrees<<"бу"<<minutes<<"'"<<seconds<<"\"";
		return ostr.str();
	}
	
};


#endif //ANGELTRANS