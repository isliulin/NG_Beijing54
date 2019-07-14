
#include <io.h>
#include <direct.h>
#include <float.h>
#include <omp.h>
#include "NGStandProcessExport.h"
#include "NGDataProcess.h"
#include "ccsv_parser.h"
#include "..\KoordTrans\KoordTrans.h"
#include "NGNaturalNeigbours.h"
#include "ErrorCode.h"



vector<string> GetFilesByDir(const char* pDirPath)
{
	vector<string> fPath;
	string fileName;
	long hFile=0;
	struct _finddata_t fileinfo;
	if((hFile=_findfirst(fileName.assign(pDirPath).append("\\*").c_str(),&fileinfo))!=-1)
	{
		do 
		{
			if(fileinfo.attrib&_A_SUBDIR)
				continue;
			fPath.push_back(fileName.assign(pDirPath).append("\\").append(fileinfo.name));
		} while (_findnext(hFile,&fileinfo)==0);
		_findclose(hFile);
	}
	return fPath;
}



int NG_StandDataPreProcess(const char* pSrcDir,const char* pResultDir)
{
	if (NULL == pSrcDir || NULL == pResultDir)
	{
		return POINT_CAN_NOT_NULL;
	}
	if (access(pResultDir,0) != 0)
	{
		mkdir(pResultDir);//如果文件夹不存在，则创建
	}
	char temp[512];
 	sprintf(temp,"%s\\Signal",pResultDir);
	{
		CNGDataProcess process;
		int nRes =  process.DecodeStandData(pSrcDir,temp);
		if (SUCCESS != nRes)
		{
			return nRes;
		}
	}
	vector<string> allfreqfiles = GetFilesByDir(temp);
	if (allfreqfiles.size() == 0 )
	{
		return NO_SOURCE_FILE;
	}
	sprintf(temp,"%s\\NGZResult",pResultDir);
	if (access(temp,0) != 0)
	{
		mkdir(temp);//如果文件夹不存在，则创建
	}
	ng_geo_init();
	for (int i = 0 ; i < allfreqfiles.size() ; i ++)
	{
		NGDataVector sites;
		double minx = DBL_MAX;
		double miny = minx;
		double maxx = DBL_MIN;
		double maxy = DBL_MIN;
		NGPOINT bottom;
		{
			FILE* fp = fopen(allfreqfiles[i].c_str(),"rb");
			if (NULL == fp)
			{
				continue;
			}
			fseek(fp,0,SEEK_END);
			int length = ftell(fp)/DATASIZE;
			sites.resize(length);
			fseek(fp,0,SEEK_SET);
			for (int i = 0 ; i < length ; i ++)
			{
				fread(&sites[i],DATASIZE,1,fp);
				minx = minx > sites[i].x? sites[i].x:minx;
				if (fabs(miny - sites[i].y) < 0.000001 && bottom.x > sites[i].y)
				{
					bottom.x = sites[i].x;
					bottom.y = miny;
				}else if (miny > sites[i].y)
				{
					miny = sites[i].y;
					bottom.x = sites[i].x;
					bottom.y = miny;
				}
				miny = miny > sites[i].y?sites[i].y:miny;
				maxx = maxx > sites[i].x? maxx:sites[i].x;
				maxy = maxy > sites[i].y?maxy : sites[i].y;
				ng_geo_trans(103,PlaneCoord,sites[i].x,sites[i].y,&sites[i].x,&sites[i].y);
				
			}
		}
		CNGNaturalNeigbours NatProcess;
		NatProcess.SetWGSLeftBottom(minx,miny);

		//返回插值的矩形框

		double lb_x,lb_y;
		double lt_x,lt_y;
		double rb_x,rb_y;
		double rt_x,rt_y;

		ng_geo_trans(103,PlaneCoord,minx , miny ,&lb_x,&lb_y);
		ng_geo_trans(103,PlaneCoord,maxx ,maxy  ,&rt_x,&rt_y);
		ng_geo_trans(103,PlaneCoord,minx , maxy ,&lt_x,&lt_y);
		ng_geo_trans(103,PlaneCoord,maxx ,miny  ,&rb_x,&rb_y);
		//先合并相同点以及相同栅格内的点

		minx = lb_x<lt_x?lb_x:lt_x;
		miny = lb_y<rb_y?lb_y:rb_y;
		maxx = rb_x>rt_x?rb_x:rt_x;
		maxy = lt_y>rt_y?lt_y:rt_y;
		CNGDataProcess::ProcessSamePoint(sites,MAPRESULTION);

		ng_geo_trans(103,PlaneCoord,bottom.x,bottom.y,&bottom.x,&bottom.y);
		
		std::string fileName = allfreqfiles[i];
		int nPos = fileName.find_last_of("_");
		fileName = fileName.substr(nPos+1);
		nPos = fileName.find_last_of(".");
		fileName = fileName.substr(0,nPos);
		sprintf(temp,"%s\\NGZResult\\Result_%s.ngz",pResultDir,fileName.c_str());
		NatProcess.DoNatNeInterpolation(sites,MAPRESULTION,minx,miny,maxx,maxy,bottom,temp);
	}
	return SUCCESS;

}

int NG_StandDataDilute(const char* pSrcDir,unsigned __int32 freqBand,const char* pResultFile)
{
	CNGDataProcess process;
	return process.StandDataDilute(pSrcDir,freqBand,pResultFile);
}

