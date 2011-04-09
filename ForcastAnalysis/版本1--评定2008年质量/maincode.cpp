#include "comn.h"
#include "deal-database.h"
#include "city_forecast.h"

void main_deal();
void readVal();

// 分析2008-2009个人质量

int main()
{
	using namespace std;

	cout<<endl<<"个人预报质量评定   2010年1月 by xufanglu"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;
	
	int i=0;
	while(true)
	{
		cout<<endl<<"个人分析 "<<++i<<endl;
			cout<<"-----------------------------------------------\n\n";
		main_deal();
	}
}