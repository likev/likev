//-------求范围内的素数---------------
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;
//----------------------------

void out_prime(unsigned end_range)
{
	std::vector<unsigned> primes;

	unsigned count=0;

	for(unsigned n=2; n <= end_range; n++)
	{
		bool is_prime = true;

		for(unsigned index=0;index != primes.size(); index++)
		{
			unsigned m = primes[index];
			if( m <= unsigned(std::sqrt(double(n)) ) )
			{
				if(!(n%m))
				{
					is_prime = false;break;
				}
			}
			else break;

		}

		if(is_prime)
		{
			primes.push_back(n);
			
			std::cout.width(8);
			std::cout<<n;
			if(!(++count % 100)) std::cout<<endl;
			
		}
	}
	cout<<endl;

}
/*
int main()
{
	unsigned m=1;
	while(m)
	{
		out_prime(m);
		std::cin>>m;
	}

}
*/