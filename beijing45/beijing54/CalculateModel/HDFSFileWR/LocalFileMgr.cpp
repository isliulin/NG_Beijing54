#include "LocalFileMgr.h"

const unsigned  MaxFileSize = ((1<<31)-(1<<24));

LocalFileMgr::LocalFileMgr(void)
{
}

LocalFileMgr::~LocalFileMgr(void)
{
}

LocalFileReader::LocalFileReader( const char * ifilename )
:IFileReader(ifilename)
{
	fp = 0;
	subfile = 0;
	cur_pos = 0;
	flength = 0;
}

LocalFileReader::~LocalFileReader( void )
{
	close();
}

bool LocalFileReader::open()
{
	if(fp) close();
	fp = fopen(filename,"rb");
	if(fp)
	{
		getflength();
	}
	cur_pos = 0;
	return fp!=0;
}

void LocalFileReader::close()
{
	if(fp)
		fclose(fp);
	fp = 0;
	cur_pos = 0;
	flength = 0;
}

void LocalFileReader::seek( long long offset )
{
	if(!fp) return;
	if(offset<=0)
		//fseek(fp,offset,SEEK_CUR);
		_fseeki64(fp,offset,SEEK_CUR);
	else
	{
		long long first = offset,second = 0;
		if(splitfile(first,first,second))
		{
			if(opensubfile()&&(second>0))
				//fseek(fp,second,SEEK_SET);
				_fseeki64(fp,second,SEEK_SET);
		}
		else
			//fseek(fp,offset,SEEK_CUR);
			_fseeki64(fp,offset,SEEK_CUR);
	}
}

bool LocalFileReader::isvalid()
{
	return fp!=0;
}

void LocalFileReader::gotohead()
{
	if(fp)
		_fseeki64(fp,0,SEEK_SET);
		//fseek(fp,0,SEEK_SET);
	cur_pos = 0;
}

bool LocalFileReader::splitfile( long long total,long long & first,long long &second )
{
	if(fp)
	{
		//cur_pos =  ftell(fp);
		cur_pos = _ftelli64(fp);
		if((cur_pos+total)>flength)
		{
			first = flength-cur_pos;
			second = total - first;
			return true;
		}
	}
	return false;
}

bool LocalFileReader::opensubfile()
{
	close();
	char newfile[300]={0};
	sprintf(newfile,"%s_s%u",filename,subfile++);
	fp = fopen(newfile,"rb");
	getflength();
	return fp!=0;
}

unsigned int LocalFileReader::read( void * buf,unsigned bufsize )
{
	if(!fp) return 0;
	unsigned int s = 0;
	long long first = bufsize,second=0;
	if(splitfile(bufsize,first,second))
	{
		if(first>0)
		{
			s+=read(buf,first);
		}
		if(opensubfile()&&(second>0))
		{
			char * temp = ((char*)buf)+first;
			s+=read(temp,second);
		}
	}
	else
	{
		while(true)
		{
			char * temp = ((char*)buf)+s;
			unsigned t = fread(temp,1,bufsize-s,fp);
			s+= t;

			if((s>=bufsize)||t<=0 || feof(fp))
				break;
		}
	}
	return s;
}

bool LocalFileReader::IsEnd()
{
	if(!fp)return true;
	return feof(fp)!=0;
}

long long LocalFileReader::getflength()
{
	if(fp&&(flength==0))
	{
		cur_pos = ftell(fp);
		//fseek(fp,0,SEEK_END);
		_fseeki64(fp,0,SEEK_END);
		flength = _ftelli64(fp);//ftell(fp);
		//fseek(fp,cur_pos-flength,SEEK_END);
		_fseeki64(fp,cur_pos-flength,SEEK_END);
	}
	return flength;
}

LocalFileWriter::LocalFileWriter( const char * ifilename )
:IFileWriter(ifilename)
{
	fp = 0;
	subfile = 0;
	curSize = 0;
}

LocalFileWriter::~LocalFileWriter()
{
	close();
}

bool LocalFileWriter::open( const char * mode/*="wb"*/ )
{
	if(fp)close();
	fp = fopen(filename,mode);
	return fp!=0;
	curSize = 0;
}

bool LocalFileWriter::open()
{
	return open("wb");
}

void LocalFileWriter::close()
{
	if(fp)
		fclose(fp);
	fp = 0;
	curSize = 0;
	

}

void LocalFileWriter::write( void * buf,unsigned bufsize )
{
	//
	if(fp)
	{
		unsigned s = 0;
		while(true)
		{
			char * temp = ((char*)buf)+s;
			unsigned t = fwrite(temp,1,bufsize-s,fp);
			s+= t;
			if(s==bufsize)
				break;
			else if((s>bufsize)||(t==0))
			{
				break;
			}
		}
		curSize += bufsize;
	}
}

void LocalFileWriter::flush()
{
	if(fp)
		fflush(fp);
}

bool LocalFileWriter::isvalid()
{
	return fp!=0;
}

void LocalFileWriter::checkLength( unsigned size )
{
	if((curSize+size)>MaxFileSize)
	{
		close();
		char newfile[300]={0};
		sprintf(newfile,"%s_s%u",filename,subfile++);
		fp = fopen(newfile,"wb");
	}
}

