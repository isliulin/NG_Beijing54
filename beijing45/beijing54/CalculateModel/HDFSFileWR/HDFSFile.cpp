#include "HDFSFile.h"
#include <stdio.h>
#include <fcntl.h>

#ifndef USE_HDFSs

hdfsFile ngfsOpenFile( hdfsFS fs, const char* path, int flags, int bufferSize, short replication, tSize blocksize )
{
	FILE * file = 0;
	if(flags == O_RDONLY)
		file = fopen(path,"rb");
	else if(flags)
		file = fopen(path,"wb");
	return file;
}


int ngfsCloseFile( hdfsFS fs, hdfsFile file )
{
	FILE * pfile = (FILE *)file;
	if(pfile)
		return fclose(pfile);
	return 0;
}

int ngfsSeek( hdfsFS fs, hdfsFile file, tOffset desiredPos )
{
	FILE * pfile = (FILE *)file;
	if(!pfile) return 0;
	return fseek(pfile,desiredPos,SEEK_SET);
}

tOffset ngfsTell( hdfsFS fs, hdfsFile file )
{
	FILE * pfile = (FILE *)file;
	if(!pfile) return 0;
	return ftell(pfile);
}


tSize ngfsRead( hdfsFS fs, hdfsFile file, void* buffer, tSize length )
{
	FILE * pfile = (FILE *)file;
	if(!pfile) return 0;
	tSize l = 0;
	while(true)
	{
		char * temp = ((char*)buffer)+l;
		tSize t = fread(temp,1,length-l,pfile);
		l+= t;

		if((l>=length)||t<=0)
			break;
	}

	return l;
}

tSize ngfsPread( hdfsFS fs, hdfsFile file, tOffset position, void* buffer, tSize length )
{
	FILE * pfile = (FILE *)file;
	if(!pfile) return 0;
	fseek(pfile,position,SEEK_SET);
	return fread(buffer,1,length,pfile);
}


tSize ngfsWrite( hdfsFS fs, hdfsFile file, const void* buffer, tSize length )
{
	FILE * pfile = (FILE *)file;
	if(!pfile) return 0;
	return fwrite(buffer,1,length,pfile);
}


int ngfsFlush( hdfsFS fs, hdfsFile file )
{
	FILE * pfile = (FILE *)file;
	if(!pfile) return 0;
	return fflush(pfile);
}

struct hdfsBuilder * ngfsNewBuilder( void )
{
	return 0;
}

void ngfsBuilderSetNameNode( struct hdfsBuilder *bld, const char *nn )
{

}

void ngfsBuilderSetNameNodePort( struct hdfsBuilder *bld, tPort port )
{

}

hdfsFS ngfsBuilderConnect( struct hdfsBuilder *bld )
{
	return 0;
}

int ngfsDisconnect(hdfsFS fs)
{
	return 0;
}

void ngfsFreeBuilder( struct hdfsBuilder *bld )
{

}

#else

hdfsFile ngfsOpenFile( hdfsFS fs, const char* path, int flags, int bufferSize, short replication, tSize blocksize )
{
	return hdfsOpenFile(fs, path, flags,bufferSize,replication, blocksize);
}


int ngfsCloseFile( hdfsFS fs, hdfsFile file )
{
	return hdfsCloseFile(fs,file );
}

int ngfsSeek( hdfsFS fs, hdfsFile file, tOffset desiredPos )
{

	return hdfsSeek(fs,file,desiredPos );
}

tOffset ngfsTell( hdfsFS fs, hdfsFile file )
{
	return hdfsTell( fs, file );
}


tSize ngfsRead( hdfsFS fs, hdfsFile file, void* buffer, tSize length )
{
	return hdfsRead( fs,file,buffer,length );
}

tSize ngfsPread( hdfsFS fs, hdfsFile file, tOffset position, void* buffer, tSize length )
{
	return hdfsPread( fs, file, position,  buffer, length );
}


tSize ngfsWrite( hdfsFS fs, hdfsFile file, const void* buffer, tSize length )
{
	return hdfsWrite( fs,file,buffer,length );
}


int ngfsFlush( hdfsFS fs, hdfsFile file )
{
	return hdfsFlush( fs,file );
}

struct hdfsBuilder * ngfsNewBuilder( void )
{
	return hdfsNewBuilder();
}

void ngfsBuilderSetNameNode( struct hdfsBuilder *bld, const char *nn )
{
	 hdfsBuilderSetNameNode( bld,nn );
}

void ngfsBuilderSetNameNodePort( struct hdfsBuilder *bld, tPort port )
{
	hdfsBuilderSetNameNodePort(bld,port );
}

hdfsFS ngfsBuilderConnect( struct hdfsBuilder *bld )
{
	return hdfsBuilderConnect( bld );
}


int ngfsDisconnect(hdfsFS fs)
{
	return hdfsDisconnect(fs);
}

void ngfsFreeBuilder( struct hdfsBuilder *bld )
{
	hdfsFreeBuilder(bld );
}

#endif



