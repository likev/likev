//指定范围随机数生成函数
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

//参数为最小值 最大值 生成个数 输出文件名等
void rand_range(int min, int max, int n, const char * file_name)
{
	if(min>max)//调整最大最小值顺序
	{
		int t=min; min=max; max=t;
	}

	int min_new=min,max_new=max;
	bool range_change=false;

	if(min<0)//调整最大最小值范围
	{
		min_new = 0;
		max_new =max - min;
		range_change=true;
	}

	ofstream fout(file_name);


	srand( unsigned(time(0)) );//利用系统时间做随机数出发点
	for(int i=0;i<n;)//i 表示已生成成功的次数
	{
		int m=0, b=max_new/RAND_MAX;  //扩大几倍
		
		m=rand()%(b+1);
		int resl=m*RAND_MAX + rand();
		if(min_new <= resl && resl <= max_new) //符合条件
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