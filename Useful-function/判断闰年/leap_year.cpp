bool is_leapyear(int a)
{
	return ( !(a%400) ||  !(a%4) && a%100 );
}