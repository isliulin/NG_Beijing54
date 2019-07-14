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
 *    CVS: $Id: ZipFileBuf.h,v 1.1.1.1 2006/02/26 11:59:24 dems14m1 Exp $
 *                                                                          *
 **************************************************************************** 
 *                                                                          *
 *    \file    ZipFileBuf.h
 *    \brief   This file contains the class ZipFileBuf
 *    \author  uli                                                          * 
 *                                                                          *
 ****************************************************************************/ 

#ifndef ZipFileBuf_H
#define ZipFileBuf_H

#include "ExportDll.h"
// SYSTEM INCLUDES
//
#include <iostream>
#include <sstream>

#include <fstream>
#include <string.h>
#include <zlib.h>

using namespace std;

/**
 *
 *  Code is based on zfstream "library" provided by zlib source code 
 *
 *  @brief  Gzipped file stream buffer class.
 *
 *  This class implements basic_filebuf for gzipped files. It doesn't yet support
 *  seeking (allowed by zlib but slow/limited), putback and read/write access
 *  (tricky). Otherwise, it attempts to be a drop-in replacement for the standard
 *  file streambuf.
*/
class HDFSWR_API ZipFileBuf : public std::streambuf
{
public:
  //  Default constructor.
  ZipFileBuf();

  //  Destructor.
  virtual ~ZipFileBuf();

  /**
   *  @brief  Set compression level and strategy on the fly.
   *  @param  comp_level  Compression level (see zlib.h for allowed values)
   *  @param  comp_strategy  Compression strategy (see zlib.h for allowed values)
   *  @return  Z_OK on success, Z_STREAM_ERROR otherwise.
   *
   *  Unfortunately, these parameters cannot be modified separately, as the
   *  previous zfstream version assumed. Since the strategy is seldom changed,
   *  it can default and setcompression(level) then becomes like the old
   *  setcompressionlevel(level).
  */
  int
  setcompression(int comp_level,
                 int comp_strategy = Z_DEFAULT_STRATEGY);

  /**
   *  @brief  Check if file is open.
   *  @return  True if file is open.
  */
  bool
  is_open() const { return (file != NULL); }

  /**
   *  @brief  Open gzipped file.
   *  @param  name  File name.
   *  @param  mode  Open mode flags.
   *  @return  @c this on success, NULL on failure.
  */
  ZipFileBuf*
  open(const char* name,
       std::ios_base::openmode mode);

  /**
   *  @brief  Close gzipped file.
   *  @return  @c this on success, NULL on failure.
  */
  ZipFileBuf*  close();

protected:
  /**
   *  @brief  Convert ios open mode int to mode string used by zlib.
   *  @return  True if valid mode flag combination.
  */
  bool
  open_mode(std::ios_base::openmode mode,
            char* c_mode) const;

  /**
   *  @brief  Number of characters available in stream buffer.
   *  @return  Number of characters.
   *
   *  This indicates number of characters in get area of stream buffer.
   *  These characters can be read without accessing the gzipped file.
  */
  virtual std::streamsize
  showmanyc();

  /**
   *  @brief  Fill get area from gzipped file.
   *  @return  First character in get area on success, EOF on error.
   *
   *  This actually reads characters from gzipped file to stream
   *  buffer. Always buffered.
  */
  virtual int_type
  underflow();

  /**
   *  @brief  Write put area to gzipped file.
   *  @param  c  Extra character to add to buffer contents.
   *  @return  Non-EOF on success, EOF on error.
   *
   *  This actually writes characters in stream buffer to
   *  gzipped file. With unbuffered output this is done one
   *  character at a time.
  */
  virtual int_type
  overflow(int_type c = traits_type::eof());

  /**
   *  @brief  Installs external stream buffer.
   *  @param  p  Pointer to char buffer.
   *  @param  n  Size of external buffer.
   *  @return  @c this on success, NULL on failure.
   *
   *  Call setbuf(0,0) to enable unbuffered output.
  */
  virtual std::streambuf*
  setbuf(char_type* p,
         std::streamsize n);

  /**
   *  @brief  Flush stream buffer to file.
   *  @return  0 on success, -1 on error.
   *
   *  This calls underflow(EOF) to do the job.
  */
  virtual int
  sync();

//
// Some future enhancements
//
//  virtual int_type uflow();
//  virtual int_type pbackfail(int_type c = traits_type::eof());
//  virtual pos_type
//  seekoff(off_type off,
//          std::ios_base::seekdir way,
//          std::ios_base::openmode mode = std::ios_base::in|std::ios_base::out);
//  virtual pos_type
//  seekpos(pos_type sp,
//          std::ios_base::openmode mode = std::ios_base::in|std::ios_base::out);

private:
  /**
   *  @brief  Allocate internal buffer.
   *
   *  This function is safe to call multiple times. It will ensure
   *  that a proper internal buffer exists if it is required. If the
   *  buffer already exists or is external, the buffer pointers will be
   *  reset to their original state.
  */
  void
  enable_buffer();

  /**
   *  @brief  Destroy internal buffer.
   *
   *  This function is safe to call multiple times. It will ensure
   *  that the internal buffer is deallocated if it exists. In any
   *  case, it will also reset the buffer pointers.
  */
  void
  disable_buffer();

  /**
   *  Underlying file pointer.
  */
  gzFile file;

  /**
   *  Mode in which file was opened.
  */
  std::ios_base::openmode io_mode;

  /**
   *  @brief  True if this object owns file descriptor.
   *
   *  This makes the class responsible for closing the file
   *  upon destruction.
  */
  bool own_fd;

  /**
   *  @brief  Stream buffer.
   *
   *  For simplicity this remains allocated on the free store for the
   *  entire life span of the gzfilebuf object, unless replaced by setbuf.
  */
  char_type* buffer;

  /**
   *  @brief  Stream buffer size.
   *
   *  Defaults to system default buffer size (typically 8192 bytes).
   *  Modified by setbuf.
  */
  std::streamsize buffer_size;

  /**
   *  @brief  True if this object owns stream buffer.
   *
   *  This makes the class responsible for deleting the buffer
   *  upon destruction.
  */
  bool own_buffer;
};



// EXTERNAL

// INLINE METHODS
//
#endif
#endif //USE_ZLIB
