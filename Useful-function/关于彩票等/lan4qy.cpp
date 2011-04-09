
#include"caipiao.h"

void lan4qy(int b[][7])
{ 

	//-------蓝球除以4的余数--------------
	ofstream fout("Lan4QY.txt");
	if(!fout)
	{ cout<<"Can not open input file.\n";
	return;
	}
	
	fout<<"最近第"<<M<<"期--第"<<N<<"期各蓝球求余情况如下:\n\n";
	fout<<"      0:  1:  2:  3:"<<endl<<endl;
	for(int i=M;i<N;i++)
	{			
		//if(i%40==0) fout<<endl<<i/40<<":";
		fout.width(3);
		fout<<i<<":  ";
		for(int j=0;j<b[i][6]%4;j++)
			fout<<"    ";
		fout<<"*   \n";
	}
	
	fout.close();
}