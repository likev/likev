
#include "contour_fill.h"
#include <file-str.h>
#include <string-trans.h>
#include <sstream>

contour_fill::contour_set readdata()
{
	using namespace std;

	string filecont;

	filetostr("files/contourdata.txt", filecont);

	str_trim(filecont);

	vector<string> linestr;

	str_split(filecont,";",linestr);

	contour_fill::contour_set contourlines(linestr.size());

	for(vector<string>::iterator it=linestr.begin();
		it != linestr.end(); it++)
	{
		str_trim(*it);
		istringstream ssin(*it);

		string pointstr;
		while(getline(ssin,pointstr))
		{
			istringstream ssin2(pointstr);

			contour_fill::pointtype pointd;

			if(ssin2>>pointd.x>>pointd.y)
			{
				contourlines[it-linestr.begin()].push_back(pointd);
			}
		}

	}

	return contourlines;

}

