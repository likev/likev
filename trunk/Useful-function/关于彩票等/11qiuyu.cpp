#include"caipiao.h"

void qiuyu11(int b[][7])
{
    //-----------�������11������-----------
	ofstream fout("11qiuyu.txt");                              
	if(!fout)
	{ cout<<"Can not open input file.\n";
	return;
	}
	
	fout<<"�����"<<M<<"��--��"<<N<<"�ڸ�����11�����������:\n";
	for(int i=M;i<N;i++)
	{
		fout.width(3);
		fout<<i<<":" ;
		for(int j=0;j<6;j++)
		{			
			
			fout.width(3);
			fout<<b[i][j]%11;
		}
		
		fout<<endl;
	}
	
	fout.close();
}