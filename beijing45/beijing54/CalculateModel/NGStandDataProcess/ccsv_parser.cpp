#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ccsv_parser.h"


#define CSV_PARSER_FREE_BUFFER_PTR(ptr)	\
	if (ptr != NULL)					\
{										\
	free(ptr);							\
	\
	ptr = NULL;							\
}
#define CSV_PARSER_FREE_FILE_PTR(fptr)	\
	if (fptr != NULL)					\
{										\
	fclose(fptr);						\
	\
	fptr = NULL;						\
}

CCSV_Parser::CCSV_Parser(const char cfield_terminator,const char cenclosed_char) 
: enclosed_char(cenclosed_char), 	
escaped_char(0x5C),
field_term_char(cfield_terminator),  	
line_term_char(0x0A),
enclosed_length(0U),    	
escaped_length(1U),
field_term_length(1U),  	
line_term_length(1U),
ignore_num_lines(0U),   	
record_count(0U),
input_fp(NULL),		   	
input_filename(NULL),
enclosure_type(ENCLOSURE_OPTIONAL),
more_rows(false)
{ 

}

CCSV_Parser::~CCSV_Parser()
{
	CSV_PARSER_FREE_FILE_PTR(input_fp);

	CSV_PARSER_FREE_BUFFER_PTR(input_filename);
}

bool CCSV_Parser::init(const char * input_file)
{
	const size_t filename_length = strlen(input_file);

	if (!filename_length)
	{
		fprintf(stderr, "Fatal error : invalid input file %s\n", input_file);

		return false;
	}

	input_filename = (char *) malloc(filename_length + 1);

	if (input_filename == NULL)
	{
		fprintf(stderr, "Fatal error : unable to allocate memory for file name buffer %s\n", input_file);

		return false;
	}

	memset(input_filename, 0, filename_length + 1);

	strcpy(input_filename, input_file);


	input_fp = fopen(input_file, "r");

	if (input_fp == NULL)
	{
		fprintf(stderr, "Fatal error : unable to open input file %s\n", input_file);

		CSV_PARSER_FREE_BUFFER_PTR(input_filename);

		return false;
	}
	more_rows = true;

	skip_lines();

	return true;
}

void CCSV_Parser::set_enclosed_char(char fields_enclosed_by, enclosure_type_t enclosure_mode)
{
	if (fields_enclosed_by != 0)
	{
		enclosed_char   = fields_enclosed_by;
		enclosed_length = 1U;
		enclosure_type  = enclosure_mode;
	}
}

void CCSV_Parser::set_field_term_char(char fields_terminated_by)
{
	if (fields_terminated_by != 0)
	{
		field_term_char   = fields_terminated_by;
		field_term_length = 1U;
	}
}

void CCSV_Parser::set_line_term_char(char lines_terminated_by)
{
	if (lines_terminated_by != 0)
	{
		line_term_char   = lines_terminated_by;
		line_term_length = 1U;
	}
}

CCSV_Row CCSV_Parser::get_row()
{
	CCSV_Row current_row;

	/* Grab one record */
	if (read_single_line())
	{
		/* This will store the length of the buffer */
		/* Character array buffer for the current record */
		char * line = line = szLineBuffer;
		unsigned int line_length = strlen(line)+1;

		switch(enclosure_type)
		{
		case ENCLOSURE_NONE : 	 /* The fields are not enclosed by any character */
			get_fields_without_enclosure(&current_row, line, &line_length);
			break;

		case ENCLOSURE_REQUIRED : /* The fields are enclosed by a character */
			get_fields_with_enclosure(&current_row, line, &line_length);
			break;

		case ENCLOSURE_OPTIONAL : /* The fields may or may not be enclosed */
		default :
			get_fields_with_optional_enclosure(&current_row, line, &line_length);
			break;
		}
	}

	record_count++;

	return current_row;
}

/* BEGIN DEFINITION FOR PROTECTED METHODS */


/* BEGIN DEFINITION FOR PRIVATE METHODS */

void CCSV_Parser::skip_lines()
{
	/* Just in case the user accidentally sets ignore_num_lines to a negative number */
	unsigned int number_of_lines_to_ignore = abs((int) ignore_num_lines);

	while(has_more_rows() && number_of_lines_to_ignore)
	{
		const CCSV_Row row = get_row();

		number_of_lines_to_ignore--;
	}

	record_count = 0U;
}

void CCSV_Parser::get_fields_without_enclosure(CCSV_Row_Ptr row, const char * line, const unsigned int * line_length)
{
	char * field = NULL;

	if (*line_length > 0)
	{
		field = (char *) malloc(*line_length);

		memset(field, 0, *line_length);

		register unsigned int field_start   = 0U;
		register unsigned int field_end     = 0U;
		register unsigned int char_pos 		= 0U;

		while(char_pos < *line_length)
		{
			char curr_char = line[char_pos];

			if (curr_char == field_term_char)
			{
				field_end = char_pos;

				const char * field_starts_at = line + field_start;

				/* Field width must exclude field delimiter characters */
				const unsigned int field_width = field_end - field_start;

				/* Copy exactly field_width bytes from field_starts_at to field */
				memcpy(field, field_starts_at, field_width);

				/* This must be a null-terminated character array */
				field[field_width] = 0x00;

				string field_string_obj = field;

				row->push_back(field_string_obj);

				/* This is the starting point of the next field */
				field_start = char_pos + 1;

			} 
			else if (curr_char == line_term_char)
			{
				field_end = char_pos;

				const char * field_starts_at = line + field_start;

				/* Field width must exclude line terminating characters */
				const unsigned int field_width = field_end - field_start;

				/* Copy exactly field_width bytes from field_starts_at to field */
				memcpy(field, field_starts_at, field_width);

				/* This must be a null-terminated character array */
				field[field_width] = 0x00;

				string field_string_obj = field;

				row->push_back(field_string_obj);
			}

			/* Move to the next character in the current line */
			char_pos++;
		}

		/* Deallocate memory for field buffer */
		CSV_PARSER_FREE_BUFFER_PTR(field);
	}
}


void CCSV_Parser::get_fields_with_enclosure(CCSV_Row_Ptr row, const char * line, const unsigned int * line_length)
{
	char * field = NULL;

	if (*line_length > 0)
	{
		field = (char *) malloc(*line_length);

		memset(field, 0, *line_length);

		register unsigned int current_state = 0U;
		register unsigned int field_start   = 0U;
		register unsigned int field_end     = 0U;
		register unsigned int char_pos 		= 0U;

		while(char_pos < *line_length)
		{
			char curr_char = line[char_pos];

			if (curr_char == enclosed_char)
			{
				current_state++;

				/* Lets find out if the enclosure character encountered is
				 * a 'real' enclosure character or if it is an embedded character that
				 * has been escaped within the field.
				 */
				register char previous_char = 0x00;

				if (char_pos > 0U)
				{
					/* The escaped char will have to be the 2rd or later character. */
					previous_char = line[char_pos - 1];

					if (previous_char == escaped_char)
					{
						--current_state;
					}
				}

				if (current_state == 1U && previous_char != escaped_char)
				{
					/* This marks the beginning of the column */
					field_start = char_pos;

				} 
				else if (current_state == 2U)
				{
					/* We have found the end of the current field */
					field_end = char_pos;

					/* We do not need the enclosure characters */
					const char * field_starts_at = line + field_start + 1U;

					/* Field width must exclude beginning and ending enclosure characters */
					const unsigned int field_width = field_end - field_start - 1U;

					/* Copy exactly field_width bytes from field_starts_at to field */
					memcpy(field, field_starts_at, field_width);

					/* This must be a null-terminated character array */
					field[field_width] = 0x00;

					string field_string_obj = field;

					row->push_back(field_string_obj);

					/* Reset the state to zero value for the next field */
					current_state = 0U;
				}
			}

			/* Move to the next character in the current line */
			char_pos++;
		}

		/* If no enclosures were found in this line, the entire line becomes the only field. */
		if (0 == row->size())
		{
			string entire_line = line;

			row->push_back(entire_line);

		} else if (current_state == 1U)
		{
			/* The beginning enclosure character was found but
			 * we could not locate the closing enclosure in the current line
			 * So we need to copy the remainder of the line into the last field.
			 */

			/* We do not need the starting enclosure character */
			const char * field_starts_at = line + field_start + 1U;

			/* Field width must exclude beginning characters */
			const unsigned int field_width = *line_length - field_start - 1U;

			/* Copy exactly field_width bytes from field_starts_at to field */
			memcpy(field, field_starts_at, field_width);

			/* This must be a null-terminated character array */
			field[field_width] = 0x00;

			string field_string_obj = field;

			row->push_back(field_string_obj);
		}

		/* Release the buffer for the field */
		CSV_PARSER_FREE_BUFFER_PTR(field);
	}
}

//使用栅栏和单元格分隔符 来分割 CSV 的 行数据
void CCSV_Parser::get_fields_with_optional_enclosure(CCSV_Row_Ptr row, const char * line, const unsigned int * line_length)
{
	char * field = NULL;

	/*
	* How to extract the fields, when the enclosure char is optional.
	*
	* This is very similar to parsing the document without enclosure but with the following conditions.
	*
	* If the beginning char is an enclosure character, adjust the starting position of the string by + 1.
	* If the ending char is an enclosure character, adjust the ending position by -1
	*/
	if (*line_length > 0)
	{
		field = (char *) malloc(*line_length);

		memset(field, 0, *line_length);

		register unsigned int current_state = 0U;
		register unsigned int field_start   = 0U;
		register unsigned int field_end     = 0U;
		register unsigned int char_pos 		= 0U;

		while(char_pos < *line_length)
		{
			char curr_char = line[char_pos];

			if (curr_char == enclosed_char)
			{
				current_state++;

				/* Lets find out if the enclosure character encountered is
				* a 'real' enclosure character or if it is an embedded character that
				* has been escaped within the field.
				*/
				register char previous_char = 0x00;

				if (char_pos > 0U)
				{
					/* The escaped char will have to be the 2rd or later character. */
					previous_char = line[char_pos - 1];

					if (previous_char == escaped_char)
					{
						--current_state;
					}
				}

				//记录第一个栅栏位置
				if (current_state == 1U && previous_char != escaped_char)
				{
					/* This marks the beginning of the column */
					field_start = char_pos;

				} 
			}

			//发现单元格分隔符，并且：未出现栅栏，或者栅栏数为偶数个，则一个新的单元格产生
			if (curr_char == field_term_char && current_state %2 == 0 )
			{
				current_state = 0U;  //重置栅栏个数为 0
				field_end = char_pos;

				const char * field_starts_at = line + field_start;

				/* Field width must exclude field delimiter characters */
				unsigned int field_width = field_end - field_start;

				const char line_first_char = field_starts_at[0];
				const char line_final_char = field_starts_at[field_width - 1];

				/* If the enclosure char is found at either ends of the string */
				unsigned int first_adjustment = (line_first_char == enclosed_char) ? 1U : 0U;
				unsigned int final_adjustment = (line_final_char == enclosed_char) ? 2U : 0U;

				/* We do not want to have any negative or zero field widths */
				field_width = (field_width > 2U) ? (field_width - final_adjustment) : field_width;

				/* Copy exactly field_width bytes from field_starts_at to field */
				memcpy(field, field_starts_at + first_adjustment, field_width);

				/* This must be a null-terminated character array */
				field[field_width] = 0x00;

				string field_string_obj = field;

				row->push_back(field_string_obj);

				/* This is the starting point of the next field */
				field_start = char_pos + 1;

			} 
			else if (curr_char == line_term_char)
			{
				field_end = char_pos;

				const char * field_starts_at = line + field_start;

				/* Field width must exclude line terminating characters */
				unsigned int field_width = field_end - field_start;

				const char line_first_char = field_starts_at[0];
				const char line_final_char = field_starts_at[field_width - 1];

				/* If the enclosure char is found at either ends of the string */
				unsigned int first_adjustment = (line_first_char == enclosed_char) ? 1U : 0U;
				unsigned int final_adjustment = (line_final_char == enclosed_char) ? 2U : 0U;

				/* We do not want to have any negative or zero field widths */
				field_width = (field_width > 2U) ? (field_width - final_adjustment) : field_width;

				/* Copy exactly field_width bytes from field_starts_at to field */
				memcpy(field, field_starts_at + first_adjustment, field_width);

				/* This must be a null-terminated character array */
				field[field_width] = 0x00;

				string field_string_obj = field;

				row->push_back(field_string_obj);
			}

			/* Move to the next character in the current line */
			char_pos++;
		}

		/* Deallocate memory for field buffer */
		CSV_PARSER_FREE_BUFFER_PTR(field);
	}
}

bool CCSV_Parser::read_single_line()
{
	if (fgets(szLineBuffer,Line_Buffer_Size,input_fp)== NULL)
	{
		/* We have reached the end of the file */
		more_rows = false;
		return false;
	}
	return true;	
}