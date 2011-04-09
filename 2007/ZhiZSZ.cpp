//---------------------------
#include<iostream.h>
//---------------------------
int main()
{
	int a[5][3]={{1,2,3},4,5,6,{7,8,9},10,11,12,13,14,15};
	cout<<"a[5][3]:\n";
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout.width(3);
			cout<<a[i][j];
		}
		cout<<endl;
	}

	int *p=a[0];
	
	cout<<"int *p=a[0]\np=:"<<p<<"    a=="<<a<<endl;
	p=a[1];
	cout<<"p=a[1]\np=:"<<p<<endl;
	cout<<"p+1="<<p+1<<endl;
	cout<<"a+1="<<a+1<<endl;
	cout<<"**a=="<<**a<<endl;

	int (*p2)[3]=a;	 //p是指向（具有3个元素的一维整型数组）的指针
	cout<<"int (*p2)[3]=a:\np2=="<<p2<<"    a=="<<a<<endl;
	cout<<"p2+1="<<p2+1<<"   a+1="<<a+1<<endl;
	cout<<"**(p2+1)="<<**(p2+1)<<"  *(a+1)="<<*(a+1)<<endl;
	cout<<"*(p2+1)+1="<<*(p2+1)+1<<"  *(a+1)+1="<<*(a+1)+1<<endl;
	cout<<"*(*(p2+1)+1)="<<*(*(p2+1)+1)<<"  *(*(a+1)+1)="<<*(*(a+1)+1)<<endl;  


	char* p3[3]={"How are you?","I am fine","Thanks"};

	cout<<p3[1]<<endl;









}