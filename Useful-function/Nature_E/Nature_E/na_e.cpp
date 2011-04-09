#include<iostream>

using namespace std;


int main()  
{
	int n=0;
	double s=0,t=0;
	double a[54]={4,4,4,4,2,3,3,1.5,1.5,2,3,6,4,5,3,5,4,5,3,3,4,2,3,3,4,5,3,1,
	              4,3,4,3,4,4,2,2,3,2,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3};

	while(++n)
	{
		cout<<"\n\n---------------------"<<n<<"---------------------\n\n";
		for(int i=0;i<54;i++)	
		{
			switch(i)
			{
			case 0:   cout<<" 1---5: ";break;
			case 5:   cout<<" 6--10: ";break;
			case 10:  cout<<"11--15: ";break;
			case 15:  cout<<"16--20: ";break;
			case 20:  cout<<"21--25: ";break;
			case 25:  cout<<"26--30: ";break;
			case 30:  cout<<"31--35: ";break;
			case 35:  cout<<"36--40: ";break;
			case 40:  cout<<"41--45: ";break;
			case 45:  cout<<"46--50: ";break;
			case 50:  cout<<"51--54: ";break;
			default:break;
			}

			cin>>s;
			t+=s*a[i];

		}

		cout<<"\n   A = "<<t/147<<endl;
	}
	cin>>s>>s;
}
