//---------------------------
#include<iostream>
#include<cmath>
#include<ctime>
#include<conio.h>
#include<iomanip>

using namespace std;
//---------------------------
int dif_equ()
{
	double x0=0,y0=0,x1,y1,d2;
	int i=0;

	clock_t ct=clock();

	while(clock()-ct <100*1000)//10秒
	{
		i++;
	/*	
	    收敛形式
		x1=y0-2;
		y1=0.5*x0+4;
	*/	

		//发散形式
		y1=x0+2;
		x1=2*y0-8;

		cout<<setw(5)<<i<<":  "<<setw(5)<<x1<<"   "<<setw(5)<<y1<<endl;

		if(abs(x1)>1e100 || abs(y1)>1e100) break;//发散
		
		d2=(x1-x0)*(x1-x0)+(y1-y0)*(y1-y0); 
		if(  d2<1e-8 )
		{
			cout<<d2<<endl;
			break;                  //收敛
		}

		x0=x1;y0=y1;

		if( (clock()-ct)%100 ==0)
		{
			system("pause");
		}
	}

	return 0;
}

int main()
{

	dif_equ();


}

