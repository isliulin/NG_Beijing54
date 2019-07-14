#pragma once
#include "ExportDll.h"

class HDFSWR_API IFile
{
public:
	IFile(const char * ifilename);
	virtual ~IFile(void);
protected:
	char *filename;
public:
	virtual bool open() = 0;
	virtual bool isvalid() = 0;	
	virtual void close() = 0;
	const char * getfilename() const {return filename;}

};

class HDFSWR_API IFileReader:public IFile
{
public:
	IFileReader(const char * ifilename);
	virtual ~IFileReader(void);
public:
	virtual void seek(long long offset) = 0;
	virtual unsigned read(void * buf,unsigned bufsize) = 0;
	virtual bool isvalid() = 0;
	virtual void gotohead() = 0;
};

class HDFSWR_API IFileWriter:public IFile
{

public:
	static IFileWriter * CreateFileWriter(const char * ifilename);
	static void ReleaseFileWriter(IFileWriter * pWriter);
public:
	IFileWriter(const char * ifilename);
	virtual ~IFileWriter(void);
public:
	virtual void checkLength (){}
	virtual void write(void * buf,unsigned bufsize) = 0;
	virtual void flush() = 0;
};
