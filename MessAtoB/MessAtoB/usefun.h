//程序中用到的功能函数声明
#include "stdafx.h"

#pragma once

//将文本内容读入字符串str
std::string & filetostr(std::string file,std::string & str);

bool strtofile(std::string file,const std::string & str);

//将实数a保留l位小数(四舍五入) 然后转化为字符串
std::string dtos(double a, int l=1);

//获取当前处于哪个时间段
int whent(void);

//处理数据并储存
bool dealdata(std::vector<std::vector<std::string>  > &weth,
			  std::vector<std::vector<double>  > &teph);
void dealfhead(std::string & fhead);
std::string dealf121();
std::string dealfile(const std::vector<std::vector<std::string>  > &weth,
			  const std::vector<std::vector<double>  > &teph, const int wht);
bool FtpConnect(const int wht);