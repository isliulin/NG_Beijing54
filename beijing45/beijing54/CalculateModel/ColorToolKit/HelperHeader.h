#ifndef __HELPERHEADER__H_
#define __HELPERHEADER__H_
#include <string>
#include "ColorToolKit.h"

using namespace std;

void ToUpperString(string &str);
void ToLowerString(string &str);


DWORD ConvertStr2ColorData(const string &strColor);

#endif