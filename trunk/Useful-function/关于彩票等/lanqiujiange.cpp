
#include"caipiao.h"

//------------------------------------------------------------------
void lanqiujiange(int b[][7])
{
	
	ofstream fout("lanqiu.txt");                              
	if(!fout)
	{ cout<<"Can not open input file.\n";
	return;
	}
	
	fout<<"--------------最近第"<<M<<"期--第"<<N<<"期各蓝球间隔情况如下-----------\n";
	
	for(int a=1;a<17;a++)
	{
		fout.width(2);
		fout<<a<<":";
		int m=0,n=0,j=1;
		for(int i=M;i<N;i++) 
		{		
			if(b[i][6]==a)		//A
			{
				m=n;
				n=i;
				j++;
				if(j%35==0) fout<<"\n   ";
			    fout.width(4);  
				fout<<n-m;
			}
		}
		
		fout<<endl;
	}

	fout.close();
}
//--------------------------------------------------------------