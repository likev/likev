
#ifndef HTTP_DEAL
#define HTTP_DEAL

#include <comn.h>
#include <afxinet.h>

bool DownloadHttpPage(LPCTSTR pszServerName, LPCTSTR pszURL, LPCTSTR pszLocalFile);
void PostHttpPage(LPCTSTR pszServerName, LPCTSTR pszURL, std::string optional, LPCTSTR pszLocalFile);

//�ж��Ƿ�����
int Fun_InternetGetConnectedState();

#endif  //HTTP_DEAL