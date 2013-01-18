//处理字符串与其他类型转换

#ifndef STRING_TRANS
#define STRING_TRANS

#include <string>
#include <vector>
#include <sstream>
#include <fstream>


//将字符串转化为其他类型(主要为数字)
template <typename T>
T& string_to(const std::string & org, T& des)
{
	std::istringstream ssin(org);

	ssin>>des;
	return des;
}
template <typename T>
T string_to(const std::string & org)
{
	T des;
	std::istringstream ssin(org);

	ssin>>des;
	return des;
}

//将其他类型(主要为数字)转化为字符串
template <typename T>
std::string& to_string(const T& org, std::string & des)
{
	std::ostringstream sout;

	sout<<org;
	return des=sout.str();
}
template <typename T>
std::string to_string(const T& org)
{
	std::string des;
	std::ostringstream sout;

	sout<<org;
	return des=sout.str();
}

//从流中获取一定字节数的字符串
std::string getstring(std::istream &istr,int count);

template <typename T>
bool readcols(std::string file, std::vector<T> & vals, int col, int ignoreline=0)
{
	std::ifstream fin(file.c_str());
	if(!fin.is_open())
	{
		return false;
	}

	for(int i=0;i<ignoreline;i++)
	{
		std::string line;
		std::getline(fin,line);
	}
	
	vals.resize(0);
	
	while(fin)
	{
		std::string unusestr;
		for(int i=0;i<col-1;i++)
		{
			fin>>unusestr;
		}


		T val;
		if(fin>>val)
			vals.push_back(val);

		std::getline(fin,unusestr); 
	}
	fin.close();

	return true;
}

#endif /* STRING_TRANS */