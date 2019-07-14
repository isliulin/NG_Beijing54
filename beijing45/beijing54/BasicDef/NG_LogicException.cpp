#include "NG_LogicException.h"

NG_LogicException::NG_LogicException(const std::string &error_message):logic_error(error_message)
{
	errorCode = -1;
}

NG_LogicException::NG_LogicException(int error_code, const std::string &error_message):logic_error(error_message)
{
	errorCode = error_code;
}

NG_LogicException::~NG_LogicException(void)
{
}

