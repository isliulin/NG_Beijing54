#pragma once
#pragma once
#ifdef BIN_EXPORTS
#define BINFILEREADER_API __declspec(dllexport)
#else
#define BINFILEREADER_API __declspec(dllimport)
#endif
