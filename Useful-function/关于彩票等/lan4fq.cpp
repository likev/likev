
#include"caipiao.h"

void lan4fq(int b[][7])
{

    //---------蓝球每4个为一组----------------
	ofstream fout("Lan4FQ.txt");
	if(!fout)
	{ cout<<"Can not open input file.\n";
	return;
	}

	fout<<"最近第"<<M<<"期--第"<<N<<"期各蓝球分区情况如下:\n";
	
	fout<<"     1:  2:  3:  4:"<<endl<<endl;
	for(int i=M;i<N;i++)
	{
		//if(i%40==0) fout<<endl<<i/40<<":";
		fout.width(3);
		fout<<i<<":";
		switch(b[i][6])
		{
		case 1:
		case 2:
		case 3:
		case 4:fout<<"  *\n";break;
		case 5:
		case 6:
		case 7:
		case 8:fout<<"      *\n";break;
		case 9:
		case 10:
		case 11:
		case 12:fout<<"          *\n";break;
		case 13:
		case 14:
		case 15:
		case 16:fout<<"              *\n";break;
		}
		
	}
	fout.close();
}