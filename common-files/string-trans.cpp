#include "string-trans.h"
#include <istream>
#include <iomanip>
#include <algorithm>

std::string getstring(std::istream &istr,int count)
{
	
	char *p = new char[count+1];
	istr.get(p,count+1);
	
	std::string s(p);
	delete [] p;

	return s;
}

std::string & str_trim_left(std::string &str,const std::string &trim_str)
{
	size_t p=str.find_first_not_of(trim_str);
	
	str.erase(0,p);

	return str;
}

std::string & str_trim_right(std::string &str,const std::string &trim_str)
{
	size_t p=str.find_last_not_of(trim_str);
	
	str.erase(p+1);

	return str;
}

std::string & str_trim(std::string &str,const std::string &trim_str)
{
	str_trim_left(str,trim_str);
	str_trim_right(str,trim_str);

	return str;
}


std::vector<std::string> & 
str_split(const std::string &str,std::string by, std::vector<std::string> &vecstr, bool istrim)
{
	vecstr.clear();
	std::string::size_type pos1=0,pos2=pos1;
	std::string temp;

	while(pos1 < str.size())
	{
		pos2 = str.find(by,pos1);

		temp = str.substr(pos1,pos2-pos1);
		if(istrim) str_trim(temp);
		if(temp.size()) vecstr.push_back(temp);

		if(pos2 == std::string::npos) break;
		
		pos1 = pos2+1;
		
	}

	return vecstr;
}

bool filetostr(std::string file,std::string & str, unsigned ignorelines)
{
	std::wstring wfile;
	AnsiToUtf16(file,wfile);

	std::ifstream fin(wfile.c_str());
	if(!fin.is_open())
	{
		return false;
	}

	str="";
	std::string temp;
	unsigned i=0;
	while(std::getline(fin,temp))
	{
		if(++i >ignorelines)
			str += temp+"\n";
	}

	fin.close();
	return true;
}

bool strtofile(std::string file,const std::string & str)
{
	std::wstring wfile;
	AnsiToUtf16(file,wfile);

	std::ofstream fout(wfile.c_str());
	if(!fout.is_open())
	{
		return false;
	}

	fout<<str;

	fout.close();
	return true;
}

//编码转换
std::string & Utf8ToAnsi(std::string &scr, std::string &des)
{
	size_t n = scr.size()*2;
	wchar_t *sl = new wchar_t[n];

	char *sm = new char[n];

	MultiByteToWideChar(CP_UTF8,0,scr.c_str(),-1,sl,n);
	WideCharToMultiByte(CP_ACP, 0,sl, -1,sm, n,NULL,0);

	des = sm;
	delete []sl;
	delete []sm;

	return des;
}

std::wstring & AnsiToUtf16(std::string &scr, std::wstring &des)
{
	size_t n = scr.size();
	
	wchar_t *sl = new wchar_t[n+1];

	MultiByteToWideChar(CP_ACP,0,scr.c_str(),-1,sl,n+1);

	des = sl;
	delete []sl;

	return des;
}

//将日期或时间字符串转化为CTime类型
CTime CStringToCTime(CString str,int type)
{
	//CString   s("2001-8-29 19:06:23");   
	int  nYear=2000, nMonth=1, nDate=1, nHour=0, nMin=0, nSec=0;
	switch(type)
	{
	case 0:
		sscanf_s(str, "%d-%d-%d %d:%d:%d", &nYear, &nMonth, &nDate, &nHour, &nMin, &nSec); 
		break;
	case 1:
		sscanf_s(str, "%d:%d:%d", &nHour, &nMin, &nSec); 
		break;
	default:break;
	}
	
	return CTime(nYear, nMonth, nDate, nHour, nMin, nSec);
}

std::string dtos(double a, int precision, bool isfixed)
{
	using namespace std;

	string m;
	stringstream stream;

	stream<<fixed<<setprecision(precision)<<a;

	stream>>m;

	return m;
}


//获取标签(必需有结束标签)内容
std::string get_tag_content(std::string tag_html,std::string tag)
{
	size_t pos1,pos2,pos3;
	pos1 = tag_html.find("<"+tag);
	pos2 = tag_html.find(">",pos1);	
	pos3 = tag_html.find("</"+tag+">",++pos2);

	return tag_html.substr(pos2,pos3-pos2);
}

//http://www.vimer.cn/2009/11/string%E6%9B%BF%E6%8D%A2%E6%89%80%E6%9C%89%E6%8C%87%E5%AE%9A%E5%AD%97%E7%AC%A6%E4%B8%B2%EF%BC%88c%EF%BC%89.html
//替换字符串  //将"12212"这个字符串的所有"12"都替换成"21"
//--->22211
std::string& replace_all(std::string& str,const std::string& old_value,const std::string& new_value)   
{   
    while(true)   
	{   
		std::string::size_type pos(0);   
		if( (pos=str.find(old_value))!=std::string::npos)   
			str.replace(pos,old_value.length(),new_value);   
        else   break;   
    }   
    return   str;   
}
//--->21221
std::string& replace_all_distinct(std::string& str,const std::string& old_value,const std::string& new_value)   
{   
	for(std::string::size_type pos(0); pos!=std::string::npos; pos+=new_value.length())   
	{   
		if(   (pos=str.find(old_value,pos))!=std::string::npos   )   
            str.replace(pos,old_value.length(),new_value);   
        else   break;   
    }   
    return   str;   
}