/**
jjj 2012.7.27

说明:
CCSV_Parser 来自网上找的的 csv_Parser 类，原作者是:Israel Ekpo <israel.ekpo@israelekpo.com>
这里做了一些改进主要包括:
	1. get_fields_with_optional_enclosure 做了一点改进，修正了多个栅栏不能正确解析的问题
	2. read_single_line 改为读取一行字符串，原始代码每次读取一个字符，CSV文件很大时读取很慢
	3. szLineBuffer 是新增的变量，也是为了加快读取代码
	4. 2,3的改进加快读取文件的速度，但是也导致行终结符设置无效,不如原始代码通用性强
	5. 为了区别于原始类这里重新命名新的类为CCSV_Parser,文件名也改成了ccsv_parser.h,ccsv_parser.cpp
	6. 其他小的改动从略

 */

#ifndef __CSV_PARSER_HPP_INCLUDED__
#define __CSV_PARSER_HPP_INCLUDED__

/* C++ header files */
#include <string>
#include <vector>

using namespace std;

typedef vector <string> CCSV_Row;
typedef CCSV_Row * CCSV_Row_Ptr;

class CCSV_Parser
{
public :
	CCSV_Parser(const char cfield_terminator=',',const char cenclosed_char='\"');
	~CCSV_Parser();

	typedef enum
	{
		ENCLOSURE_TYPE_BEGIN = 0,
		ENCLOSURE_NONE       = 1,		//不使用 栅栏enclosure字符 来分割单元格
		ENCLOSURE_REQUIRED   = 2,		//仅使用 栅栏enclosure字符 而忽略 单元格分隔符 来分割单元格
		ENCLOSURE_OPTIONAL   = 3,		//使用   栅栏enclosure字符 和 单元格分隔符 来分割单元格
		ENCLOSURE_TYPE_END

	} enclosure_type_t;

public:
	//下面几个函数应该在init函数之前调用，如果需要的话
	void set_skip_lines(unsigned int lines_to_skip){ignore_num_lines = lines_to_skip;}	//设置跳过不读取的行数
	void set_enclosed_char(char fields_enclosed_by, enclosure_type_t enclosure_mode);	//设置栅栏enclosure字符类别,CSV中默认为 双引号 " 
	void set_field_term_char(char fields_terminated_by);								//设置单元格分隔符
	void set_line_term_char(char lines_terminated_by);									//设置一行终结字符

	bool init(const char * input_filename);					//初始化，读取CSV文件，并跳过指定行数
	bool has_more_rows(){return more_rows;}					//判断是否读取完毕
	CCSV_Row get_row();										//读取一行数据
	
	unsigned int get_record_count(){return record_count;}
	void reset_record_count(){record_count = 0U;}

public:
	//解析行数据成单元格函数
	//不考虑栅栏enclosure字符,仅使用单元格分隔符来分割CSV行
	void get_fields_without_enclosure(CCSV_Row_Ptr row, const char * line, const unsigned int * line_length);
	//使用栅栏enclosure字符分割CSV行,不考虑用单元格分隔符，成对的栅栏构成一个单元格
	void get_fields_with_enclosure(CCSV_Row_Ptr row, const char * line, const unsigned int * line_length);
	//使用栅栏和单元格分隔符来分割CSV行
	void get_fields_with_optional_enclosure(CCSV_Row_Ptr row, const char * line, const unsigned int * line_length);

private :
	void skip_lines();
	bool read_single_line();	

protected :
	char enclosed_char;					
	char escaped_char;
	char field_term_char;
	char line_term_char;
	unsigned int enclosed_length;
	unsigned int escaped_length;
	unsigned int field_term_length;
	unsigned int line_term_length;
	unsigned int ignore_num_lines;
	unsigned int record_count;
	FILE * input_fp;
	char * input_filename;
	enclosure_type_t enclosure_type;
	bool more_rows;
	enum {Line_Buffer_Size = 4096};			//一行数据大小
	char szLineBuffer[Line_Buffer_Size];

}; 

#endif 
