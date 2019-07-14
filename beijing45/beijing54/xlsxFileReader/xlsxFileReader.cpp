#include "pch.h"
#include "xlsxFileReader.h"
#include <iostream>
#include <windows.h>
#include "libxl.h"


using namespace libxl;

excel::excel(const char* fileName,int sheetId,int functionId) 
{
	if (fileName == NULL)
	{
		printf("Name Is ERROR!");
		return;
	}
	
	const char* cstr = fileName;
	int len = MultiByteToWideChar(CP_ACP, 0, cstr, strlen(cstr), NULL, 0);

	wchar_t* wstr = new wchar_t[len + 1];

	MultiByteToWideChar(CP_ACP,0,cstr, strlen(cstr),wstr, len);
	wstr[len] = '\0';
	book = xlCreateXMLBook();
	book->setKey(L"Halil Kural", L"windows-2723210a07c4e90162b26966a8jcdboe");
	book->load(wstr);
	if (!book) 
	{
		printf("Init Book Fail!");
	}
	else 
	{
		printf("Init Book Successful!\n");
		int count = book->sheetCount();
		printf("%d\n",count);
	}
	if (functionId == 1) // 1 : query ,  2 : Insert 
	{
		sheet = book->getSheet(sheetId);
	}
	else if (functionId == 2) 
	{
		sheet = book->addSheet(L"sheet1");
	}
	if (!sheet)
	{
		printf("Init Sheet Fail!");
	}
	
}
int excel::readnumInt(int row , int col) 
{
	int result = sheet->readNum(row,col);
	return result;
}

double excel::readnumDouble(int row, int col)
{
	double result = sheet->readNum(row, col);
	return result;
}

std::string excel::readnumString(int row ,int col) 
{
	const wchar_t*str = sheet->readStr(row, col);
	int len = WideCharToMultiByte(CP_ACP, 0, str, wcslen(str), NULL, 0, NULL, NULL);
	char *newString = new char[len + 1];
	WideCharToMultiByte(CP_ACP, 0, str, wcslen(str), newString, len, NULL, NULL);
	std::string result = newString;
	return result;

}

int excel::getColNum() 
{
	
	return sheet->lastCol();
}
int excel::getRowNum()
{
	return sheet->lastRow();
}