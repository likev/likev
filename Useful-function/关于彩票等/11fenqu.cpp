#include"caipiao.h"

void fenqu11(int b[][7])
{
	
    //---------蓝球每4个为一组----------------
	ofstream fout("11fenqu.txt");
	if(!fout)
	{ cout<<"Can not open input file.\n";
	return;
	}
	
	fout<<"-------------最近第"<<M<<"期--第"<<N<<"期各红球分区情况如下:------------\n";
	fout<<"           1-3:    4-6:    7-9:   10-12:  13-15:  16-18:  19-21:  22-24:  25-27:  28-30:  31-33:\n\n";
	
	for(int i=N-1;i>M-1;i--)
	{
		fout.width(3);
		fout<<i<<":";
		
		int m=0,k=0;
		for(int j=0;j<6;j++)
		{
			int m1=(b[i][j]+2)/3,t=0;
			if(m1==m) {k++;fout<<"#";}
			else 
			{
				t=(m1-m)*8;
				fout.width(t-k);
				fout<<"#";
				k=0;
			}
			
            m=m1;
		}
		fout<<endl<<endl;	
	}

	fout<<"           1-3:    4-6:    7-9:   10-12:  13-15:  16-18:  19-21:  22-24:  25-27:  28-30:  31-33:\n\n";
	
	fout.close();
}