//-------������---------------
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
	int m=0;   //��¼�����ĸ���
	for(int i=1001;i<=10000;i+=2)   //�������ܴ��iֵ���Ը�Ϊlong int
		if(isprime(i))
		{
			if(m%5==0) cout<<endl;
			m++;
			cout<<"i=";
			cout.width(8);
			cout<<left<<i;
		}
		cout<<"\n����"<<m<<"������"<<endl;
  
	 cout<<clock()<<endl; 
	 cin.get();
}
*/