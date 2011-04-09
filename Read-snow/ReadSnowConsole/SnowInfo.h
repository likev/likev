#ifndef _SNOW_INFO
#define _SNOW_INFO

#include "comn.h"

class SnowInfo
{
	bool isValid;
	double snowVolumn;
	double snowDepth;

public:
	SnowInfo()
	{
		isValid = false;
		snowVolumn = 0;
		snowDepth = 0;
	}

	SnowInfo(double volumn, double depth)
	{
		if(volumn>=0 && depth>=0)
		{
			isValid = true;
			snowVolumn = volumn;
			snowDepth = depth;
		}
	}

	SnowInfo operator +(const SnowInfo& right)const
	{
		//if(!isValid || !right.isValid) return SnowInfo();

		double depth = snowDepth > right.snowDepth ? snowDepth : right.snowDepth;
		return SnowInfo(this->snowVolumn + right.snowVolumn, depth);
	}
	bool IsValid()const
	{
		return this->isValid;
	}

	double GetVolumn()const
	{
		return isValid ? snowVolumn : -1;
	}

	double GetDepth()const
	{
		return isValid ? snowDepth : -1;
	}

	std::string GetSnowStr()const
	{
		std::ostringstream sout("");

		sout<<GetDepth()<<"/"<<GetVolumn();

		return sout.str();
	}
};


#endif //_SNOW_INFO