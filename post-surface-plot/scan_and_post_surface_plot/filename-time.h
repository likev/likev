#ifndef _FILENAME_TIME
#define _FILENAME_TIME

#include <afxwin.h>         // MFC 核心和标准组件

#include <string>

class FilenameTime{

	std::string name;
	CTime time;

public:
	FilenameTime(){}
	FilenameTime(std::string filename, CTime related_time)
	{
		name = filename;
		time = related_time;
	}

	std::string get_name()const
	{
		return name;
	}
	CTime get_time()const
	{
		return time;
	}

	bool name_equal(const FilenameTime &right)const
	{
		return name == right.get_name();
	}

};

bool time_less_than(const FilenameTime &left,const FilenameTime &right);

#endif //_FILENAME_TIME