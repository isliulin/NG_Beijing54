#ifdef USE_ZLIB
// -*- C++ -*-
/****************************************************************************
 *                                                                          *
 *                                                                          *
 *                AAAAA    CCCCCC   OOOOO   RRRRRR   N     N                *
 *               A     A  C        O     O  R     R  NN    N                *
 *               A     A  C        O     O  R     R  N N   N                *
 *               AAAAAAA  C        O     O  RRRRRR   N  N  N                *
 *               A     A  C        O     O  R  R     N   N N                *
 *               A     A  C        O     O  R   R    N    NN                *
 *               A     A   CCCCCC   OOOOO   R    R   N     N                *
 *                                                                          *
 *                                                                          *
 *       Automatic Configuration and Optimization of Radio Networks         *
 *                                                                          *
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 *    CVS: $Id: SearchIfStream.cc,v 1.1.1.1 2006/02/26 11:59:24 dems14m1 Exp $
 *                                                                          *
 ****************************************************************************
 *                                                                          *
 *    \file    SearchIfStream.cc
 *    \brief
 *    \author  uli                                                          *
 *                                                                          *
 ****************************************************************************/

// {{{ INCLUDES

#include "SearchIfStream.h"

// SYSTEM INCLUDES
//

#include <string>
#include <stdlib.h>

#pragma warning(disable:4996)

#define _cond_delete_array(what) if (what) delete[] what; what=0;

inline void NGGlobal_StrCpy(char*& dest, const char* source)
{
	dest =  new char[strlen(source)+1];
	strcpy(dest,source);
}

// PROJECT INCLUDES
//

// LOCAL INCLUDES
//

// }}}

// {{{ PUBLIC

///////////////////////////////// PUBLIC /////////////////////////////////////

//=============================== LIFECYCLE ==================================

SearchIfStream::SearchIfStream(const char* name,
			       const char* search_path,
			       bool simulate,
			       openmode mode,
			       int prot)
    : ZipIfStream(), mpLongFilename(0), mSimulate(simulate)
{
    open(name, search_path, mode, prot);
}

//=============================== OPERATORS ==================================

//=============================== OPERATIONS =================================

void SearchIfStream::open(const char* orig_name,
			  const char* orig_search_path,
			  openmode mode,
			  int prot)
{
    char* name;
    char* search_path=0;

    bool zip_filename = strcmp(orig_name+strlen(orig_name)-3, ".gz")==0;

    NGGlobal_StrCpy(name, orig_name);
    if (orig_search_path)
    {
	NGGlobal_StrCpy(search_path, orig_search_path);
    }

    char* long_name = 0;

    const char* str_ptr = 0;

    // first try to find directly

    do
    {
	_cond_delete_array(long_name);

	size_t path_len = 0;
	if (str_ptr)
	{
	    // remove leading path from name
	    char* ptr = name+strlen(name)-1;
	    while (ptr>name && *ptr!='/') ptr--;

	    if (*ptr=='/')
	    {
		char* temp = name;
		NGGlobal_StrCpy(name, ptr+1);
		delete[] temp;
	    }

	    path_len = strlen(str_ptr);
	    if (strchr(str_ptr,':')) path_len =  strchr(str_ptr,':')-str_ptr;
	}

	long_name =  new char[path_len+strlen(name)+2+3];  // +3 for .gz
	long_name[0] = 0;

	if (path_len)
	{
	    strncpy(long_name, str_ptr, path_len);
	    if (long_name[path_len-1]!='/')
	    {
		long_name[path_len]='/';
		long_name[path_len+1]=0;
	    }
	    else long_name[path_len]=0;
	}

	strcat(long_name, name);

	// try to open:
	ZipIfStream::open(long_name, mode);

    	/*if (good() && zip_filename && !mSimulate)  // found but zipped
	{
	    close();
	    OpenZippedFile(long_name);
	}
	*/

	if (!good()) // try zipped/unzipped file
	{
	    if (zip_filename)
	    {
		// remove ending
		long_name[strlen(long_name)-3] = 0;
		// try to open
//#if __GNUC__ == 3
//#else
//		ifstream::open(long_name, mode, prot);
//#endif
	    }
	    else
	    {
		strcat(long_name, ".gz");
/*
#if __GNUC__ == 3
		ifstream::open(long_name, mode);
#else
		ifstream::open(long_name, mode, prot);
#endif
		if (good() && !mSimulate)
		{
		    close();
		    OpenZippedFile(long_name);
		}
*/
	    }
	    ZipIfStream::open(long_name, mode);
	}

	if (!str_ptr) // first run
	{
	    str_ptr = search_path;
	}
	else
	{
	    str_ptr = strchr(str_ptr, ':');
	    if (str_ptr) str_ptr++;
	}

    } while (str_ptr && !good());

    if (mpLongFilename) delete[] mpLongFilename;

    if (!std::istream::good())
    {
	NGGlobal_StrCpy(mpLongFilename, "UNDEFINED");
    }
    else
    {
	mpLongFilename =  new char[strlen(long_name)+1];
	strcpy(mpLongFilename, long_name);
    }

    delete[] long_name;

    delete[] name;
    delete[] search_path;
}

char* SearchIfStream::Test(const char* filename, const char* path)
{
    // temporarily try to open the file:
    SearchIfStream test_file(filename, path, true);  //just simulate open
    char* temp = 0;
    if (test_file.good())
    {
	temp =  new char[strlen(test_file.GetFilename())+1];
	strcpy(temp, test_file.GetFilename());
    }
    return temp;
}

//=============================== ACCESS =====================================

//=============================== INQUIRY ====================================

// }}}

// {{{ PROTECTED

///////////////////////////////// PROTECTED //////////////////////////////////

// }}}

// {{{ PRIVATE

///////////////////////////////// PRIVATE ////////////////////////////////////

// }}}
#endif // USE_ZLIB
