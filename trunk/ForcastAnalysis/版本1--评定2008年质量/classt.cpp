class m
{
public:
	int a;

};

m getm()
{
	m s;
	s.a=0;

	return s;
}

int ifelse(int m)
{
	if(m<10)
		return 5;
	else if(m<20)
		return 15;
	else if(m<30)
		return 25;
	else if(m<40)
		return 35;
	else if(m<50)
		return 45;
	else
		return 55;
}

int biaoda(int m)
{
	return m<10 ? 5
		:  m<20 ? 15 
		:  m<30 ? 25
		:  m<40 ? 35
		:  m<50 ? 45
		:  55;
}