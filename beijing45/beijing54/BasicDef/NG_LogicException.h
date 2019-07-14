#pragma once

#include <stdexcept>
#include <string>

class NG_LogicException : public std::logic_error
{
private:
	int errorCode;
public:
	NG_LogicException(const std::string &error_message);
	NG_LogicException(int error_code, const std::string &error_message);
	~NG_LogicException(void);

	void setErrorCode(int error_code)
	{
		errorCode = error_code;
	}

	int getErrorCode(void )
	{
		return errorCode;
	}
};
