
#include"caipiao.h"

//---------------------------------------------
void shuchuhlq(int a[][49])                                                          
{
	int m=33,n=0;                                             
   	cout<<"           红球            ||     蓝球\n";
	for(int i=0;i<4;i++)                                    //用4行方式显示红球和蓝球的值
	{
		for(int j=0;j<9;j++,n++)                          //每行显示9个红球
		{
			if(n>=33) {cout<<"         ";break;}
			a[0][n]=n+1;
			cout.width(3);
			cout<<a[0][n];
		}
		cout<<"||";                                   //用||符号将红蓝球分开。
		for(int k=0;k<4;k++,m++)                     //每行显示4个蓝球。 
		{
			a[0][m]=m-32;
			cout.width(3);
			cout<<a[0][m];
		}
			cout<<endl;
	}
}
