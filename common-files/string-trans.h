//�����ַ�������������ת��

#ifndef STRING_TRANS
#define STRING_TRANS

#include <afxwin.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>


//���ַ���ת��Ϊ��������(��ҪΪ����)
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

//����������(��ҪΪ����)ת��Ϊ�ַ���
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

//�����л�ȡһ���ֽ������ַ���
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

//ɾ��str��ߵĿհ��ַ��������޸ĺ���ִ�
std::string & str_trim_left(std::string &str,const std::string &trim_str=" \t\n");

//ɾ��str�ұߵĿհ��ַ��������޸ĺ���ִ�
std::string & str_trim_right(std::string &str,const std::string &trim_str=" \t\n");

//ɾ��str���ߵĿհ��ַ��������޸ĺ���ִ�
std::string & str_trim(std::string &str,const std::string &trim_str=" \t\n");

//��str���ַ���by�ָ��洢������vecstr�в����ش�����
std::vector<std::string> & 
str_split(const std::string &str,std::string by, std::vector<std::string> &vecstr,  bool istrim=true);

//���ļ�����ת��Ϊ�ַ���������
bool filetostr(std::string filename,std::string & content, unsigned ignorelines=0);

//���ַ�������дΪ�ļ�
bool strtofile(std::string filename,const std::string & str);

//��UTF8�����ַ���ת��ΪAnsi����
std::string & Utf8ToAnsi(std::string &scr, std::string &des);
//��Ansi�����ַ���ת��ΪUnicode(UTF-16)�����ַ���
std::wstring & AnsiToUtf16(std::string &scr, std::wstring &des);

//�����ڻ�ʱ���ַ���ת��ΪCTime����
CTime CStringToCTime(CString str,int type=0);

//��������ת��Ϊ�ַ�����Ĭ��Ϊ�������
std::string dtos(double a, int precision=6, bool isfixed=true);

//��ȡ��ǩ(�����н�����ǩ)����
std::string get_tag_content(std::string tag_html,std::string tag);

//�滻�ַ���  //��"12212"����ַ���������"12"���滻��"21"
//--->22211
std::string& replace_all(std::string& str,const std::string& old_value,const std::string& new_value);   

//--->21221
std::string& replace_all_distinct(std::string& str,const std::string& old_value,const std::string& new_value);

#endif /* STRING_TRANS */