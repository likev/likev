#include<fstream>
#include<iostream>
using namespace std;
extern const int M;
extern const int N;

#ifndef _CAIPIAO_H
#define _CAIPIAO_H

void shuchuhlq(int a[][49]);//------------------------------输出红蓝球的号码
void wenjiansr(int b[][7]);//-------------------从文件输入数据给数组b  
void jisuancishu(int a[][49],int b[][7]);//--------------计算每个数出现的次数
void lanqiujiange(int b[][7]);
void hongqiujiange(int b[][7]);
void fenqu11(int b[][7]);
void qiuyu11(int b[][7]);
void lan4fq(int b[][7]);
void lan4qy(int b[][7]);

#endif

