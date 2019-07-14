#pragma once
#ifdef SPLITE_EXPORTS
#define SPLITE_API __declspec(dllexport)
#else
#define SPLITE_API __declspec(dllimport)

#endif
#include <vector>
