#include "isPointInRgn.h"
#include <iostream>
#include <fstream>

int main()
{
	double x1,y1;

	std::vector<mVector<double> > borderA,borderB;

	std::ifstream finA("in1.txt"), finB("in2.txt");

	while(finA>>x1>>y1)
	{
		borderA.push_back(mVector<double>(x1,y1) );
	}

	while(finB>>x1>>y1)
	{
		borderB.push_back(mVector<double>(x1,y1) );
		
	}
	
	std::cout<<isRgnInRgn(borderB, borderA)<<std::endl;
}