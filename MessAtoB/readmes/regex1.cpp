
#include <iostream>
#include <iomanip>
#include <sstream>
#include "sglf.h"
#include "setinfo.h"
#include "usefun.h"

using namespace std;




void test()
{
	string str,str2,
		sf="//172.18.172.59/file/SEVP/rffc/Z_SEVP_C_BEZZ_20091025081500_P_RFFC-SPCC-200910251200-16812.TXT",
	    sf2="//172.18.172.59/file/SEVP/rffc/Z_SEVP_C_BEXA_20091025080507_P_RFFC-SPCC-200910251200-16812.TXT";
	filetostr(sf,str);
	filetostr(sf2,str2);

	str += str2;

	char * s[17]={"57143","57049","57067","57066","57065","57073","57076","57080",
		"57056","57051","57063","57070","57071","57077","57162","57074","57078"};

	vector<string> stns(s,s+17);

    sglf a;
	SetInfo c;

	string m;
	for(int i=0;i<17;i++)
	{
		if(!a.init(*(s+i),str))
		{
			cout<<"false"<<endl;
			return;
		}

		m = dtos(a.f[0][19],1);
		cout<<c.stname[a.stn]<<"     "<<m<<"     "<<c.weth[m]<<endl;
	}
}

int main()
{
	double a=3.5;
	cout<<a<<dtos(a,0)<<endl;
	test();
}