// sample_multithread_c_program.c
// compile with: /c
//
//  Bounce - Creates a new thread each time the letter 'a' is typed.
//  Each thread bounces a happy face of a different color around
//  the screen. All threads are terminated when the letter 'Q' is
//  entered.
//

#include <afxwin.h>
#include <iostream>

#include <string>

using namespace std;

UINT MyThreadProc( LPVOID pParam )
{
    if (pParam == NULL)
    return 1;   // if pObject is not valid

    // do something with 'pObject'

	for(int i=0;i<100;i++)
	{
		cout<<'a';
		Sleep(100);
	}

	
    return 0;   // thread completed successfully
}

UINT MyThreadProc2( LPVOID pParam )
{
    if (pParam == NULL)
    return 1;   // if pObject is not valid

    // do something with 'pObject'

	for(int i=0;i<100;i++)
	{
		cout<<'b';
		Sleep(100);
	}

	
	
    return 0;   // thread completed successfully
}

int main()
{
	char *pNewObject1 ="a", *pNewObject2 ="b", *pNewObject3 ="c";
	
	AfxBeginThread(MyThreadProc, ( LPVOID)pNewObject1);
	AfxBeginThread(MyThreadProc2, pNewObject2);
	//AfxBeginThread(MyThreadProc, pNewObject3);

	cin>>pNewObject1;

}