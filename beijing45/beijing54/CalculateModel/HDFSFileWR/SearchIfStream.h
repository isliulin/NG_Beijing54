#ifdef USE_ZLIB
// -*- C++ -*-
// 			MoRaNET Header to be included

/****************************************************************************/
/*!
  
    \file   SearchIfStream.h
    \brief  This file contains the class SearchIfStream

*/
/****************************************************************************/

#ifndef SearchIfStream_H
#define SearchIfStream_H

// SYSTEM INCLUDES
//
#include <fstream>
#include <ios>

// PROJECT INCLUDES
//
#include "ZipIfStream.h"

// LOCAL INCLUDES
//


// FORWARD REFERENCES
//

/****************************************************************************/
//!  SearchIfStream is basically a ifstream, but searches in several directories
//!  for the file. 

/*!  The directories to be searched are given by a DynArray of char*. Only
     the opening constructor and the open method are implemented 
*/
/****************************************************************************/

class HDFSWR_API SearchIfStream : public ZipIfStream
{
 public:
    SearchIfStream() : ZipIfStream(), mpLongFilename(0) {}
    SearchIfStream(const char *name, 
		   const char* path = 0,
		   bool mSimulate = false,
		   openmode mode=in|binary, 
		   int prot=0664);
    virtual ~SearchIfStream() {delete[] mpLongFilename;}
	    
    void open(const char *name, 
	      const char* path,
	      openmode mode=in|binary, 
	      int prot=0664); 

    //! Get the filename and its corresponding path, the file was actually read from 
    const char* GetFilename() {return mpLongFilename;}
    
    //! Just test if file can be found 
    static char* Test(const char* filename, const char* path);

    
  protected:
  private:
    char* mpLongFilename;

    //! if  to actually unzip zipped file (or just a test)
    bool mSimulate;
    
};

// EXTERNAL

// INLINE METHODS
//

#endif
#endif //USE_ZLIB
