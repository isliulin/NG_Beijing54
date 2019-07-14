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
 *    CVS: $Id: ZipOfStream.cc,v 1.1.1.1 2006/02/26 11:59:24 dems14m1 Exp $
 *                                                                          *
 **************************************************************************** 
 *                                                                          *
 *    \file    ZipOfStream.cc
 *    \brief   The implementation part of ZipOfStream
 *    \author  uli
 *                                                                          *
 ****************************************************************************/ 
                  
// {{{ INCLUDES

// LOCAL INCLUDES
// 
#include "ZipOfStream.h"

// SYSTEM INCLUDES
// 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// PROJECT INCLUDES
//
 
// }}}

// {{{ PUBLIC

///////////////////////////////// PUBLIC /////////////////////////////////////

//=============================== LIFECYCLE ==================================

//=============================== OPERATORS ==================================

//=============================== OPERATIONS =================================

// Default constructor initializes stream buffer
ZipOfStream::ZipOfStream()
    : std::ostream(NULL) , mpZipBuf(0), mpStdBuf(0)
{
}


// Initialize stream buffer and open file
ZipOfStream::ZipOfStream(const char* name,
                       std::ios_base::openmode mode)
: std::ostream(NULL), mpZipBuf(0), mpStdBuf(0)
{
    this->open(name, mode);
}

// Open file and go into fail() state if unsuccessful
void
ZipOfStream::open(const char* name,
                 std::ios_base::openmode mode)
{
    close();
    
    if (DoZip(name))
    {
	mpZipBuf =  new ZipFileBuf();
	this->init(mpZipBuf);    

	if (!mpZipBuf->open(name, mode | std::ios_base::out | std::ios_base::binary))  // always binary!!
	    this->setstate(std::ios_base::failbit);
	else
	    this->clear();
    }
    else
    {
	mpStdBuf =  new std::filebuf();
	this->init(mpStdBuf);    

	if (!mpStdBuf->open(name, mode | std::ios_base::out))
	    this->setstate(std::ios_base::failbit);
	else
	    this->clear();
    }
}


// Close file
void
ZipOfStream::close()
{
    flush();

    if (mpZipBuf)
    {
	//mpZipBuf->pubsync();
	if (!mpZipBuf->close())
	    this->setstate(std::ios_base::failbit);
	delete mpZipBuf; mpZipBuf = 0;
    }
    
    if (mpStdBuf)
    {
	//mpStdBuf->pubsync();
	if (!mpStdBuf->close())
	    this->setstate(std::ios_base::failbit);
	delete mpStdBuf; mpStdBuf = 0;
    }
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
