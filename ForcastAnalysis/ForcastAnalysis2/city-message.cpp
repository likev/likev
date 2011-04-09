//#include "StdAfx.h"

#include "city-message.h"
#include <sstream>

bool city_message::init(string snum,const string& sfile)
{
	using namespace std;

	size_t n=sfile.find(snum);
	if(n==sfile.npos) //Î´ÕÒµ½
		return false;
	std::istringstream istream(sfile.substr(n,4000));

	istream>>stn>>lon>>lat>>h>>fcn>>ele;
	
	data.clear();
	vector<double> t;double m;
	for(int i=0;i<fcn;i++)
	{
		data.push_back(t);
		for(int j=0;j<=ele;j++)
		{
			if(!(istream>>m))
				return false;
			data[i].push_back(m);
		}

	}

	return true;
	
}
