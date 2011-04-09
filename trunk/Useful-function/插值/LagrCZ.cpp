#include<iostream>
#include<cmath>
using namespace std;
double yy(double x);
double pn(double _x);

int main()
{

	cout<<yy(2.5)<<ends<<pn(2.5)<<endl;
}
double yy(double x)
{
	return x*x+sin(x);
}
double pn(double _x)
{
	int n=2;           
	double pn=0,x[3]={0,1,2},y[3];
	for(int i=0;i<=n;i++)
		y[i]=yy(x[i]);
	for(int k=0;k<=n;k++)
	{
		double lx=1;
		for(int j=0;j<=n;j++)
		{
			if(j==k) continue;
			lx*=(_x-x[j])/(x[k]-x[j]);
		}
		pn+=y[k]*lx;

	}
	return pn;
}