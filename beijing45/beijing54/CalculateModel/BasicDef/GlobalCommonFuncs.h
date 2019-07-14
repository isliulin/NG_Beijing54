#ifndef __BASICDEF_GLOBALCOMMONFUNCS_h
#define __BASICDEF_GLOBALCOMMONFUNCS_h

//去除tstring前后的特定字符
void TstringTrim(tstring& inString, TCHAR chTarget=_T(' '));

//比较两个string串的关系 --忽略大小写
int Cmp_nocase(const tstring& str1, const tstring& str2);

//将串中的值变为大写
void TstringMakeUpper(tstring& inoutString);

//将串中的值变为大写
void AstringMakeUpper(std::string& inoutString);

//将串中的值变为大写
void WstringMakeUpper(std::wstring& inoutString);

tstring s2ts(const std::string& s);

std::string ts2s(tstring& inputws);


#endif