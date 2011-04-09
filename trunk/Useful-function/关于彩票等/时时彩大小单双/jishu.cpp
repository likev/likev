#include<iostream>
using namespace std;

int main()
{
	int a=0,b=0,p=1;
	double t=0;
	for(int i=0;p!=0;i++)
	{
		cin>>p;
		if(p==2) {a++;b++;}
		else if(p==3) b++;
		else continue;
	}

	cout<<"a=="<<a<<"    b=="<<b<<endl;
	cout<<"a/b=="<<static_cast<double>(a)/b<<endl;
}