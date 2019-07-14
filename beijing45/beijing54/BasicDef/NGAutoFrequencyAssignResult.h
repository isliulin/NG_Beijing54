#pragma once
#include <vector>
#include <string>
class CNGAutoFrequencyAssignResult
{
public:
	CNGAutoFrequencyAssignResult(void){}
	virtual ~CNGAutoFrequencyAssignResult(void){}
public:
	std::vector<std::string> StationIDs;
	std::vector<double>  Frequencys;

};
