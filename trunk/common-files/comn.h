//common include 
#pragma once

#include <afxwin.h>         // MFC ���ĺͱ�׼���
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <map>

//#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����


//#include <afxdb.h>  //CDatabase

/*
//wxWidgets
#include <wx/wx.h>
#include <wx/fileconf.h>

*/

template <typename T>
bool beql(T a,T b,int per=9)
{
	if(abs(a-b) < pow(T(10.0),-per) )
		return true;
	else 
		return false;
}

template<typename T>
class return_define_value
{
	const T b;
public:
	return_define_value(const T& v):b(v)
	{}

	template<typename TT>
	T operator()(const TT &value)
	{
		return b;
	}
};
