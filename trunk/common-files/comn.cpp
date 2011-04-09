#include "comn.h"

bool beql(double a,double b,int per)
{
	if(abs(a-b) < pow(10.0,-per) )
		return true;
	else 
		return false;
}