#include<iostream.h>

template <typename T> void maopao(int n,T a[]);
template <typename T> void xuanze(int n,T a[]);
//-------------------------------
int main()
{
	int a[5]={3,2,5,1,6};
	maopao(5,a);
	for(int i=0;i<5;i++)
		cout<<"a["<<i+1<<"]="<<a[i]<<endl;
	xuanze(5,a);
    for(i=0;i<5;i++)
		cout<<"a["<<i+1<<"]="<<a[i]<<endl;
}

template <typename T>        //����ģ�壬ʵ�ֹ�����ͬ���������Ͳ�ͬ�� 
void maopao(int n,T a[])     //ð�����򷨣�����������Ԫ�أ�����һ������
{
	T *p1=0,*p2=0,t=0;
	for(int i=0;i<n-1;i++)
	{
        p1=a;p2=a+1;
		for(int j=0;j<n-i-1;j++)
		{
			if(*p1>*p2)
			{ t=*p1;*p1=*p2;*p2=t; }  //��������Ԫ�ء�
			p1++;
			p2++;
		}
	}
}

template <typename T>
void xuanze(int n,T a[])     //ѡ�����򷨣�����ѡ����СԪ�أ���������
{
	T t=0;
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(a[j]<a[i])
			{ t=a[i];a[i]=a[j];a[j]=t; }  //������Ԫ�ء�
}


