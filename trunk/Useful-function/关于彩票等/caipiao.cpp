//---------��Ʊ������----------
#include"caipiao.h"
const int M=0,N=400;
//----------------------------------------------
int main()
{
	int a[2][33+16]={0};         //a[0][i]������������
	int b[N][7]={0};            //a[1][0]-----a[32]���������ֵĴ���,
	shuchuhlq(a);              //a[1][33]-----a[48]����������ֵĴ���
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






	





