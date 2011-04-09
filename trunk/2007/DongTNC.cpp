//-------------------
#include<iostream>
using namespace std;
//-------------------
int main()
{
	int m=12;
	int *p=new int[m];
	*p=8;
	*(p+1)=11;
	*(p+2)=12;p[3]=13;*(p+4)=14;*(p+5)=15;*(p+6)=16;*(p+7)=17;*(p+8)=18;
	for(int i=1;i<9;i++)
	{
	   cout<<"p+"<<i<<"="<<p+i<<"  *(p+"<<i<<")="<<p[i]<<endl;
	}
}