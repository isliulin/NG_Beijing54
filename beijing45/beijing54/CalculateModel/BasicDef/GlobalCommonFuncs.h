#ifndef __BASICDEF_GLOBALCOMMONFUNCS_h
#define __BASICDEF_GLOBALCOMMONFUNCS_h

//ȥ��tstringǰ����ض��ַ�
void TstringTrim(tstring& inString, TCHAR chTarget=_T(' '));

//�Ƚ�����string���Ĺ�ϵ --���Դ�Сд
int Cmp_nocase(const tstring& str1, const tstring& str2);

//�����е�ֵ��Ϊ��д
void TstringMakeUpper(tstring& inoutString);

//�����е�ֵ��Ϊ��д
void AstringMakeUpper(std::string& inoutString);

//�����е�ֵ��Ϊ��д
void WstringMakeUpper(std::wstring& inoutString);

tstring s2ts(const std::string& s);

std::string ts2s(tstring& inputws);


#endif