#pragma once
#include "IFileManager.h"
#include <stdio.h>
class LocalFileMgr
{
public:
	LocalFileMgr(void);
	~LocalFileMgr(void);
};


class HDFSWR_API LocalFileReader:
	public IFileReader
{
public:
	LocalFileReader(const char * ifilename);
	~LocalFileReader(void);
protected:
	FILE * fp;
	unsigned subfile;
	long long flength; 
	bool splitfile(long long total,long long & first,long long &second);
	bool opensubfile();
public:
	bool open();
	void close();
	long long cur_pos;
	long long getflength();
public:
	virtual void seek(long long offset) ;
	virtual unsigned read(void * buf,unsigned bufsize);
	virtual bool isvalid();
	virtual void gotohead();
	virtual bool IsEnd();
};


class HDFSWR_API LocalFileWriter:public IFileWriter
{
public:
	LocalFileWriter(const char * ifilename);
	~LocalFileWriter();
protected:
	FILE * fp;
	unsigned curSize;
	unsigned subfile;
public:
	bool open();
	bool open(const char * mode);
	void close();
	void checkLength(unsigned size);
public:
	virtual void write(void * buf,unsigned bufsize);
	virtual void flush();
	virtual bool isvalid();

};