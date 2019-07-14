#include "HDFSFileMgr.h"
#include <fcntl.h>

HDFSFileSystem::HDFSFileSystem( const char * nn,short port )
{
	pBuilder = 0;
	filesys = 0;
	pBuilder = ngfsNewBuilder();
	ngfsBuilderSetNameNode(pBuilder,nn);
	ngfsBuilderSetNameNodePort(pBuilder,port);
	filesys = ngfsBuilderConnect(pBuilder);
}

HDFSFileSystem::~HDFSFileSystem()
{
	ngfsDisconnect(filesys);
	//ngfsFreeBuilder(pBuilder);
}



HDFSFileReader::HDFSFileReader(const char * ifilename)
:IFileReader(ifilename)
{
	currentoffset = 0;
	fileHandler = 0;
	filesys = 0;

}

HDFSFileReader::~HDFSFileReader(void)
{
	close();
}

bool HDFSFileReader::isvalid()
{
	return fileHandler!=0;
}


void HDFSFileReader::seek( long long offset )
{
	currentoffset = offset;
}

unsigned HDFSFileReader::read( void * buf,unsigned bufsize )
{
	if(currentoffset!=0)
	{
		tOffset pos = currentoffset + ngfsTell(filesys,fileHandler);
		currentoffset = 0;
		return ngfsPread(filesys,fileHandler,pos,buf,bufsize);
	}
	else
	{
		return ngfsRead(filesys,fileHandler,buf,bufsize);
	}
}


bool HDFSFileReader::open()
{
	fileHandler = ngfsOpenFile(filesys,filename,O_RDONLY,0,0,0);
	return fileHandler!=0;
}

void HDFSFileReader::gotohead()
{
	ngfsSeek(filesys,fileHandler,0);
}

void HDFSFileReader::build( HDFSFileSystem & hdfsFs )
{
	filesys = hdfsFs.GetFileSystem();
}

void HDFSFileReader::close()
{
	if(fileHandler)
	{
		ngfsCloseFile(filesys,fileHandler);
	}
	fileHandler = 0;
}


HDFSFileWriter::HDFSFileWriter( const char * ifilename )
:IFileWriter(ifilename)
{
	fileHandler = 0;
	filesys = 0;
}

HDFSFileWriter::~HDFSFileWriter()
{
		close();
}

void HDFSFileWriter::write( void * buf,unsigned bufsize )
{
	ngfsWrite(filesys,fileHandler,buf,bufsize);
}

void HDFSFileWriter::flush()
{
	ngfsFlush(filesys,fileHandler);
}

bool HDFSFileWriter::isvalid()
{
	return fileHandler!=0;
}

void HDFSFileWriter::bulid(HDFSFileSystem & hdfsFs)
{
	filesys = hdfsFs.GetFileSystem();
}

bool HDFSFileWriter::open()
{
	fileHandler = ngfsOpenFile(filesys,filename,O_WRONLY|O_CREAT,0,0,0);
	return fileHandler!=0;
}

void HDFSFileWriter::close()
{
	if(fileHandler)
	{
		flush();
		ngfsCloseFile(filesys,fileHandler);
	}
	fileHandler = 0;
}



