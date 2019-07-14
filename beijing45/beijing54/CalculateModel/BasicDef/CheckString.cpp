#include <sstream>
#include "CheckString.h"

using namespace std;


bool ISNumber_CheckString(char* str)
{
	stringstream num(str);
	double data;
	char ch;
	if(!(num>>data))
	{
		return false;
	}

	if (num>>ch)
	{
		return false;
	}

	return true;
}