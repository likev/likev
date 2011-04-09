//---------彩票主程序----------
#include"caipiao.h"
const int M=0,N=400;
//----------------------------------------------
int main()
{
	int a[2][33+16]={0};         //a[0][i]代表红球和蓝球
	int b[N][7]={0};            //a[1][0]-----a[32]代表红球出现的次数,
	shuchuhlq(a);              //a[1][33]-----a[48]代表篮球出现的次数
	wenjiansr(b);
	jisuancishu(a,b);
	lanqiujiange(b);
	hongqiujiange(b);

	lan4fq(b);
	lan4qy(b);
	fenqu11(b);
	qiuyu11(b);

	cin.get();
}






	





