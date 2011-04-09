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

template <typename T>        //函数模板，实现功能相同，数据类型不同。 
void maopao(int n,T a[])     //冒泡排序法：交换相邻两元素，消除一个逆序。
{
	T *p1=0,*p2=0,t=0;
	for(int i=0;i<n-1;i++)
	{
        p1=a;p2=a+1;
		for(int j=0;j<n-i-1;j++)
		{
			if(*p1>*p2)
			{ t=*p1;*p1=*p2;*p2=t; }  //调换相邻元素。
			p1++;
			p2++;
		}
	}
}

template <typename T>
void xuanze(int n,T a[])     //选择排序法：依次选出最小元素，进行排序。
{
	T t=0;
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(a[j]<a[i])
			{ t=a[i];a[i]=a[j];a[j]=t; }  //调换两元素。
}


