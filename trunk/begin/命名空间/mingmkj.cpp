//!!!----C++中默认是在命名空间std中进行的。故
//一般不用声明using std::cout,using std::ios等。

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