#ifdef USE_ZLIB
// -*- C++ -*-
// 			MoRaNET Header to be included
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
 *    CVS: $Id: ZipIfStream.h,v 1.1.1.1 2006/02/26 11:59:24 dems14m1 Exp $
 *                                                                          *
 **************************************************************************** 
 *                                                                          *
 *    \file    ZipIfStream.h   
 *    \brief   This file contains the class ZipIfStream   
 *    \author  uli
 *                                                                          *
 ****************************************************************************/ 

#ifndef ZipIfStream_H
#define ZipIfStream_H

// SYSTEM INCLUDES
//
#include <iostream>
#include <sstream>

#include <fstream>
#include <zlib.h>

#include "ZipFileBuf.h"


/*****************************************************************************/
/* Based on gzifstream provided with zlib library */
/**
 *  @brief  Gzipped file input stream class.
 *
 *  This class implements ifstream for gzipped files. Seeking and putback
 *  is not supported yet.
*/

class HDFSWR_API ZipIfStream : public std::istream
{
public:
  //  Default constructor
  ZipIfStream();

  /**
   *  @brief  Construct stream on gzipped file to be opened.
   *  @param  name  File name.
   *  @param  mode  Open mode flags (forced to contain ios::in).
  */
  explicit
  ZipIfStream(const char* name,
             std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary);

  /**
   *  Obtain underlying stream buffer.
  */
  ZipFileBuf*
  rdbuf() const
  { return const_cast<ZipFileBuf*>(&sb); }

  /**
   *  @brief  Check if file is open.
   *  @return  True if file is open.
  */
  bool
  is_open() { return sb.is_open(); }

  /**
   *  @brief  Open gzipped file.
   *  @param  name  File name.
   *  @param  mode  Open mode flags (forced to contain ios::in).
   *
   *  Stream will be in state good() if file opens successfully;
   *  otherwise in state fail(). This differs from the behavior of
   *  ifstream, which never sets the state to good() and therefore
   *  won't allow you to reuse the stream for a second file unless
   *  you manually clear() the state. The choice is a matter of
   *  convenience.
  */
  void
  open(const char* name,
       std::ios_base::openmode mode = std::ios_base::in | std::ios_base::binary);
  /**
   *  @brief  Close gzipped file.
   *
   *  Stream will be in state fail() if close failed.
  */
  void
  close();

private:
  /**
   *  Underlying stream buffer.
  */
  ZipFileBuf sb;
};



// EXTERNAL

// INLINE METHODS
//

#endif
#endif //USE_ZLIB
