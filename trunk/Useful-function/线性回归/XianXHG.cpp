//-----一元线性回归---------------
#include<iostream.h>
int const N=20;
//-----------一元线性回归--------------
class huigui 
{
	double x[N],y[N];
public:
	huigui(double a[],double b[]);  //构造函数   //系统生成默认析构函数
	void Xxhg();	                
	
};

huigui::huigui(double a[],double b[N])
{
	for(int i=0;i<N;i++)
	{x[i]=a[i];y[i]=b[i];}
}


void huigui::Xxhg()
	{
		double x1=0,y1=0,t1=0,t2=0,b=0,b0=0;
		for(int i=0;i<N;i++)
		{
			x1+=x[i];
			y1+=y[i];
			t1+=x[i]*y[i];
			t2+=x[i]*x[i];
		}
		
		b=(t1-x1*y1/N)/(t2-x1*x1/N);
		b0=y1/N-b*x1/N;
		
		if(b>0)       cout<<"回归方程为：^y="<<b0<<"+"<<b<<"x"<<endl;
		else if(b==0) cout<<"回归方程为：^y="<<b0<<endl;
		else          cout<<"回归方程为：^y="<<b0<<b<<"x"<<endl<<endl;
		cout<<"∑X="<<x1<<"   ∑Y="<<y1<<endl;
		
	}	

//--------------------------------
int main()
{
	double a1[20]={32.0,25,20, 26,   27, 24,  28, 24, 15, 16, 24,  30, 22, 30, 24, 33, 26, 20, 32,  35},
		   b1[20]={0.9,1.2,2.2,2.4,-0.5,2.5,-1.1,0.0,6.2,2.7,3.2,-1.1,2.5,1.2,1.8,0.6,2.4,2.5,1.2,-0.8};
	huigui m(a1,b1);
	m.Xxhg();
}
