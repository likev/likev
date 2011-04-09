//---------------------------
#include<iostream>
#include<cmath>
using namespace std;

double f(double x)
{  return 3*x+4*x*x+sin(x);  }               //函数形式

double Trape(double a,double b)
{  return (f(a)+f(b))*(b-a)/2;  }   //梯形公式    1次代数精度

double MidRect(double a,double b)
{  return (b-a)*f((a+b)/2); }       //中矩形公式  1次代数精度

double Simpson(double a,double b)
{  return ( f(a)+4*f((a+b)/2)+f(b) )*(b-a)/6; }   //辛普生公式 3次代数精度

double NewtCot(double a,double b)
{  return ( 7*(f(a)+f(b)) + 32*( f((3*a+b)/4)+f((a+3*b)/4) )
		   +12*f((a+b)/2) )*(b-a)/90; }          //四阶牛顿-柯特斯公式 4次代数精度
		    
double Gauss(double a,double b)
{  return ( f( (a+b)/2-(b-a)/3.464 ) 
		   + f( (a+b)/2+(b-a)/3.464 ) )*(b-a)/2; }     //二点高斯公式 3次代数精度

//---------------------------
int main()
{

	cout<<Trape(0,10)<<ends<<MidRect(0,10)<<ends
		<<Simpson(0,10)<<ends<<NewtCot(0,10)<<ends<<Gauss(0,10)<<endl;
}