//------------------------
#include"caipiao.h"
//-----------------------------------------
void hongqiujiange(int b[][7])
{
	ofstream fout("hongqiu.txt");                              
	if(!fout)
	{ cout<<"Can not open input file.\n";
	return;
	}

	fout<<"--------------最近第"<<M<<"期--第"<<N<<"期各红球间隔情况如下-----------\n";
	for(int a=1;a<34;a++)
	{
		fout.width(2);
		fout<<a<<":";
		int m=0,n=0,k=1;
		for(int i=M;i<N;i++) 
		{		
			for(int j=0;j<6;j++)
			{
				if(b[i][j]==a)		//A
				{
					k++;
					if(k%35==0) fout<<"\n   ";
					m=n;
					n=i;
					fout.width(4);  
					fout<<n-m;
				}
			}
		}
		
		fout<<"\n------------------------------------------------------------------------------";
		fout<<"--------------------------------------------------------------------------"<<endl;
	}

	fout.close();

}