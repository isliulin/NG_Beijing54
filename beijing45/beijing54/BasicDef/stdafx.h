// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����

#include <Windows.h>
#include <string>
#include <tchar.h>
#ifdef  UNICODE 
typedef std::wstring tstring;
typedef std::wostringstream tostringstream;
#else
typedef std::string tstring; 
typedef std::ostringstream tostringstream;
#endif
