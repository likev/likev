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

	fout<<"--------------�����"<<M<<"��--��"<<N<<"�ڸ��������������-----------\n";
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