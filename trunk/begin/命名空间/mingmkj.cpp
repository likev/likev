//!!!----C++��Ĭ�����������ռ�std�н��еġ���
//һ�㲻������using std::cout,using std::ios�ȡ�

#include<iostream.h>
//----------------------
namespace B{int t=10;}

namespace A
{
	int x=1;
    int y=2;
}
int main()
{
	using namespace A;
	int a=x;
	cout<<"a="<<a<<endl;
	int b=y;
	int c=B::t;
	cout<<"b="<<b<<endl<<"c="<<c<<endl;

}