

#include <string>
#include <vector>
#include <iostream>
	
using namespace std;

class LYname
{
public:
	vector<string> a;

	LYname()
	{
		char * b[10]={"ÂåÑô","èï´¨","ÂåÄş","ÃÏ½ò","ÈêÑô","áÔÏØ","ĞÂ°²","ÒÁ´¨","ÙÈÊ¦","ÒËÑô"};

		a.assign(b,b+10);
	}

	void out(void)
	{
		for(size_t i=0;i<a.size();i++)
		{
			cout<<a[i]<<"   ";
		}
		cout<<endl;
	}
};