#include <iostream>

class outNum{
public:
	outNum()
	{
		int a;
		std::cin>>a;
		std::cout<<a<<std::endl;
	}
};
int run()
{
	std::cout<<"run\n";
	return 0;
}

int main()
{
	std::cout<<"begin\n";
	return 0;
}
outNum a;
int m=run();