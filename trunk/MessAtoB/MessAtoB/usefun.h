//�������õ��Ĺ��ܺ�������


#pragma once
#include "stdafx.h"

//���ı����ݶ����ַ���str
std::string & filetostr(std::string file,std::string & str);

bool strtofile(std::string file,const std::string & str);

//��ʵ��a����lλС��(��������) Ȼ��ת��Ϊ�ַ���
std::string dtos(double a, int l=1);
