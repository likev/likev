//��վ��ʱЧԤ������

#include <string>
#include <vector>

#ifndef SGLF
#define SGLF

using std::vector;
using std::string;

class sglf{

public:
	int stn,fcn,ele; 
	double lon,lat,h;

	//�Ը����ʹ洢���� ����ͳ�Ʒ���
	vector<vector<double> > f;

	bool init(string snum, const string& sfile);

};



#endif