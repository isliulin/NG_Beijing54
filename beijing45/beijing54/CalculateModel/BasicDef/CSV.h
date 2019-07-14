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
	//�����fin�豣֤is_open����true
    Csv(ifstream& fin , string sep = ",") : //fin�Ѵ򿪵�csv�ļ���,sep�ָ���
      fin(fin), fieldsep(sep),lineBufferSize(DEFAULT_LINE_BUFFER_SIZE) {}

      int getline(string&);//��ȡһ��CSV����
      string getfield(int n);//��ȡgetline�õ���һ��CSV���ݵ�ָ������������(n:0~(������-1��)
      int getnfield() const { return nfield; }//��ȡgetline�õ���һ��CSV���ݵ�������

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
    //עT������CString
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


	
	// д�ӿ�
	void	CSVWriteNextRow()
	{
		
		for (vector<string>::iterator it	= mCurrentRow.begin();
			it != mCurrentRow.end(); it++)
		{
			std::string str = *it;
			*it = "";
			replace(str, "\"", "\"\""); //�����ű��˫����
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
	//д��ͷ
    void CSVWriteHead(vector<string> head)
	{
	   nfield=head.size();
	   mHead=mCurrentRow=head;
	   CSVWriteNextRow();

	}
    //עT������CString
    //���뵱ǰ�е�ĳ������
    //n��0��ʼ
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

    //������ǰ����д������
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
	
	// ����ǰ�е�����д���ļ���׼����һ������
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
			replace(str, "\"", "\"\""); //�����ű��˫����

	        if(NeedQuotation(str))
	        { 
	          //������Ҫ��˫����
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
                //�ӷָ���
				fwrite(mfieldsep.c_str(),strlen(mfieldsep.c_str()),1,mfout);	
			}
		}
	
		fwrite("\n",1,1,mfout);
	    fflush(mfout);
	}
    //��ѯ��ͷ���ڵ���(��0��ʼ��-1�����ڶ�Ӧ�ı�ͷ)
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
