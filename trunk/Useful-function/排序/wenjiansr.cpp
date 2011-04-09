#include"fstream.h"
int const N=665;
//------------------------------------------
template <typename T> void xuanze(int n,T a[]);
int main()           //子函数读取文件，将值赋给数组b[][7].
{                   //字符串s代表文件名，注意应写出格式名.txt。

	int b[N][7]={0};
	ifstream fin("shuju.txt");                              
	if(!fin)
	{ cout<<"Can not open output file.\n";
	  return;
	}

	for(int i=0;i<N;i++)
	{
		for(int j=0;j<7;j++)
		{
			fin>>b[i][j];
		}
	}

	for(i=0;i<N;i++)
		xuanze(6,b[i]);


	ofstream fout("shuju1.txt");                              
	if(!fout)
	{ cout<<"Can not open output file.\n";
	  return;
	}

	for(i=0;i<N;i++)
	{
		for(int j=0;j<7;j++)
		{
			fout.width(3);
			fout<<b[i][j];
		}
		fout<<endl;
	}

	fout.close();

	



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
