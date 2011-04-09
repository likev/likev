//ָ����Χ��������ɺ���
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//����Ϊ��Сֵ ���ֵ ���ɸ��� ����ļ�����
void rand_range(int min, int max, int n, const char * file_name)
{
	if(min>max)//���������Сֵ˳��
	{
		int t=min; min=max; max=t;
	}

	int min_new=min,max_new=max;
	bool range_change=false;

	if(min<0)//���������Сֵ��Χ
	{
		min_new = 0;
		max_new =max - min;
		range_change=true;
	}

	ofstream fout(file_name);


	srand( unsigned(time(0)) );//����ϵͳʱ���������������
	for(int i=0;i<n;)//i ��ʾ�����ɳɹ��Ĵ���
	{
		int m=0, b=max_new/RAND_MAX;  //���󼸱�
		
		m=rand()%(b+1);
		int resl=m*RAND_MAX + rand();
		if(min_new <= resl && resl <= max_new) //��������
		{
			i++;
			if(range_change)
			{
				fout<<resl+min<<endl;
			}
			else
			{
				fout<<resl<<endl;
			}
		}
	}

}