
#include "Sglf.h"
#include <sstream>

bool Sglf::init(std::string snum,const std::string& sfile)
{
	using namespace std;

	size_t n=sfile.find(snum);
	if(n==sfile.npos) //Î´ÕÒµ½
		return false;
	istringstream istream(sfile.substr(n));

	istream>>stn>>lon>>lat>>h>>fcn>>ele;
	
	f.clear();
	vector<double> t;double m;
	for(int i=0;i<fcn;i++)
	{
		f.push_back(t);
		for(int j=0;j<=ele;j++)
		{
			if(!(istream>>m))
				return false;
			f[i].push_back(m);
		}

	}

	return true;
	
}