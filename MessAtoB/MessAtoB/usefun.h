//�������õ��Ĺ��ܺ�������
#include "stdafx.h"

#pragma once

//���ı����ݶ����ַ���str
std::string & filetostr(std::string file,std::string & str);

bool strtofile(std::string file,const std::string & str);

//��ʵ��a����lλС��(��������) Ȼ��ת��Ϊ�ַ���
std::string dtos(double a, int l=1);

//��ȡ��ǰ�����ĸ�ʱ���
int whent(void);

//�������ݲ�����
bool dealdata(std::vector<std::vector<std::string>  > &weth,
			  std::vector<std::vector<double>  > &teph);
void dealfhead(std::string & fhead);
std::string dealf121();
std::string dealfile(const std::vector<std::vector<std::string>  > &weth,
			  const std::vector<std::vector<double>  > &teph, const int wht);
bool FtpConnect(const int wht);