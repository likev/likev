#include<cstdio>
#include<iostream>

int main()
{
	if(remove("clear.dsp"))
		std::cout<<"Can not delete!\n";
	else std::cout<<"OK!\n";
}