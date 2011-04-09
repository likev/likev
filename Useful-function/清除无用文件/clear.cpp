#include<cstdio>
#include<iostream>
#include<string>
using namespace std;

int main()
{
	char s[]="D:\\My Documents\\chengxu\\Useful function\\清除无用文件\\clear.plg";

	if(remove(s))
	cout<<"Can not delete!\n";
}