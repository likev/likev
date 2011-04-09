#include "micaps-data.h"
#include <iostream>
#include <wx/string.h>

int main()
{
	using std::cout;using std::endl;
	
	double dirct,val;
	
	Diamond2 dm3("/home/atqixiangju/data/ecmwf/wind/500/10072008.000");
	
	cout<<dm3.GetValue(35,0,dirct,val)<<endl;
	cout<<val<<endl;
	
	int a = 10;
	cout<<wxString::Format(wxT("%03d"),a).mb_str()<<endl;
}
