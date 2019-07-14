#include "XSharedFile.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <share.h>
#include <stdio.h>

#ifdef _MSC_VER
#include <io.h>
#endif

XSharedFile::XSharedFile(void)
{
	fd = -1;
}

XSharedFile::~XSharedFile(void)
{
	Close();
}

bool XSharedFile::OpenFile( const char * filename,bool isread )
{
	if(!filename)return false;
	if(isread)
		fd = open(filename,O_RDONLY|O_BINARY);
	else
		fd = open(filename,O_WRONLY|O_CREAT|O_BINARY,_S_IREAD);
	return fd >0;
}

int XSharedFile::Read( void * buf,int len )
{
	if(fd<=0) return 0;
	unsigned int s = 0;
	while(true)
	{
		char * temp = ((char*)buf)+s;
		int t = read(fd,temp,len-s);
		s+= t;

		if((s>=len)||t<=0)
			break;
	}
	return s;
}

int XSharedFile::Seek( int offset )
{
	if(fd>0)
		return lseek(fd,offset,SEEK_CUR);
	return 0;
		
}

int XSharedFile::Write( void * buf, int len )
{
	if(fd<=0) return 0;
	unsigned int s = 0;
	while(true)
	{
		char * temp = ((char*)buf)+s;
		int t = write(fd,temp,len-s);
		s+= t;

		if((s>=len)||t<=0)
			break;
	}
	return s;
}



void XSharedFile::Close()
{
	if(fd>0)
		close(fd);
	fd = -1;
}

int XSharedFile::FileLength()
{
	if(fd>0)
		return filelength(fd);
	return 0;
}

int XSharedFile::Tell()
{
	if(fd>0)
		return tell(fd);
	return 0;
}
