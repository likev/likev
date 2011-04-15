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
	primes.push_back(2);
	cout<<2;

	for(unsigned n=3; n != end_range; n++)
	{
		bool is_prime = true;

		for(unsigned index=0;index != primes.size(); index++)
		{
			int m = primes[index];
			if( m <= int(std::sqrt(double(n)) ) )
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
			std::cout.width(8);
			std::cout<<n;
			primes.push_back(n);
		}
	}

}

int main()
{
	out_prime(10e5);

}