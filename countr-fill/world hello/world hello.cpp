// world hello.cpp : 定义控制台应用程序的入口点。
//
#include <iostream>
#include "string-trans.h"
#include "contour_fill.h"
int main()
{
	using namespace std;

	contour_fill::contr_set_type lines=readdata();

	vector<contour_fill::contr_set_type> contr_set_type;

	contour_fill(lines,0,0,450,350).get_fill_contours(contr_set_type);

	return 0;
}

