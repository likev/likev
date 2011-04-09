//---------------------------
#include<fstream.h>
int const M=62,N=4,H1=4,H2=12;
//---------------------------
int main()
{
	int a[80][4]={0};
	int p1=0,p2=0,p3=0,p4=0;	
	
	ifstream fin("text.txt");
	if(!fin)
	{ cout<<"Can not open input file.\n";
	  return;
	}

	for(int i=0;i<M;i++)
	{
		fin>>a[i][0]>>a[i][1]>>a[i][2]>>a[i][3];

	}

//-------------------------------------------
    for(i=H1;i<H2;i++)
	{		
		if(a[i][0]==1 && a[i][1]==1)  p1++;
		if(a[i][0]==1 && a[i][1]==2)  p2++;
        if(a[i][0]==2 && a[i][1]==1)  p3++;
        if(a[i][0]==2 && a[i][1]==2)  p4++;
	}
    
	cout<<"------------从最近第"<<H1<<"期至第"<<H2<<"期数据统计如下：--------------\n";
	cout<<"大大共有p1=="<<p1<<endl;
    cout<<"大小共有p2=="<<p2<<endl;
	cout<<"小大共有p3=="<<p3<<endl;
	cout<<"小小共有p4=="<<p4<<endl;



}