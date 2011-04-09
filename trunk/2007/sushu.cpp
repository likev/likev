#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main()
{

	ofstream fout("sushu.txt");

	int n=5000;
	vector<int> s(n);

	for(int i=0;i<n;i++)
		s[i]=2*i+3;
 
//������������ÿ������ȥ����
	double iend=sqrt(2.0*n+1)+1;
    for(int i=3;i<iend;i+=2)
	{
		if(!s[(i-3)/2]) continue;//��������Ϊ����������������ѭ����
		cout.width(3);
		cout<<i*100/int(iend)<<" %";
		for(int j=(i*i-3)/2;j<n;j++)
		{
			if(!s[j]) continue;
			if(!(s[j]%i)) s[j]=0;
		}
		cout<<"\b\b\b\b\b";
	}

//��ƽ��Ϊ�����������
	fout<<"  2:  "; int k=0;
	for(int i=0,j=3;i<n;i++)	
	{
		if(s[i]>j*j) 
		{ 
			fout.width(3); 
			fout<<endl<<endl<<j<<":  ";j+=2;
		}
		if(s[i]) 
		{
			fout<<s[i]<<"  "; 
			k++;
		}
	}

	fout.close();

	cout<<endl<<k*100.0/n<<" %"<<endl;
}