#include "cmath-ex.h"
#include <cmath>

const double pi = 3.14159265358979;

double sind(double d)
{
	return sin(d*pi/180);
}
double cosd(double d)
{
	return cos(d*pi/180);
}
double tand(double d)
{
	return tan(d*pi/180);
}

bool dbeql(double a,double b,int per)
{
	if(std::abs(a-b) < pow(10.0,-per) )
		return true;
	else 
		return false;
}
