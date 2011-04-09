//-------------------------------------
#include<iostream.h>
#include<ctime>
#include<conio.h>
//----------------------------------------
//  int const  CLK_TKE=1000;
class Watch
{
	double begin;
	double end;
public:
	Watch();
	Watch(clock_t);
	void Start();
	void Stop();
	void Show();
};

//------------------------------------------
Watch::Watch()
{
	begin=end=0.0;
}

//-----------------------------------------
Watch::Watch(clock_t t)
{
	cout<<"begin... \n";
	begin=(double)t/CLOCKS_PER_SEC;//ת�����롣
	end=0.0;
}
//-----------------------------------------
void Watch::Start()
{
	cout<<"begin....\n";
	begin=(double)clock()/CLOCKS_PER_SEC;  //����clock()������ʱ��������ĳ�������ʱ��
}
//-------------------------------------------
void Watch::Stop()
{
	end=(double)clock()/CLOCKS_PER_SEC;
	Show();
}
//---------------------------------------
void Watch::Show()
{
	cout<<"stop.\n Elapsed time:"<<(end-begin)<<"s\n";
}
//-------------------------------------------

int main()
{
	Watch s1;
//	getch();
	s1.Start();
	getch();
	s1.Stop();

	//---------------------------------
}

