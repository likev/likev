void speed()
{
	double t=1;
	for(int i=1;i<1e9;i++)
	{
		//cout<<"                     \r"<<i<<"  "<<t;
		t *= i;
		if(t>1e9) t =1;
	}
}