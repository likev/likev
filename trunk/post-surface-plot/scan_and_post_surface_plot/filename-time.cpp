#include "filename-time.h"

bool time_less_than(const FilenameTime &left,const FilenameTime &right)
{
	return left.get_time() < right.get_time();
}