#include <comn.h>
#include <string-trans.h>

int main()
{
	using namespace std;
	std::string stra="abcde\\��he.txt";
	wchar_t strb[]=L"abcde\\��he.txt"; 

	std::wstring strc;
	AnsiToUtf16(stra,strc);

	string str;

	std::ifstream fin(strc.c_str());

	if(fin.is_open())
	{
		cout<<"good"<<endl;
		fin.close();
	}
	filetostr(stra,str);
}

