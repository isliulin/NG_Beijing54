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
 *    CVS: $Id: ZipIfStream.cc,v 1.1.1.1 2006/02/26 11:59:24 dems14m1 Exp $
 *                                                                          *
 **************************************************************************** 
 *                                                                          *
 *    \file    ZipIfStream.cc
 *    \brief   
 *    \author  uli                                                          * 
 *                                                                          *
 ****************************************************************************/ 

// {{{ INCLUDES

#include "ZipIfStream.h"

// SYSTEM INCLUDES
// 

#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string>

// PROJECT INCLUDES
//

// LOCAL INCLUDES
// 
 
// }}}

// {{{ PUBLIC

///////////////////////////////// PUBLIC /////////////////////////////////////

//=============================== LIFECYCLE ==================================

// Default constructor initializes stream buffer
ZipIfStream::ZipIfStream()
: std::istream(NULL), sb()
{ this->init(&sb); }

// Initialize stream buffer and open file
ZipIfStream::ZipIfStream(const char* name,
                       std::ios_base::openmode mode)
: std::istream(NULL), sb()
{
  this->init(&sb);
  this->open(name, mode);
}


// Open file and go into fail() state if unsuccessful
void
ZipIfStream::open(const char* name,
                 std::ios_base::openmode mode)
{
  if (!sb.open(name, mode | std::ios_base::in))
    this->setstate(std::ios_base::failbit);
  else
    this->clear();
}

// Close file
void
ZipIfStream::close()
{
  if (!sb.close())
    this->setstate(std::ios_base::failbit);
}

/*****************************************************************************/
//=============================== ACCESS =====================================

//=============================== INQUIRY ==================================== 

// }}}

// {{{ PROTECTED

///////////////////////////////// PROTECTED //////////////////////////////////

// }}}

// {{{ PRIVATE

///////////////////////////////// PRIVATE ////////////////////////////////////

// }}}
#endif //USE_ZLIB
