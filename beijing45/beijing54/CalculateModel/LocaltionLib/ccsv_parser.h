/**
jjj 2012.7.27

˵��:
CCSV_Parser ���������ҵĵ� csv_Parser �࣬ԭ������:Israel Ekpo <israel.ekpo@israelekpo.com>
��������һЩ�Ľ���Ҫ����:
	1. get_fields_with_optional_enclosure ����һ��Ľ��������˶��դ��������ȷ����������
	2. read_single_line ��Ϊ��ȡһ���ַ�����ԭʼ����ÿ�ζ�ȡһ���ַ���CSV�ļ��ܴ�ʱ��ȡ����
	3. szLineBuffer �������ı�����Ҳ��Ϊ�˼ӿ��ȡ����
	4. 2,3�ĸĽ��ӿ��ȡ�ļ����ٶȣ�����Ҳ�������ս��������Ч,����ԭʼ����ͨ����ǿ
	5. Ϊ��������ԭʼ���������������µ���ΪCCSV_Parser,�ļ���Ҳ�ĳ���ccsv_parser.h,ccsv_parser.cpp
	6. ����С�ĸĶ�����

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
		ENCLOSURE_NONE       = 1,		//��ʹ�� դ��enclosure�ַ� ���ָԪ��
		ENCLOSURE_REQUIRED   = 2,		//��ʹ�� դ��enclosure�ַ� ������ ��Ԫ��ָ��� ���ָԪ��
		ENCLOSURE_OPTIONAL   = 3,		//ʹ��   դ��enclosure�ַ� �� ��Ԫ��ָ��� ���ָԪ��
		ENCLOSURE_TYPE_END

	} enclosure_type_t;

public:
	//���漸������Ӧ����init����֮ǰ���ã������Ҫ�Ļ�
	void set_skip_lines(unsigned int lines_to_skip){ignore_num_lines = lines_to_skip;}	//������������ȡ������
	void set_enclosed_char(char fields_enclosed_by, enclosure_type_t enclosure_mode);	//����դ��enclosure�ַ����,CSV��Ĭ��Ϊ ˫���� " 
	void set_field_term_char(char fields_terminated_by);								//���õ�Ԫ��ָ���
	void set_line_term_char(char lines_terminated_by);									//����һ���ս��ַ�

	bool init(const char * input_filename);					//��ʼ������ȡCSV�ļ���������ָ������
	bool has_more_rows(){return more_rows;}					//�ж��Ƿ��ȡ���
	CCSV_Row get_row();										//��ȡһ������
	
	unsigned int get_record_count(){return record_count;}
	void reset_record_count(){record_count = 0U;}

public:
	//���������ݳɵ�Ԫ����
	//������դ��enclosure�ַ�,��ʹ�õ�Ԫ��ָ������ָ�CSV��
	void get_fields_without_enclosure(CCSV_Row_Ptr row, const char * line, const unsigned int * line_length);
	//ʹ��դ��enclosure�ַ��ָ�CSV��,�������õ�Ԫ��ָ������ɶԵ�դ������һ����Ԫ��
	void get_fields_with_enclosure(CCSV_Row_Ptr row, const char * line, const unsigned int * line_length);
	//ʹ��դ���͵�Ԫ��ָ������ָ�CSV��
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
	enum {Line_Buffer_Size = 4096};			//һ�����ݴ�С
	char szLineBuffer[Line_Buffer_Size];

}; 

#endif 
