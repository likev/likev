#include"fstream.h"
int const N=665;
//------------------------------------------
template <typename T> void xuanze(int n,T a[]);
int main()           //�Ӻ�����ȡ�ļ�����ֵ��������b[][7].
{                   //�ַ���s�����ļ�����ע��Ӧд����ʽ��.txt��

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
void xuanze(int n,T a[])     //ѡ�����򷨣�����ѡ����СԪ�أ���������
{
	T t=0;
	for(int i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if(a[j]<a[i])
			{ t=a[i];a[i]=a[j];a[j]=t; }  //������Ԫ�ء�
}
