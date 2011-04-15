//-------求素数---------------
#include <iostream>
#include <ctime>
#include <cmath>
using namespace std;
//----------------------------

bool isprime(int n)
{
	bool flag=true;
	for(int k=2;k<=sqrt(double(n))&&flag==true;k++)
		flag=(n%k!=0);
	return flag;
}

/*
//-----------------------------
int main()
{   
	int m=0;   //记录素数的个数
	for(int i=1001;i<=10000;i+=2)   //如果想求很大的i值可以改为long int
		if(isprime(i))
		{
			if(m%5==0) cout<<endl;
			m++;
			cout<<"i=";
			cout.width(8);
			cout<<left<<i;
		}
		cout<<"\n共有"<<m<<"个素数"<<endl;
  
	 cout<<clock()<<endl; 
	 cin.get();
}
*/