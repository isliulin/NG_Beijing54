#pragma once
#ifndef USE_HDFSs
struct hdfsBuilder;
typedef void * hdfsFile;
typedef void * hdfsFS;

typedef unsigned int tSize;
typedef int tOffset;
typedef unsigned short tPort;
#else
#include "hdfs.h"
#endif

extern "C"
{
	struct hdfsBuilder *ngfsNewBuilder(void);
	void ngfsBuilderSetNameNode(struct hdfsBuilder *bld, const char *nn);
	void ngfsBuilderSetNameNodePort(struct hdfsBuilder *bld, tPort port);
	hdfsFS ngfsBuilderConnect(struct hdfsBuilder *bld);
	int ngfsDisconnect(hdfsFS fs);
	void ngfsFreeBuilder(struct hdfsBuilder *bld);
	hdfsFile ngfsOpenFile(hdfsFS fs, const char* path, int flags, int bufferSize, short replication, tSize blocksize);
	int ngfsCloseFile(hdfsFS fs, hdfsFile file);
	int ngfsSeek(hdfsFS fs, hdfsFile file, tOffset desiredPos);
	tOffset ngfsTell(hdfsFS fs, hdfsFile file);
    tSize ngfsRead(hdfsFS fs, hdfsFile file, void* buffer, tSize length);
	tSize ngfsPread(hdfsFS fs, hdfsFile file, tOffset position, void* buffer, tSize length);
	tSize ngfsWrite(hdfsFS fs, hdfsFile file, const void* buffer, tSize length);
	int ngfsFlush(hdfsFS fs, hdfsFile file);

};
