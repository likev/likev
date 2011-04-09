//自然常数e和特殊方阵。

#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;



int canum(int i,int j,int n)
{
	int t=i+1;

	if(t>n-i) t=n-i;
	if(t>j+1) t=j+1;
	if(t>n-j) t=n-j;

	return t;
}

void fanz(int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			switch(canum(i,j,n))
			{
			case 1:cout<<"X ";break;
			case 2:cout<<"Y ";break;
			case 3:cout<<"Z ";break;
            default:cout<<canum(i,j,n)-3<<ends;
			}

		}
		cout<<endl;
	}
}

int main()
{
	double t=1,e=2;

	for(int i=2;i<50;i++)
	{
		t*=i;
		e+=1/t;
	}
	cout<<setprecision(16)<<e<<endl;

	fanz(8);
}