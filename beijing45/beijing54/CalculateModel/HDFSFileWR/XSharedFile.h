#pragma once
#include "ExportDll.h"

class HDFSWR_API XSharedFile
{
public:
	XSharedFile(void);
	virtual ~XSharedFile(void);
protected:
	int fd;
public:
	bool IsOpened(){return fd>0;}
	bool OpenFile(const char * filename,bool isread);
	int Read(void * buf,int len);
	int Seek(int offset);
	int Write(void * buf, int len);
	int FileLength();
	int Tell();
	void Close();

};
