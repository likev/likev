//处理字符串与其他类型转换

#ifndef STRING_TRANS
#define STRING_TRANS

#include <afxwin.h>
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

//删除str左边的空白字符并返回修改后的字串
std::string & str_trim_left(std::string &str,const std::string &trim_str=" \t\n");

//删除str右边的空白字符并返回修改后的字串
std::string & str_trim_right(std::string &str,const std::string &trim_str=" \t\n");

//删除str两边的空白字符并返回修改后的字串
std::string & str_trim(std::string &str,const std::string &trim_str=" \t\n");

//将str以字符串by分割后存储在向量vecstr中并返回此向量
std::vector<std::string> & 
str_split(const std::string &str,std::string by, std::vector<std::string> &vecstr,  bool istrim=true);

//将文件内容转化为字符串并返回
bool filetostr(std::string filename,std::string & content, unsigned ignorelines=0);

//将字符串内容写为文件
bool strtofile(std::string filename,const std::string & str);

//将UTF8编码字符串转换为Ansi编码
std::string & Utf8ToAnsi(std::string &scr, std::string &des);
//将Ansi编码字符串转换为Unicode(UTF-16)编码字符串
std::wstring & AnsiToUtf16(std::string &scr, std::wstring &des);

//将日期或时间字符串转化为CTime类型
CTime CStringToCTime(CString str,int type=0);

//将浮点数转化为字符串，默认为定点输出
std::string dtos(double a, int precision=6, bool isfixed=true);

//获取标签(必需有结束标签)内容
std::string get_tag_content(std::string tag_html,std::string tag);

//替换字符串  //将"12212"这个字符串的所有"12"都替换成"21"
//--->22211
std::string& replace_all(std::string& str,const std::string& old_value,const std::string& new_value);   

//--->21221
std::string& replace_all_distinct(std::string& str,const std::string& old_value,const std::string& new_value);

#endif /* STRING_TRANS */