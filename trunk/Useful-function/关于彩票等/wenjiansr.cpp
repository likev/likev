
#include"caipiao.h"

//------------------------------------------
void wenjiansr(int b[][7])           //�Ӻ�����ȡ�ļ�����ֵ��������b[][7].
{                                                //�ַ���s�����ļ�����ע��Ӧд����ʽ��.txt��
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
