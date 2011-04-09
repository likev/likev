#include <iostream>
#include <ctime>

using namespace std;

void speed(void);

int main()
{
	clock_t time = clock();
	speed();
	time = clock()-time;
	cout<<ends<<time<<endl;

	return 0;//·µ»Ø
}