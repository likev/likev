//վ����Ϣ�Լ�����״������

#include "stdafx.h"
#include <map>

#ifndef SETINFO_WETH
#define SETINFO_WETH

using std::map;using std::string;using std::vector;

class SetInfo{

public:
	//վ����Ϣ
	map<int,string> stname;

	//����״��
	map<string,string> weth;

	//�������
	map<string,string> windx,windv;

	SetInfo(void)
	{
		stname[57073] = "��������"; stname[57099] = "����";stname[57071] = "�Ͻ�";
		stname[57076] = "��ʦ";       stname[57074] = "����";stname[57078] = "����";
		stname[57070] = "�°�";       stname[57065] = "����";stname[57066] = "����";
		stname[57162] = "����";       stname[57077] = "�ﴨ";


		weth["0.0"] = "����"; 
		weth["1.0"] = "����"; 
		weth["2.0"] = "����"; 
		weth["3.0"] = "����"; 
		weth["4.0"] = "������"; 
		weth["5.0"] = "�������"; 
		weth["6.0"] = "���ѩ"; 
		weth["7.0"] = "С��"; 
		weth["8.0"] = "����"; 
		weth["9.0"] = "����"; 
		weth["10.0"] = "����"; 
		weth["11.0"] = "����"; 
		weth["12.0"] = "�ش���"; 
		weth["13.0"] = "��ѩ"; 
		weth["14.0"] = "Сѩ"; 
		weth["15.0"] = "��ѩ"; 
		weth["16.0"] = "��ѩ"; 
		weth["17.0"] = "��ѩ"; 
		weth["18.0"] = "��"; 
		weth["19.0"] = "����"; 
		weth["20.0"] = "ɳ����"; 
		weth["29.0"] = "����"; 
		weth["30.0"] = "��ɳ";  



		windx["0.0"] = "����";
		windx["1.0"] = "����";
		windx["2.0"] = "��";
		windx["3.0"] = "����";
		windx["4.0"] = "��";
		windx["5.0"] = "����";
		windx["6.0"] = "��";
		windx["7.0"] = "����";
		windx["8.0"] = "��";
		windx["9.0"] = "��ת��";

		windv["0.0"] = "С�ڵ���3��";
		windv["1.0"] = "3-4��";
		windv["2.0"] = "4-5��";
		windv["3.0"] = "5-6��";
		windv["4.0"] = "6-7��";
		windv["5.0"] = "7-8��";
		windv["6.0"] = "8-9��";
		windv["7.0"] = "9-10��";
		windv["8.0"] = "10-11��";
		windv["9.0"] = "11-12��";
	}
};

class StnName{
public:
	//վ����Ϣ
	vector<string> nm;

	StnName()
	{
		nm.assign(11,"");
		nm[0] = "��������"; nm[1] = "����";nm[2] = "�Ͻ�";
		nm[3] = "��ʦ";       nm[4] = "����";nm[5] = "����";
		nm[6] = "�°�";       nm[7] = "����";nm[8] = "����";
		nm[9] = "����";       nm[10] = "�ﴨ";
	}
};


#endif