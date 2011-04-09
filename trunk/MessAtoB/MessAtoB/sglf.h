//��վ��ʱЧԤ������

#include <string>
#include <vector>

#ifndef SGLF
#define SGLF

class Sglf{

public:
	int stn,fcn,ele; 
	double lon,lat,h;

	//�Ը����ʹ洢���� ����ͳ�Ʒ���
	std::vector<std::vector<double> > f;

	bool init(std::string snum, const std::string& sfile);
	bool israin(int hourspan)const
	{
		int n = hourspan/12;
		if(n>fcn)
		{
			return false;
		}
		n--;

		double rain_code = f[n][19];
		if((rain_code>2&&rain_code<18)
		 || rain_code == 19.0 )
		{
			return true;
		}
		return false;
	}

};



#endif