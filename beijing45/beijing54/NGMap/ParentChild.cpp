#include "../CommonTools/StringTools.h"
#include "ParentChild.h"
#include "CHSStdioFile.h"
#pragma warning(disable:4996)

CParentChildFile::CParentChildFile(const char* pszFileName)
{
	m_Readfile.open(pszFileName, std::ios_base::in);
	m_bFileOK = m_Readfile.good();
}

CParentChildFile::~CParentChildFile(void)
{
	if (m_bFileOK)
	{
		m_Readfile.close();
	}
}

bool CParentChildFile::GetElementString(const char* pszParent,const char* pszChild,std::string &strLine)
{
	bool bFind = false;

	if (m_bFileOK)
	{
		//读取行数据的临时存放空间
		const int nLineLen = 2048;
		char szLine[nLineLen];		
		m_Readfile.seekg( 0, std::ios_base::beg );	//到文件头

		//如果没有到文章的结束，就一直读 
		while(!m_Readfile.eof())
		{
			if(m_Readfile.getline(szLine, nLineLen).good())
			{			
				strLine = szLine;
				if(strLine.find(pszParent) != std::string::npos)
				{
					bFind = true;
					break;
				}				
			}
			else
			{
				break;
			}
		}
		
		if (bFind)					//定位到文件中的  pszParent
		{
			bFind = false;		
			while(!m_Readfile.eof())
			{
				if(m_Readfile.getline(szLine, nLineLen).good())
				{			
					strLine = szLine;
					if(strLine.find(pszChild) != std::string::npos)
					{
						bFind = true;
						//2010.10.11 定位到 ) 字符例如(cstring)
						std::basic_string <char>::size_type  nStart = strLine.rfind(')');	
						strLine = strLine.substr(nStart + 1, strLine.length() - nStart -1);
						
						//2013.7.8
						//Linux下遇到"\r\n",将其转成"\r"放置到szLine中,所以需要将 \r 也删除掉
						stringTrimA(strLine, '\r');

						//去除前后的空格
						stringTrimA(strLine, ' ');

						//2010.10.11,如果是字符"\",则需要读取下一行
						if (strLine == "\\")
						{
							m_Readfile.getline(szLine, nLineLen);
							strLine = szLine;
							stringTrimA(strLine, '\r');
							stringTrimA(strLine, ' ');
						}
						break;
					}				
				}
				else
				{
					break;
				}				
			}			
		}
	}

	return bFind;
}

bool CParentChildFile::MoveToElement(const char* pszParent,const char* pszChild)
{
	bool bFind = false;

	if (m_bFileOK)
	{
		const int nLineLen = 2048;
		char szLine[nLineLen];		
		m_Readfile.seekg( 0, std::ios_base::beg );	//到文件头

		//如果没有到文章的结束，就一直读 
		while(!m_Readfile.eof())
		{
			if(m_Readfile.getline(szLine, nLineLen).good())
			{
				std::string strLine = szLine;
				if(strLine.find(pszParent) != std::string::npos)
				{
					bFind = true;
					break;
				}				
			}
			else
			{
				break;
			}
		}

		if (bFind)					//定位到文件中的  pszParent
		{
			bFind = false;		
			while(!m_Readfile.eof())
			{
				if(m_Readfile.getline(szLine, nLineLen).good())
				{
					std::string strLine = szLine;
					if(strLine.find(pszChild) != std::string::npos)
					{
						bFind = true;						
						break;
					}				
				}
				else
				{
					break;
				}				
			}			
		}
	}		

	return bFind;
}

void CParentChildFile::GetElement(const char* pszParent, const char* pszChild, int &ElementValue)
{
	ElementValue = 0;

	std::string strLine; 
	if (GetElementString(pszParent,pszChild,strLine))
	{
        sscanf(strLine.c_str(),"%d",&ElementValue);
		//ElementValue = atoi(strLine.c_str());
	}
}

void CParentChildFile::GetElement(const char* pszParent, const char* pszChild, long &ElementValue)
{
	ElementValue = 0;

	std::string strLine;  
	if (GetElementString(pszParent,pszChild,strLine))
	{
        int nTemp = 0;
        sscanf(strLine.c_str(),"%d",&nTemp);
        ElementValue = nTemp;
		//ElementValue = atol(strLine.c_str());
	}
}

void CParentChildFile::GetElement(const char* pszParent, const char* pszChild, double &ElementValue)
{
	ElementValue = 0.0;

	std::string strLine; 
	if (GetElementString(pszParent,pszChild,strLine))
	{
        sscanf(strLine.c_str(),"%lf",&ElementValue);
		//ElementValue = atof(strLine.c_str());
	}
}


void CParentChildFile::GetElement(const char* pszParent, const char* pszChild, std::string &ElementValue)
{
	ElementValue = "";
	std::string strLine; 
	if (GetElementString(pszParent,pszChild,strLine))
	{
		std::basic_string<char>::size_type nStart = 0;
		std::basic_string<char>::size_type nEnd = 0;
		nStart = strLine.find('\"');
		nEnd = strLine.rfind('\"');
		if (nStart != std::string::npos && nEnd != std::string::npos && nStart < nEnd)
		{
			ElementValue = strLine.substr(nStart + 1,nEnd-nStart-1);
		}
		else
		{
			ElementValue = strLine;
		}
	}
}
