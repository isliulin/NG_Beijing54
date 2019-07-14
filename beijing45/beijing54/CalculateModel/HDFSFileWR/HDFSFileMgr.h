#pragma once
#include "IFileManager.h"
#include "HDFSFile.h"

class HDFSWR_API HDFSFileSystem
{
public:
	HDFSFileSystem(const char * nn,short port);
	~HDFSFileSystem();
protected:
	hdfsBuilder * pBuilder;
	hdfsFS filesys;
public:
	hdfsFS GetFileSystem() const {return filesys;}
};

class HDFSWR_API HDFSFileReader :
	public IFileReader
{
public:
	HDFSFileReader(const char * ifilename);
	~HDFSFileReader(void);
protected:
	hdfsFile fileHandler;
	long long currentoffset;
	hdfsFS filesys;
public:
	void build(HDFSFileSystem & hdfsFs);
	bool open();
public:
	virtual void seek(long long offset) ;
	virtual unsigned read(void * buf,unsigned bufsize);
	virtual bool isvalid();
	virtual void gotohead();
	virtual void close();
};

class HDFSWR_API HDFSFileWriter:public IFileWriter
{
public:
	HDFSFileWriter(const char * ifilename);
	~HDFSFileWriter();
protected:
	hdfsFile fileHandler;
	hdfsFS filesys;
public:
	void bulid(HDFSFileSystem & hdfsFs);
	bool open();
	void close();
public:
	virtual void write(void * buf,unsigned bufsize);
	virtual void flush();
	virtual bool isvalid();
 
};
