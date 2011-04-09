//单站多时效预报对象

#include <string>
#include <vector>

#ifndef SGLF
#define SGLF

using std::vector;
using std::string;

class sglf{

public:
	int stn,fcn,ele; 
	double lon,lat,h;

	//以浮点型存储数据 便于统计分析
	vector<vector<double> > f;

	bool init(string snum, const string& sfile);

};



#endif