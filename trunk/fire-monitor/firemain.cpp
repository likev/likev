
//�𾯼�����ļ�

#include "firewarning.h"

HANDLE hMutex=CreateMutex(NULL,FALSE,NULL);
char tdquit=0;

int main()
{
	LYname s;
	CTime lastTime;

	cout<<"��������2.1  �����2011��10��3��\n\n"
		     "������������кõ����������վ grow.sinaapp.com ��������\n"
			 "-----------------------------------------------------------------\n\n";

	//dealfire("�� ��","bas txt");
	//return 0;

	while(1)
	{
		cout<<"���ڼ��......   ��ǰʱ��:"<<CTime::GetCurrentTime().Format("%c").GetBuffer()<<endl<<endl;
		if(FtpConnect(lastTime))
		{
			Sleep(1000*60*10); //10���Ӽ��һ��
		}
		else
		{
			cout<<"��¼������ʧ�� ����1���Ӻ����µ�¼"<<endl;
			cout<<"-----------------------------------------------------------------\n\n";
			Sleep(1000*60);//1���Ӻ����¼��
		}
	}
}

