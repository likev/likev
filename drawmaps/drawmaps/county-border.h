
#include "contr.h"


class county_border
{
public:
	typedef contr::pointxy<double> point_type;
public:
	std::string name;
	point_type location;
	std::vector<point_type> line;
};