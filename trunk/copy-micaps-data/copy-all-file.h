
/*
   
*/

#ifndef COPY_FILE_
#define COPY_FILE_

#include <iostream>
#include "wx/dir.h"
#include "wx/wx.h"
#include "wx/filename.h"

class MyDirTrav:public wxDirTraverser
{
public:
	MyDirTrav(const wxString &dir_from,const wxString &dir_to)
	:dirFrom(dir_from),dirTo(dir_to)
	{	
	}
	wxDirTraverseResult OnFile(const wxString& filename)
	{
		wxString fullname = filename.substr(dirFrom.size());
		bool issuccess = ::wxCopyFile(filename,dirTo+fullname );
		//wxMessageBox(filename+wxT("-->")+dirTo+fullname);
		//std::cout<<"file: "<<filename.mb_str()<<"  copy "<<fullname.mb_str()<<"  "<<::wxCopyFile(filename,dirTo+fullname )<<std::endl;
		return wxDIR_CONTINUE;
	}
	
	wxDirTraverseResult OnDir(const wxString& dirname)
	{
		wxString fullname = dirname.substr(dirFrom.size());
		
		if(!::wxDirExists(dirTo+fullname) )
		{
			bool issuccess = ::wxMkdir(dirTo+fullname );
		}
		//std::cout<<"dir: "<<dirname.mb_str()<<"  make dir "<<fullname.mb_str()<<"  "<<::wxMkdir(dirTo+fullname )<<std::endl;
		return wxDIR_CONTINUE;
	}

private:
	wxString dirFrom, dirTo;
};

#endif /* COPY_FILE_ */
