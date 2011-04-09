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
 
//计算素数，用每个素数去除。
	double iend=sqrt(2.0*n+1)+1;
    for(int i=3;i<iend;i+=2)
	{
		if(!s[(i-3)/2]) continue;//除数若不为素数，则跳出本次循环。
		cout.width(3);
		cout<<i*100/int(iend)<<" %";
		for(int j=(i*i-3)/2;j<n;j++)
		{
			if(!s[j]) continue;
			if(!(s[j]%i)) s[j]=0;
		}
		cout<<"\b\b\b\b\b";
	}

//以平方为界输出素数。
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