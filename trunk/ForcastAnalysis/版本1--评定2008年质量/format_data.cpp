#include "comn.h"

void format_csv_file(std::string sfile)
{
	using namespace std;

	ifstream fin(sfile.c_str());

	string format_file = sfile + "_format.txt";
	ofstream fout(format_file.c_str());

	if(!fin.is_open())
	{
		cout<<"打开文件 "<<sfile<<" 失败！"<<endl;
	}

	if(!fout.is_open())
	{
		cout<<"打开文件 "<<format_file<<" 失败！"<<endl;
	}

	string sline;

	while(getline(fin,sline))
	{
		string date, val;

		istringstream ssin(sline);

		ssin>>date;
		fout<<setw(12)<<date;

		while(ssin>>val)
		{
			fout<<setw(8)<<val;
		}
		fout<<endl;
	}

	fin.close();
	fout.close();


}