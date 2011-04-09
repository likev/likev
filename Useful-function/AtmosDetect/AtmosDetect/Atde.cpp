#include <iostream>
#include <cmath>

using namespace std;

double valE(double T)
{
	double Ew,T0=273.16;

	Ew= 10.79574*(1-T0/T)-5.028*log10(T/T0)
	   +1.50475*(1-pow(10.0,-8.2969*(T/T0-1)))*1e-4 
	   +0.42873*(pow(10.0,4.76955*(1-T0/T))-1)*1e-3+0.78614;

	return pow(10.0,Ew);
}

int main()
{//
	double pi=3.14159265,h=1752.4,b=35+57.0/60;
	double ca,p,ph,gn=9.80665,tp;

	double E,Ew,T0=273.16,t,td,tw,A=0.667e-3;

	while(1)
	{
		cout<<"\n\n-----------------------\n";

		cout<<"\n     �����¶�t :"; cin>>t; cout<<"     ʪ���¶�tw:";cin>>tw;
		cout<<"\n      ��ѹP����:";cin>>p;cout<<"       �����¶�: ";cin>>tp;

		ca=cos(2*b*pi/180);
			
		ph=p*(1-0.0026442*ca)*(1-0.000000196*h)*(1+0.0000184*tp)/(1+0.0001818*tp);

		E=valE(tw+T0)-A*ph*(t-tw);
		Ew=valE(t+T0);
 
        td=243.92*log10(E/6.1078)/(7.69-log10(E/6.1078));

		cout<<"\n\n      ˮ��ѹ  e:"<<E
			<<"\n      ���ʪ��U:"<<E/Ew*100
			<<"\n     ¶���¶�Td:"<<td<<endl;
		cout<<"\n       ��վ��ѹ:"<<ph;
	}

}