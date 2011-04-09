
#include "comn.h"
#include "http-deal.h"

int main()
{
	using namespace std;
	
	CInternetSession session(_T("Mozilla/5.0 (Windows; U; Windows NT 5.1; zh-CN; rv:1.9.2) Gecko/20100115 Firefox/3.6"),
								1,
								PRE_CONFIG_INTERNET_ACCESS,
								NULL,
								NULL,
								INTERNET_FLAG_DONT_CACHE

		);
	

	DWORD value;
	session.QueryOption(INTERNET_OPTION_FROM_CACHE_TIMEOUT,value);
	cout<<value;
}

