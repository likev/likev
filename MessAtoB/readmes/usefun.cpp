//程序中用到的功能函数定义
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>

std::string & filetostr(std::string file,std::string & str)
{
	std::ifstream fin(file.c_str());
	if(!fin.is_open())
	{
		return str;
	}

	str="";
	std::string temp;
	while(std::getline(fin,temp))
	{
		str += temp+'\n';
	}

	fin.close();
	return str;
}

std::string dtos(double a, int l)
{
	using namespace std;

	string m;
	stringstream stream;

	stream<<fixed<<setprecision(l)<<a;

	stream>>m;

	return m;
}