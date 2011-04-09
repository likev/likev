
#include"caipiao.h"

//------------------------------------------
void wenjiansr(int b[][7])           //子函数读取文件，将值赋给数组b[][7].
{                                                //字符串s代表文件名，注意应写出格式名.txt。
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
}
