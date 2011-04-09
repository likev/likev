
#include "comn.h"

bool log_to_file(const std::string &filename, const std::string &information)
{
	CTime now = CTime::GetCurrentTime();
	std::ofstream fout(filename.c_str(),std::ios_base::out|std::ios_base::app);

	if(!fout.is_open()) return false;

	fout<<now.Format("[%Y-%m-%d %H:%M:%S]: ")<<information<<std::endl;
	fout.close();

	return true;
}

