
#ifndef _MICAPS_DIAMOND3_
#define _MICAPS_DIAMOND3_


#include "cmath-ex.h"

#include <cmath>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

//#include <iostream>

struct PointValue
{
	double lon,lat,val;
	
	PointValue()
	{
		lon = lat = val = 0;
	}
	
	PointValue(double lonitude,double latitude, double value)
	{
		lon = lonitude;
		lat = latitude;
		val = value;
	}
	
};

struct WindVector
{
	double dirct , val;
	
	WindVector()
	{
		dirct = val = 0;
	};
	
	WindVector(double direction, double value)
	{
		dirct = direction;
		val = value;
	};
	
};

struct PointWind
{
	double lon,lat,dirct,val;
	
	PointWind()
	{
		lon = lat = dirct = val = 0;
	}
	
	PointWind(double lonitude, double latitude, double direction, double value)
	{
		lon = lonitude;
		lat = latitude;
		dirct = direction;
		val = value;
	}
};

class Diamond3
{
public:
	Diamond3(){};
	Diamond3(const std::string &filename)
	{
		init(filename);
	};
	
	bool init(const std::string &filename)
	{
		std::ifstream fin(filename.c_str());
		
		if(!fin.is_open())
		{
			//std::cout<< "no such file! "<<std::endl;
			return false;
		}
			
		std::string linestr;
		getline(fin,linestr);
		getline(fin,linestr);
		
		gridPoints.clear();
		
		int id;
		double lon,lat,h,val;

		while(fin>>id)
		{
			fin>>lon>>lat>>h>>val;
			//if( !dbeql(val,9999.0,0) )
			{
				gridPoints.push_back(PointValue(lon,lat,val) );
			}
		}
		return true;

	}
	
	bool GetValue(double lon,double lat, double & value)const
	{
		for(std::vector<PointValue>::const_iterator it=gridPoints.begin();
			it != gridPoints.end(); ++it)
		{
			//std::cout<< it->lon <<"  "<<it->lat<<std::endl;
			if(it->lon == lon && it->lat == lat)
			{
				
				value = it->val;
				return true;
			}
		}
		
		return false;
	}
		
private:
	std::vector<PointValue> gridPoints;
};

class Diamond2
{
public:
	Diamond2(){};
	Diamond2(const std::string &filename)
	{
		init(filename);
	};
	
	bool init(const std::string &filename)
	{
		std::ifstream fin(filename.c_str());
		
		if(!fin.is_open())
			return false;
			
		std::string linestr;
		getline(fin,linestr);
		getline(fin,linestr);
		
		gridPoints.clear();
		
		int id;
		double lon,lat,h,dirct,val;

		while(fin>>id)
		{
			fin>>lon>>lat>>h>>h>>h>>h>>h>>dirct>>val;

			//if( !dbeql(dirct,9999.0,0) && !dbeql(val,9999.0,0) )
			{
				gridPoints.push_back(PointWind(lon,lat,dirct,val) );
			}
		}
		return true;

	}
	
	bool GetValue(double lon,double lat, double & direction, double & value)const
	{
		for(std::vector<PointWind>::const_iterator it=gridPoints.begin();
			it != gridPoints.end(); ++it)
		{
			if(it->lon == lon && it->lat == lat)
			{
				direction = it->dirct;
				value = it->val;
				return true;
			}
		}
		
		return false;
	}
	
	bool GetValue(double lon,double lat, WindVector & wind)const
	{
		for(std::vector<PointWind>::const_iterator it=gridPoints.begin();
			it != gridPoints.end(); ++it)
		{
			if(it->lon == lon && it->lat == lat)
			{
				wind = WindVector(it->dirct,it->val);
				return true;
			}
		}
		
		return false;
	}
		
private:
	std::vector<PointWind> gridPoints;
};


#endif  /*_MICAPS_DIAMOND3_*/
