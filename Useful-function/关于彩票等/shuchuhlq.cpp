
#include"caipiao.h"

//---------------------------------------------
void shuchuhlq(int a[][49])                                                          
{
	int m=33,n=0;                                             
   	cout<<"           ����            ||     ����\n";
	for(int i=0;i<4;i++)                                    //��4�з�ʽ��ʾ����������ֵ
	{
		for(int j=0;j<9;j++,n++)                          //ÿ����ʾ9������
		{
			if(n>=33) {cout<<"         ";break;}
			a[0][n]=n+1;
			cout.width(3);
			cout<<a[0][n];
		}
		cout<<"||";                                   //��||���Ž�������ֿ���
		for(int k=0;k<4;k++,m++)                     //ÿ����ʾ4������ 
		{
			a[0][m]=m-32;
			cout.width(3);
			cout<<a[0][m];
		}
			cout<<endl;
	}
}
