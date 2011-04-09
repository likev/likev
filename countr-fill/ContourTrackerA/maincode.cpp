// maincode.cpp : 定义控制台应用程序的入口点。
//
#include <comn.h>
#include "contour_track.h"


int main()
{
	using namespace std;

	contr::contour_track ac("t.txt");
	ac.begin_actions();
	
	contr::contour_track::iso_lines_type lines = ac.get_all_iso_line();
	
	for(size_t i=0;i<lines.size();i++)
	{
		for(size_t j=0;j<lines[i].a_iso_line.size();j++)
		{
			cout<<endl<<lines[i].a_iso_line[j].xy.x
				<<"  "<<lines[i].a_iso_line[j].xy.y;
		}
		cout<<endl<<";";
	}
	
	
}