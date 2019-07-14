#ifndef _CSV_H
#define _CSV_H


#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define DEFAULT_LINE_BUFFER_SIZE 1024

class Csv
{    // read and parse comma-separated values

public:
	//传入的fin需保证is_open返回true
    Csv(ifstream& fin , string sep = ",") : //fin已打开的csv文件流,sep分隔符
      fin(fin), fieldsep(sep),lineBufferSize(DEFAULT_LINE_BUFFER_SIZE) {}

      int getline(string&);//获取一行CSV数据
      string getfield(int n);//提取getline得到的一行CSV数据的指定列数的内容(n:0~(总列数-1）)
      int getnfield() const { return nfield; }//获取getline得到的一行CSV数据的总列数

private:
    ifstream& fin;            // input file pointer
    string line;            // input line
    vector<string> field;    // field strings
    int nfield;                // number of fields
    string fieldsep;        // separator characters
    int lineBufferSize;
    int split();
    int endofline(char);
    int advplain(const string& line, string& fld, int);
    int advquoted(const string& line, string& fld, int);
};

#if 0
class CsvWrite
{

public:
	CsvWrite(ofstream &fout,string sep = ","):mfout(fout),mfieldsep(sep),nfield(0)
	{}
    void CSVWriteHead(vector<string> head)
	{
	   nfield=head.size();
	   mHead=mCurrentRow=head;
	   CSVWriteNextRow();

	}
    //注T不包括CString
	template<class T>
	bool	CSVWriteColumn(int n, T data)
	{
		if(n>=nfield&&n<0)
		{
          return false;
		}
		std::stringstream ss;
		ss << data;
		
		mCurrentRow[n]	= ss.str();

		return true;
	}


	
	// 写接口
	void	CSVWriteNextRow()
	{
		
		for (vector<string>::iterator it	= mCurrentRow.begin();
			it != mCurrentRow.end(); it++)
		{
			std::string str = *it;
			*it = "";
			replace(str, "\"", "\"\""); //单引号变成双引号
	        if(NeedQuotation(str))
	        {
			  mfout << '"' << str << '"';
	        }
			else
			{
              mfout <<str ;
			}
			if (it + 1 != mCurrentRow.end())
			{
				mfout << mfieldsep;
			}
		}
	
		mfout << std::endl;
	}

	int  GetFieldColumn(string& headfield)
	{  
	   int i=-1;
	   vector<string>::iterator it;
       for ( it	= mHead.begin();it != mHead.end(); it++)
		{  
		   i++;
          if((*it)==headfield)
          	{
              break;
          	}
		}
	   
        if(it!= mHead.end())
    	{
           return i;
    	}
	    return -1; 
	}
private:
	int replace(std::string& src_str, const std::string& old_str, const std::string& new_str)
	{
		int	count	= 0;
		int old_str_len	= int(old_str.length());
		int new_str_len	= int(new_str.length());
		int	pos	= 0;
		while((pos=int(src_str.find(old_str,pos)))!=std::string::npos)
		{
			src_str.replace(pos,old_str_len,new_str);
			pos+=new_str_len;
			++count;
		}
		return count;
	} 
	bool NeedQuotation(const std::string& str)
	{
      const char* c_str=str.c_str();
	  if(c_str)
	  { 
	    int i=0; 
        while(*(c_str+i)!='"'&&*(c_str+i)!='\r'&&*(c_str+i)!=','&&*(c_str+i)!='\0')
        {
          i++;
        }
        if(i!=strlen(c_str))
        {
          return true;
        }
		
	  }

	  return false;
	}
private:
	ofstream &mfout;
	string mfieldsep;// separator characters
	int nfield;
	vector<string> mCurrentRow;
    vector<string> mHead;
 };
#endif

class CsvWrite
{

public:
	CsvWrite(string filename,string sep = ","):mfieldsep(sep),nfield(0)
	{ 
	  mfout=fopen(filename.c_str(),"w");
	}
	~CsvWrite()
	{
      if(mfout)
      {
        fclose(mfout);
      }
	}
	//写表头
    void CSVWriteHead(vector<string> head)
	{
	   nfield=head.size();
	   mHead=mCurrentRow=head;
	   CSVWriteNextRow();

	}
    //注T不包括CString
    //插入当前行的某列数据
    //n从0开始
	template<class T>
	bool	CSVWriteColumn(int n, T data)
	{   
	    if(mfout==0)
    	{
          return false;
    	}
		if(n>=nfield&&n<0)
		{
          return false;
		}
		std::stringstream ss;
		ss << data;
		
		mCurrentRow[n]	= ss.str();

		return true;
	}

    //放弃当前行已写的数据
	void   CSVClearRow()
	{
       	if(mfout==0)
		{
          return ;
		}
		for (vector<string>::iterator it	= mCurrentRow.begin();
			it != mCurrentRow.end(); it++)
		{
			*it = "";
		}

	}
	
	// 将当前行的数据写入文件，准备下一行数据
	void	CSVWriteNextRow()
	{
		if(mfout==0)
		{
          return ;
		}
		for (vector<string>::iterator it	= mCurrentRow.begin();
			it != mCurrentRow.end(); it++)
		{
			std::string str = *it;
			*it = "";
			replace(str, "\"", "\"\""); //单引号变成双引号

	        if(NeedQuotation(str))
	        { 
	          //表项需要加双引号
			  fwrite("\"",1,1,mfout);
			  fwrite(str.c_str(),strlen(str.c_str()),1,mfout);	
			  fwrite("\"",1,1,mfout);
	        }
			else
			{
               fwrite(str.c_str(),strlen(str.c_str()),1,mfout);	
			}
			if (it + 1 != mCurrentRow.end())
			{
                //加分隔符
				fwrite(mfieldsep.c_str(),strlen(mfieldsep.c_str()),1,mfout);	
			}
		}
	
		fwrite("\n",1,1,mfout);
	    fflush(mfout);
	}
    //查询表头所在的列(从0开始，-1不存在对应的表头)
	int  GetFieldColumn(string& headfield)
	{  
	   int i=-1;
	   vector<string>::iterator it;
       for ( it	= mHead.begin();it != mHead.end(); it++)
		{  
		   i++;
          if((*it)==headfield)
          	{
              break;
          	}
		}
	   
        if(it!= mHead.end())
    	{
           return i;
    	}
	    return -1; 
	}
private:
	int replace(std::string& src_str, const std::string& old_str, const std::string& new_str)
	{
		int	count	= 0;
		int old_str_len	= int(old_str.length());
		int new_str_len	= int(new_str.length());
		int	pos	= 0;
		while((pos=int(src_str.find(old_str,pos)))!=std::string::npos)
		{
			src_str.replace(pos,old_str_len,new_str);
			pos+=new_str_len;
			++count;
		}
		return count;
	} 
	bool NeedQuotation(const std::string& str)
	{
      const char* c_str=str.c_str();
	  if(c_str)
	  { 
	    int i=0; 
        while(*(c_str+i)!='"'&&*(c_str+i)!='\r'&&*(c_str+i)!=','&&*(c_str+i)!='\0')
        {
          i++;
        }
        if(i!=strlen(c_str))
        {
          return true;
        }
		
	  }

	  return false;
	}
private:
	FILE *mfout;
	string mfieldsep;// separator characters
	int nfield;
	vector<string> mCurrentRow;
    vector<string> mHead;
 };



#endif
