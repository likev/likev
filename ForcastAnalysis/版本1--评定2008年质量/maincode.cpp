#include "comn.h"
#include "deal-database.h"
#include "city_forecast.h"

void main_deal();
void readVal();

// ����2008-2009��������

int main()
{
	using namespace std;

	cout<<endl<<"����Ԥ����������   2010��1�� by xufanglu"<<endl;
	cout<<"-----------------------------------------------------------------"<<endl;
	
	int i=0;
	while(true)
	{
		cout<<endl<<"���˷��� "<<++i<<endl;
			cout<<"-----------------------------------------------\n\n";
		main_deal();
	}
}