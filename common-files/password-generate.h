#include "comn.h"

#ifndef _PASSWORD_GENERATE_
#define _PASSWORD_GENERATE_

class password
{
	std::string pwstr;

public:
	password()
	{
		pwstr="";
	}
	password(std::string ps)
	{
		setpw(ps);
	}

	std::string getpw()
	{
		return pwstr;
	}
	
	void setpw(std::string ps)
	{
		for(size_t i=0;i<ps.size();i++)
		{
			if(ps[i]>126)
				ps[i]=126;
			else if(ps[i]<33)
				ps[i]=33;
		}
		pwstr = ps;
	}

	std::string& operator ++()
	{
		char c=33;
		if(!pwstr.size()) 
		{
			setpw(std::string(1,c));
			return pwstr;
		}

		size_t pos = pwstr.size()-1;

		for(size_t i=pos;i>=0;i--)
		{
			if(pwstr[i]!=126)
			{
				pwstr[i]++;
				break;
			}
			else
			{
				pwstr[i] = c;
			}
			if(i==0)
			{
				std::string ps(pwstr.size()+1,c);
				setpw(ps);
				break;
			}

		}

		return pwstr;
	}
};

#endif  /* _PASSWORD_GENERATE_ */