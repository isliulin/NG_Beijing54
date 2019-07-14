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
 *    CVS: $Id: ZipOfStream.h,v 1.1.1.1 2006/02/26 11:59:24 dems14m1 Exp $
 *                                                                          *
 **************************************************************************** 
 *                                                                          *
 *    \file    ZipOfStream.h   
 *    \brief   This file contains the class ZipOfStream   
 *    \author  uli
 *                                                                          *
 ****************************************************************************/ 

#ifndef ZipOfStream_H
#define ZipOfStream_H

// SYSTEM INCLUDES
//
#include <fstream>

// PROJECT INCLUDES
//
#include "ZipFileBuf.h"

// LOCAL INCLUDES
//


// FORWARD REFERENCES
//

/****************************************************************************/
//! ZipOfStream is basically a ofstream, that zips the output when closing 
//! the file in case of .gz file ending ending 
/****************************************************************************/

class HDFSWR_API ZipOfStream : public std::ostream
{
public:
  //  Default constructor
  ZipOfStream();

  /**
   *  @brief  Construct stream on gzipped file to be opened.
   *  @param  name  File name.
   *  @param  mode  Open mode flags (forced to contain ios::out).
  */
  explicit
  ZipOfStream(const char* name,
	      std::ios_base::openmode mode = std::ios_base::out | std::ios_base::binary);
    
    ~ZipOfStream() {close();}
    
	    

  /**
   *  Obtain underlying stream buffer.
  */
  ZipFileBuf*
  rdbuf() const
  { return dynamic_cast<ZipFileBuf*>(mpZipBuf); }

  /**
   *  @brief  Check if file is open.
   *  @return  True if file is open.
  */
  bool
      is_open() { if (mpZipBuf) return mpZipBuf->is_open();
                  if (mpStdBuf) return mpStdBuf->is_open();
                  else return false;}

  /**
   *  @brief  Open gzipped file.
   *  @param  name  File name.
   *  @param  mode  Open mode flags (forced to contain ios::out).
   *
   *  Stream will be in state good() if file opens successfully;
   *  otherwise in state fail(). This differs from the behavior of
   *  ofstream, which never sets the state to good() and therefore
   *  won't allow you to reuse the stream for a second file unless
   *  you manually clear() the state. The choice is a matter of
   *  convenience.
  */
  void
  open(const char* name,
       std::ios_base::openmode mode = std::ios_base::out | std::ios_base::binary);
  /**
   *  @brief  Close gzipped file.
   *
   *  Stream will be in state fail() if close failed.
  */
  void
  close();

protected:
  bool DoZip(const char* filename) 
  {
	 // return strncmp(filename+strlen(filename)-3, ".gz", 3)==0;
	  return true;
  }
  
      
  
private:
  /**
   *  Underlying stream buffer.
  */
  ZipFileBuf* mpZipBuf;
  std::filebuf* mpStdBuf;
};



// EXTERNAL

// INLINE METHODS
//

#endif
#endif // USE_ZLIB
