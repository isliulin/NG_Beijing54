#include "IFileManager.h"
#include <string.h>


IFile::IFile( const char * ifilename )
{
	filename = 0;
	if(ifilename!=0)
	{
		int len = strlen(ifilename)+1;
		filename= new char[len];
		strcpy(filename,ifilename);
	}
}

IFile::~IFile( void )
{
	if(filename)
		delete [] filename;
}


IFileReader::IFileReader(const char * ifilename)
:IFile(ifilename)
{
}

IFileReader::~IFileReader(void)
{
}

//IFileReader * IFileReader::CreateFileReader( const char * ifilename )
//{
//	LocalFileReader * pFile = new  LocalFileReader(ifilename);
//	if(pFile->isvalid())
//		return pFile;
//	else
//		delete pFile;
//	return 0;
//}
//
//void IFileReader::ReleaseFileReader( IFileReader * pFileReader )
//{
//	if(pFileReader)
//		delete pFileReader;
//}


IFileWriter::IFileWriter(const char * ifilename)
:IFile(ifilename)
{
}

IFileWriter::~IFileWriter(void)
{
}

//IFileWriter * IFileWriter::CreateFileWriter( const char * ifilename )
//{
//	LocalFileWriter * pFile = new LocalFileWriter(ifilename);
//	if(pFile->isvalid())
//		return pFile;
//	else
//		delete pFile;
//	return 0;
//}
//
//void IFileWriter::ReleaseFileWriter( IFileWriter * pWriter )
//{
//	if(pWriter)
//		delete pWriter;
//}


