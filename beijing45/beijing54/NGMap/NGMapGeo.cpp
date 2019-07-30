#include <math.h>
#include <iomanip>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <io.h>

#include "MapType.h"
#include "ParentChild.h"
#include "NGMapGeo.h"

#include <assert.h>

#include "../CommonTools/StringTools.h"
#include "../CommonTools/FileTools.h"
#include "../KoordTrans/KoordTrans/KoordTrans.h"

#if defined(_WIN32)||defined(_WIN64)
#define XSleep(s) Sleep((s)*1000)
#else
#include <unistd.h>
#define XSleep(s) sleep((s))
#endif

#ifndef _ASSERT
#define _ASSERT assert
#endif

#include <map>
#pragma warning(disable:4996)

bool ConvertFromStringToFileType(std::string& cstrFileType, FileType& ftType)
{
	ftType = Binary;
	return true;
	std::string strTmp = cstrFileType;
	stringTrimA(strTmp);
	stringUpperA(strTmp);

	if(strTmp == "TIFF")
		ftType = TIFFFILE;
	else
		if(strTmp == "TIFF(LZW)")
			ftType = LZWTIFF;
		else
			if(strTmp == "USERDEFINED")
				ftType = UserDefined;
			else
				if(strTmp == "TEXT")//"ASCII")
					ftType = ASCII;
				else
					if(strTmp == "COLORTABLE")
						ftType = ColorTable;
					else
						if(strTmp == "BINARY")
							ftType = Binary;
						else
							if(strTmp == "MATRIX")
								ftType = LSMatrixFile;
							else
								if(strTmp == "ASC")
									ftType = Asc;
								else
									if(strTmp == "X_Y_Value")
										ftType = X_Y_Value;
									else
										if(strTmp == "BIL,BIP,BSQ")
											ftType = BandGroup;
										else
											if(strTmp == "PLANET")
												ftType = Planet;
											else
												if(strTmp == "*.HDD; *.FED")
													ftType = TopoData;
												else
													if(strTmp == "COVERAGEDATA")
														ftType = CoverageData;
													else
														ftType = FT_UNKNOWN;
	return true;
}

bool ConvertFromStringToBitType(std::string& cstrBitType, BitType& btType)
{
	std::string strTmp = cstrBitType;
	stringTrimA(strTmp);
	stringUpperA(strTmp);

	if(strTmp == "CHAR")
		btType = _8Bit;
	else
		if(strTmp == "UNSIGNED_CHAR")
			btType =_8BitUnsigned;
		else
			if(strTmp == "SHORT")
				btType = _16BitSigned;
			else
				btType = _16BitSigned;
	return true;
}

bool ConvertFromStringToDirection(std::string& cstrDirection, EDirection& eDirection)
{
	std::string strTmp = cstrDirection;
	stringTrimA(strTmp);
	stringUpperA(strTmp);

	if(strTmp == "ROWS_TOP_TO_BOTTOM")
	{
		eDirection = eRowsTopToBottom;
	}
	else if(strTmp == "ROWS_BOTTOM_TO_TOP")
	{
		eDirection = eRowsBottomToTop;
	}
	else
	{
		return false;
	}

	return true;
}

bool ConvertFromStringToByteOrder(std::string& cstrByteOrder, EByteOrder& eByteOrder)
{
	std::string strTmp = cstrByteOrder;
	stringTrimA(strTmp);
	stringUpperA(strTmp);

	if(strTmp == "BIGENDIAN")
	{
		eByteOrder = eBigEndian;
	}
	else if(strTmp == "LITTLEENDIAN")
	{
		eByteOrder = eLittleEndian;
	}
	else
	{
		return false;
	}

	return true;
}


CNGMapGeo::CNGMapGeo()
:m_strDir("")
{
	m_XLowLeft = 0;
	m_YLowLeft = 0;						//左下角坐标值
	m_Xspacing = 0;
	m_Yspacing = 0;						//分辨率，每两个像素点之间的距离
	m_XAreaExtend = 0;					//整张地图大小
	m_YAreaExtend = 0;
	m_Tile_nX = 0;						//每一块像素点个数
	m_Tile_nY = 0;							//每一块像素点个数
	m_nWidth = 0;						//整张地图像素点个数
	m_nHeight = 0;
	m_DefaultValue = 0;

	m_eFileType = Binary;               //文件的类别,如Binary, Tiff等
	m_eBitType = _16BitSigned;
	memset(szPresentFilePath,0,MAX_FILE_PATH);
        memset(szCurrTileDir,0,MAX_FILE_PATH);
	memset(szLayerName,0,NameBytes);
	memset(szCoordShortName,0,NameBytes);
	memset(szMapDataTypeName,0,NameBytes);
	memset(szMapDataPrefixName,0,NameBytes);

	m_pTileInfo = NULL;
	m_nXBlocks = 0;							//X 方向地图块个数
	m_nYBlocks = 0;							//Y 方向地图块个数

	m_bReadOnlyFlag = true;					// read only flag
	//m_pProfile = NULL;

}

CNGMapGeo::~CNGMapGeo()
{
	if (m_pTileInfo != NULL)
		delete []m_pTileInfo;

	/*
	if (m_pProfile != NULL)
		delete m_pProfile;
	*/
}


//获取指定bittype的
int GetBitTypeByteCount(BitType eBitType)
{
	//默认字节数设置为2
	int nByteCounts = 2;
	switch(eBitType)
	{
	case _8Bit: nByteCounts = 1; break;
	case _8BitUnsigned: nByteCounts = 1; break;
	case _16BitSigned: nByteCounts = 2; break;
	default:
		nByteCounts = 2;
		break;
	}

	return nByteCounts;
}

int CNGMapGeo::CreateDefaultFile( const char * szFileName, double xmin, double ymin, double xmax, double ymax, double resolution, int nCoordSys )
{
	char buffer[1024]={0};
	strcpy(buffer,szFileName);
	PathRemoveFileNameA(buffer);
	if(access(buffer,0)!=0)
		mkdir(buffer);
	if (access(buffer,0) == 0)
	{
		GetFileNameA(szFileName,buffer);
		string temp = buffer;
		temp.erase(temp.find_last_of("."));

		//calculate param
		double	dxLowLeft = xmin;
		double  dyLowLeft = ymin;
		double  dspacing = resolution;
		if (resolution <= 0)
		{
			dspacing = 0.0001;
		}
		double  dxAreaExtend = xmax - xmin;
		double  dyAreaExtend = ymax - ymin;
		int     nTile_nX = 1000;
		int		nTile_nY = 1000;

		int		nWidth = ceil(dxAreaExtend/dspacing);
		int		nHeight = ceil(dyAreaExtend/dspacing);

		int		nXBlocks = ceil(double(nWidth)/nTile_nX);
		int		nYBlocks = ceil(double(nHeight)/nTile_nY);

		int nXSuffixWidth = 2;
		int nYSuffixWidth = 2;

		if (log10(double(nXBlocks))+1 > nXSuffixWidth)
		{
			nXSuffixWidth = log10(double(nXBlocks))+1;
		}
		if (log10(double(nYBlocks))+1 > nYSuffixWidth)
		{
			nYSuffixWidth = log10(double(nYBlocks))+1;
		}

		short nDefaultValue = 0x8181;
		string xSuffix = "00";
		string ySuffix = "00";
		if (nXSuffixWidth > 2)
		{
			for (int i = 2; i <= nXSuffixWidth; i++)
			{
				xSuffix += '0';
			}
		}
		if (nYSuffixWidth > 2)
		{
			for (int i = 2; i <= nYSuffixWidth; i++)
			{
				ySuffix += '0';
			}
		}

		FILE* pSream = fopen(szFileName, "w");
		fprintf(pSream, "\n[Filenames]\n");
		fprintf(pSream, "Prefix                                           = (cstring)                                \"%s\"\n",temp.c_str());
		fprintf(pSream, "Delimiter                                        = (cstring)                                    \"_\"\n");
		fprintf(pSream, "XSuffix                                          = (cstring)                                   \"%s\"\n",xSuffix.c_str());
		fprintf(pSream, "YSuffix                                          = (cstring)                                   \"%s\"\n",ySuffix.c_str());
		fprintf(pSream, "\n[DataDescription]\n");

		fprintf(pSream, "XPixel                                           = (long)                                      %d\n",nTile_nX);
		fprintf(pSream, "YPixel                                           = (long)                                      %d\n",nTile_nY);
		fprintf(pSream, "BitsPerPixel                                     = (long)                                        16\n");
		fprintf(pSream, "PixelDataType                                    = (cstring)                                \"short\"\n");
		fprintf(pSream, "FileType                                         = (cstring)                               \"Binary\"\n");
		fprintf(pSream, "ByteOrder                                        = (cstring)                            \"BigEndian\"\n");
		fprintf(pSream, "InvertByte                                       = (cstring)                                \"FALSE\"\n");
		fprintf(pSream, "OffsetBytes                                      = (long)                                         0\n");
		fprintf(pSream, "Multiplier                                       = (double)                            1.0000000000\n");
		fprintf(pSream, "Offset                                           = (double)                            0.0000000000\n");
		fprintf(pSream, "PresentationFile                                 = (cstring)                           \"%s\"\n",temp.c_str());
		fprintf(pSream, "Direction                                        = (cstring)                           \"Rows_Bottom_To_Top\"\n");
		
		fprintf(pSream, "\n[LayerDescription]\n");
		fprintf(pSream, "CoordSystem                                      = (cstring)                           \"Long - Lat  -WGS 84-\"\n");
		fprintf(pSream, "DataType                                         = (cstring)                           \"Topo\"\n");
		fprintf(pSream, "DefaultLayerName                                 = (cstring)                           \"%s\"\n",temp.c_str());
		fprintf(pSream, "ReferencePoint                                   = (cstring)                      \"LowerLeftCorner\"\n");
		fprintf(pSream, "Units                                            = (cstring)                               \"degree\"\n");
		fprintf(pSream, "RefPointX                                        = (double)                         %.6f\n",dxLowLeft);
		fprintf(pSream, "RefPointY                                        = (double)                           %.6f\n",dyLowLeft);
		fprintf(pSream, "AreaExtendX                                      = (double)                            %.6f\n",dxAreaExtend);
		fprintf(pSream, "AreaExtendY                                      = (double)                            %.6f\n",dyAreaExtend);
		fprintf(pSream, "ResolutionX                                      = (double)                            %.8f\n",dspacing);
		fprintf(pSream, "ResolutionY                                      = (double)                            %.8f\n",dspacing);
		fprintf(pSream, "DefaultValue                                     = (double)							%d\n",nDefaultValue);
		fclose(pSream);
	}
	return 0;
}


int CNGMapGeo::CreateDefaultBinaryFile()
{
	char blockfile[300] = {0};

	//创建每个块的二进制文件
	for (int y=0; y< m_nYBlocks; y++)
	{
		for(int x = 0; x < m_nXBlocks; x ++)
		{
			sprintf(blockfile,m_strDataFileFormat.c_str(),x+1,y+1);
			FILE* fp = fopen(blockfile, "w+b");
			if(fp != NULL)
			{

				long nDataNumber  = m_Tile_nY * m_Tile_nY;	//数据个数
				int nByteCounts = GetBitTypeByteCount( m_eBitType);

				char* szbuffer = (char*)malloc(nDataNumber * nByteCounts);
				memset(szbuffer,0x81,sizeof(char)*nDataNumber * nByteCounts);


				if (szbuffer != NULL)
				{
					fwrite(szbuffer,nByteCounts,nDataNumber,fp);
					fclose(fp);
				}
			}
		}
	}
	return 0;
}

// Read map data create on missing
bool CNGMapGeo::ReadMapDataCOM(const char *pszFilePath, double xmin, double ymin, double xmax, double ymax, double resolution, int nCoordSys)
{
	bool bRes = true;

	bool bCreateFlag = false;
	if(!IsFileExistsA(pszFilePath))
	{
		bCreateFlag = true;
		// create on missing
		CreateDefaultFile(pszFilePath, xmin, ymin, xmax, ymax, resolution, nCoordSys);
	}

	bRes = ReadMapData(pszFilePath);

	if (bCreateFlag)
	{
		CreateDefaultBinaryFile();
	}
	
	m_bReadOnlyFlag = false;

	return bRes;
}


bool CNGMapGeo::ReadMapData(const char *pszFilePath)
{
	if(!IsFileExistsA(pszFilePath))
		return false;		//文件不存在则直接返回 2010.11.19

	strcpy(szCurrTileDir,pszFilePath);
	PathRemoveFileNameA(szCurrTileDir);
	m_strDir = szCurrTileDir;
	m_strDir = m_strDir+ "/";// 地图数据文件夹目录

	ng_geo_init();

	std::string strPrefix;
	int nXSuffixWidth = 2;
	int nYSuffixWidth = 2;
	try
	{
		CParentChildFile ldfFile(pszFilePath);

		std::string strPrsFileName;
		ldfFile.GetElement("DataDescription","PresentationFile",strPrsFileName);//配色文件
		strPrsFileName = m_strDir  + strPrsFileName;
		strcpy(szPresentFilePath,strPrsFileName.c_str());

		ldfFile.GetElement("LayerDescription","RefPointX",m_XLowLeft);
		ldfFile.GetElement("LayerDescription","RefPointY",m_YLowLeft);

		ldfFile.GetElement("DataDescription","XPixel",m_Tile_nX);		//每个地图块大小
		ldfFile.GetElement("DataDescription","YPixel",m_Tile_nY);

		ldfFile.GetElement("LayerDescription","ResolutionX",m_Xspacing);
		ldfFile.GetElement("LayerDescription","AreaExtendX",m_XAreaExtend);
		//edit by jjj 2012.12.17
		//分辨率为度时,小数位多,可能造成m_nWidth,m_nHeight计算取整时因精度问题少1
		//所有这里取整之前加0.5确保m_nWidth,m_nHeight正确
		//m_nWidth = (long)(m_XAreaExtend/m_Xspacing);
		m_nWidth = (long)(m_XAreaExtend/m_Xspacing+0.5);

		ldfFile.GetElement("LayerDescription","ResolutionY",m_Yspacing);
		ldfFile.GetElement("LayerDescription","AreaExtendY",m_YAreaExtend);
		m_nHeight = (long)(m_YAreaExtend/m_Yspacing+0.5);

		int nValueTemp = 0;
		ldfFile.GetElement("LayerDescription","DefaultValue",nValueTemp);
		m_DefaultValue = nValueTemp;

		std::string strCoordSystem;
		ldfFile.GetElement("LayerDescription","CoordSystem",strCoordSystem);
		strcpy(szCoordShortName,strCoordSystem.c_str());
		m_nCoordSys = ng_GetCoordNoFromName(szCoordShortName);

		std::string strDataType;
		ldfFile.GetElement("LayerDescription","DataType",strDataType);			//地图类别字符串
		strcpy(szMapDataTypeName,strDataType.c_str());

		std::string strLayerName;
		ldfFile.GetElement("LayerDescription","DefaultLayerName",strLayerName);	//地图类别字符串
		strcpy(szLayerName,strLayerName.c_str());

		std::string strSuffix;
		ldfFile.GetElement("Filenames", "XSuffix", strSuffix);
		stringTrimA(strSuffix);
		nXSuffixWidth = strSuffix.length();

		ldfFile.GetElement("Filenames", "YSuffix", strSuffix);
		stringTrimA(strSuffix);
		nYSuffixWidth = strSuffix.length();

		ldfFile.GetElement("Filenames", "Prefix", strPrefix);

		//Add by Liuqingmei@20111207
		//读取文件的类型,如TIFF,BINARY等
		std::string strFileType;
		ldfFile.GetElement("DataDescription", "FileType", strFileType);
		ConvertFromStringToFileType(strFileType, m_eFileType);

		//读取文件中的像素的类型
		std::string strPixelType;
		ldfFile.GetElement("DataDescription", "PixelDataType", strPixelType);
		ConvertFromStringToBitType(strPixelType, m_eBitType);

		//读取数据的方向
		std::string strDirection;
		ldfFile.GetElement("DataDescription", "Direction", strDirection);
		ConvertFromStringToDirection(strDirection, m_eDirection);

		//读取字节序
		std::string strByteOrder;
		ldfFile.GetElement("DataDescription", "ByteOrder", strByteOrder);
		ConvertFromStringToByteOrder(strByteOrder, m_eByteOrder);
	}
	catch (...)
	{
		return false;
	}

	if (m_nWidth <= 0 || m_nHeight <= 0 || m_Tile_nX <= 0 || m_Tile_nY <= 0)
		return false;

	m_nXBlocks = m_nWidth / m_Tile_nX;
	m_nYBlocks = m_nHeight / m_Tile_nY;
	if (m_nXBlocks <= 0 || m_nYBlocks <= 0 )
		return false;

	if (m_pTileInfo != NULL)
		delete []m_pTileInfo;
	m_pTileInfo = new TILEINFO[m_nXBlocks*m_nYBlocks];	//总共块的个数
	if (m_pTileInfo == NULL)
		return false;

	int nIndex = 0;
	std::ostringstream ostrTmp;
	ostrTmp<<m_strDir<<strPrefix<<'_'<<"%0"<<nXSuffixWidth<<"d_%0"<<nYSuffixWidth<<"d";
	m_strDataFileFormat = ostrTmp.str();
	for (int y=0; y< m_nYBlocks; y++)
	{
		for(int x = 0; x < m_nXBlocks; x ++)
		{
			nIndex = y*m_nXBlocks+x;
			m_pTileInfo[nIndex].InitMapInfo(this,x,y);
		}
	}

	return true;
}

short CNGMapGeo::ShortElement(int x, int y)
{
	//debug 下使用
	_ASSERT (m_pTileInfo != NULL && m_nXBlocks > 0 &&m_nYBlocks > 0);

	POINT ptPos;
	if (HitTile(x,y,ptPos))
	{
		int nIndex = (ptPos.y-1) *m_nXBlocks + (ptPos.x-1);
		TILEINFO* pInfo = &m_pTileInfo[nIndex];
		POINT ptOrg;
		ptOrg.x = m_Tile_nX *(ptPos.x - 1);
		ptOrg.y = m_Tile_nY *(ptPos.y - 1);
		return pInfo->ShortElement(x - ptOrg.x,y - ptOrg.y);
	}

	return m_DefaultValue;				//返回缺省值
}

short CNGMapGeo::ShortElement(double dx, double dy, int CoordSys)
{	
	_ASSERT (m_pTileInfo != NULL && m_nXBlocks > 0 &&m_nYBlocks > 0);

	if (CoordSys != m_nCoordSys)
	{
		ng_geo_trans(CoordSys,m_nCoordSys,dx,dy,&dx,&dy);
	}

	int x = (int)((dx - m_XLowLeft)/m_Xspacing);
	int y = (int)((dy - m_YLowLeft)/m_Yspacing);
	POINT ptPos;
	if (HitTile(x,y,ptPos))
	{
		int nIndex = (ptPos.y-1) *m_nXBlocks + (ptPos.x-1);
		TILEINFO* pInfo = &m_pTileInfo[nIndex];
		POINT ptOrg;
		ptOrg.x = m_Tile_nX *(ptPos.x - 1);
		ptOrg.y = m_Tile_nY *(ptPos.y - 1);
		return pInfo->ShortElement(x - ptOrg.x,y - ptOrg.y);
	}

	return m_DefaultValue;				//返回缺省值
}


void CNGMapGeo::SetShortElement(double dx, double dy, int CoordSys, short val)
{	
	_ASSERT (m_pTileInfo != NULL && m_nXBlocks > 0 &&m_nYBlocks > 0);

	if (CoordSys != m_nCoordSys)
	{
		ng_geo_trans(CoordSys,m_nCoordSys,dx,dy,&dx,&dy);
	}

	int x = (int)((dx - m_XLowLeft)/m_Xspacing);
	int y = (int)((dy - m_YLowLeft)/m_Yspacing);
	POINT ptPos;
	if (HitTile(x,y,ptPos))
	{
		int nIndex = (ptPos.y-1) *m_nXBlocks + (ptPos.x-1);
		TILEINFO* pInfo = &m_pTileInfo[nIndex];
		POINT ptOrg;
		ptOrg.x = m_Tile_nX *(ptPos.x - 1);
		ptOrg.y = m_Tile_nY *(ptPos.y - 1);
		
		pInfo->SetShortElement(x - ptOrg.x,y - ptOrg.y, val);
	}
}

int CNGMapGeo::GetMapDataType()
{
	std::string strTemp(szMapDataTypeName);
	return GetDataTypeFromStr(strTemp);
}

INGMapGeo *NG_CreateMapGeo()
{
	INGMapGeo *pRet = new CNGMapGeo;
	return pRet;
}

void NG_ReleaseMapGeo(INGMapGeo *PMap)
{
	if (PMap != NULL)
		delete PMap;
}


bool CNGMapGeo::HitTile(int nImgX,int nImgY, POINT& ptPos)
{
	//2012.2.1
	//(nImgX,nImgY)点落在地图之外，返回FALSE
 	if (nImgX >= m_nWidth || nImgX < 0 || nImgY >= m_nHeight || nImgY < 0)
 		return false;

	ptPos.x = nImgX / m_Tile_nX + 1;
	ptPos.y = nImgY / m_Tile_nY + 1;

	//仅debug情况下作判断，因为HitTile 将被不停调用
	_ASSERT(ptPos.x > 0 && ptPos.y > 0);

	return true;
}

NGProfile *CNGMapGeo::GetProfile(POINT &ptBegin, POINT &ptEnd,NGProfile *m_pProfile)
{
	//Modify by Liuqm@20140110--因为经常会出现点在地图外的情况，目前还没有想到更好的方法
	//暂时先在取地图高度的地方做了处理，所以去掉此处的断言
// 	_ASSERT(ptBegin.x >= 0 && ptBegin.x < m_nWidth);
// 	_ASSERT(ptBegin.y >= 0 && ptBegin.y < m_nHeight);
	//modify end
	/*
	_ASSERT(m_pProfile != NULL && m_pProfile->pImgCoordX != NULL &&
		m_pProfile->pImgCoordY != NULL && m_pProfile->pImgData != NULL &&
		m_pProfile->pDistance != NULL);
		*/
	if(m_pProfile==NULL)
		return NULL;
	// only have one point
	if (ptBegin.x == ptEnd.x && ptBegin.y == ptEnd.y)
	{
		m_pProfile->nPointsNum = 0;
		return m_pProfile;
	}

	int x = ptBegin.x;
	int y = ptBegin.y;

	int i;
	int xstep = 1;
	int ystep = 1;

	// two points is in a vertical line
	if (ptBegin.x == ptEnd.x)
	{
		if (ptEnd.y > ptBegin.y)
			m_pProfile->nPointsNum = ptEnd.y - ptBegin.y;
		else
		{
			m_pProfile->nPointsNum = ptBegin.y - ptEnd.y;
			ystep = -1;
		}

		//如果profile的空间不能满足profile的需求，则需要扩容
		if(m_pProfile->nPointsNum >= m_pProfile->nSize)
		{
			long nPointsNum = m_pProfile->nPointsNum;
			if(m_pProfile->Resize(nPointsNum) == false)
				return NULL;
			m_pProfile->nPointsNum = nPointsNum;
		}

		for (i = 0, y = ptBegin.y; i <= m_pProfile->nPointsNum; i++, y+=ystep)
		{
			m_pProfile->pImgCoordX[i] = ptBegin.x;
			m_pProfile->pImgCoordY[i] = y;
			m_pProfile->pImgData[i] = ShortElement(ptBegin.x,y);
			m_pProfile->pDistance[i] = (double)i*m_Yspacing;
		}
	}
	// two points is in a horizontal line
	else if (ptBegin.y == ptEnd.y)
	{
		if (ptEnd.x > ptBegin.x)
			m_pProfile->nPointsNum = ptEnd.x - ptBegin.x ;
		else
		{
			m_pProfile->nPointsNum = ptBegin.x - ptEnd.x ;
			xstep = -1;
		}

		//如果profile的空间不能满足profile的需求，则需要扩容
		if(m_pProfile->nPointsNum >= m_pProfile->nSize)
		{
			long nPointsNum = m_pProfile->nPointsNum;
			if(m_pProfile->Resize(nPointsNum) == false)
				return false;
			m_pProfile->nPointsNum = nPointsNum;
		}

		for (i = 0, x = ptBegin.x; i <= m_pProfile->nPointsNum; i++, x+=xstep)
		{
			m_pProfile->pImgCoordX[i] = x;
			m_pProfile->pImgCoordY[i] = ptBegin.y;
			m_pProfile->pImgData[i] = ShortElement(m_pProfile->pImgCoordX[i],m_pProfile->pImgCoordY[i]);
			m_pProfile->pDistance[i] = (double)i*m_Xspacing;
		}
	}
	else
	{
		// default: Bresenham Line
		int dx, dy;
		int e;

		// dx: distance between two points in X direction
		if (ptEnd.x > ptBegin.x)
			dx = ptEnd.x - ptBegin.x;
		else
		{
			dx = ptBegin.x - ptEnd.x;
			xstep = -1;
		}

		// dy: distance between two points in Y direction
		if (ptEnd.y > ptBegin.y)
			dy = ptEnd.y - ptBegin.y;
		else
		{
			dy = ptBegin.y - ptEnd.y;
			ystep = -1;
		}

		double dXtmp = 0.0;
		double dYtmp = 0.0;

		if (dx > dy)
		{
			e = -dx;
			m_pProfile->nPointsNum = dx;
			//如果profile的空间不能满足profile的需求，则需要扩容
			if(m_pProfile->nPointsNum >= m_pProfile->nSize)
			{
				long nPointsNum = m_pProfile->nPointsNum;
				if(m_pProfile->Resize(nPointsNum) == false)
					return NULL;
				m_pProfile->nPointsNum = nPointsNum;
			}
			for (i = 0; i <= dx; i++)
			{
				m_pProfile->pImgCoordX[i] = x;
				m_pProfile->pImgCoordY[i] = y;
				m_pProfile->pImgData[i] = ShortElement(x,y);

				dXtmp = ((double)(x-ptBegin.x)) * m_Xspacing;
				dYtmp = ((double)(y-ptBegin.y)) * m_Xspacing;
				m_pProfile->pDistance[i] = sqrt(pow(dXtmp,2) + pow(dYtmp,2));

				x += xstep;
				e += 2 * dy;
				if (e >= 0)
				{
					y += ystep;
					e -= 2 * dx;
				}
			}
		}
		else
		{
			e = -dy;
			m_pProfile->nPointsNum  = dy;
			//如果profile的空间不能满足profile的需求，则需要扩容
			if(m_pProfile->nPointsNum >= m_pProfile->nSize)
			{
				long nPointsNum = m_pProfile->nPointsNum;
				if(m_pProfile->Resize(nPointsNum) == false)
					return NULL;
				m_pProfile->nPointsNum = nPointsNum;
			}
			for (i = 0; i <= dy; i++)
			{
				m_pProfile->pImgCoordX[i] = x;
				m_pProfile->pImgCoordY[i] = y;
				m_pProfile->pImgData[i] = ShortElement(x,y);

				dXtmp = ((double)(x-ptBegin.x)) * m_Xspacing;
				dYtmp = ((double)(y-ptBegin.y)) * m_Xspacing;
				m_pProfile->pDistance[i] = sqrt(pow(dXtmp,2) + pow(dYtmp,2));

				y += ystep;
				e += 2 * dx;
				if (e >= 0)
				{
					x += xstep;
					e -= 2 * dy;
				}
			}
		}// else
	}

	//对profile中的无效值做处理
	short nDefaultValue = m_DefaultValue;
	for(i=0; i<=m_pProfile->nPointsNum; i++)
	{
		if(m_pProfile->pImgData[i] == nDefaultValue)
		{
			m_pProfile->pImgData[i] = 0;
		}
	}
	return m_pProfile;
}

void CNGMapGeo::ReleaseTitleData(POINT &ptPos)
{

	if (ptPos.x > 0 && ptPos.x <= m_nXBlocks && ptPos.y > 0 && ptPos.y <= m_nYBlocks)
	{
		int x = ptPos.x - 1;
		int y = ptPos.y - 1;
		int nIndexTemp = y*m_nXBlocks+x;
		m_pTileInfo[nIndexTemp].ReleaseData();
	}
}

void CNGMapGeo::ReleaseMapData()
{
	if (m_pTileInfo != NULL)
	{
		int nIndex = 0;
		for (int i=0; i< m_nYBlocks; i ++)
		{
			for(int j = 0; j < m_nXBlocks; j ++)
			{
				nIndex = i*m_nXBlocks+j;
				m_pTileInfo[nIndex].ReleaseData();			//该块数据已经加载进内存
			}
		}
	}
}


void CNGMapGeo::ReleaseParticalTitle( int nXIndex,int nYIndex,int resverblock)
{

	if((nXIndex>=m_nXBlocks)||(nYIndex>=m_nYBlocks)||(nXIndex<0)||(nYIndex<0))
		return ;
	if(resverblock <2)
		resverblock = 2; //至少保留周边两块
	if(!m_pTileInfo)
		return;
	//释放离开resverblock块距离的数据
	for(int x=0;x<m_nXBlocks;x++)
	{
		for(int y=0;y<m_nYBlocks;y++)
		{
			if((labs(x-nXIndex)>resverblock)
				&&(labs(y-nYIndex)>resverblock))
				m_pTileInfo[y*m_nXBlocks+x].ReleaseData();
		}
	}

}

CNGGISMapManger::CNGGISMapManger()
{
	omp_init_lock(&m_lock);
}

CNGGISMapManger::~CNGGISMapManger()
{
	omp_set_lock(&m_lock);
	map<string,CNGMapIndex>::iterator it;
	for(it=gismaps.begin();it!=gismaps.end();it++)
	{
		INGMapGeo * p = it->second.pMap;
		if(p)
			delete p;
	}
	gismaps.clear();
	omp_unset_lock(&m_lock);
	omp_destroy_lock(&m_lock);
}

INGMapGeo * CNGGISMapManger::Find( string mappath )
{
	INGMapGeo * pGis = NULL;
	omp_set_lock(&m_lock);
	map<string,CNGMapIndex>::iterator it = gismaps.find(mappath);
	if(it!= gismaps.end())
	{
		it->second.useindex ++;
		pGis = it->second.pMap;
	}
	else
	{
		if(IsFileExistsA(mappath.c_str()))
		{
			CNGMapGeo * pNGGis = new CNGMapGeo();
			if(!pNGGis->ReadMapData(mappath.c_str()))
				delete pNGGis;
			else
			{
				pGis = pNGGis;
				CNGMapIndex pMapIndex = {pNGGis,1};
				gismaps.insert(make_pair(mappath,pMapIndex));
			}
		}
	}
	omp_unset_lock(&m_lock);
	return pGis;
}

void CNGGISMapManger::ReleaseMap( string mappath )
{
	omp_set_lock(&m_lock);
	map<string,CNGMapIndex>::iterator it = gismaps.find(mappath);
	if(it!= gismaps.end())
	{
		it->second.useindex -- ;
		if(it->second.useindex<=0)
		{
			INGMapGeo * p = it->second.pMap;
			if(p)
				delete p;
			gismaps.erase(it);
		}
	}
	omp_unset_lock(&m_lock);
}

CNGGISMapManger global_gismanager;

INGMapGeo* NG_FindGisMap(const char * gismapPath)
{
	if(gismapPath)
		return global_gismanager.Find(gismapPath);
	return NULL;
}
void NG_ReleaseGisMap(const char * gismapPath)
{
	if(gismapPath)
		global_gismanager.ReleaseMap(gismapPath);
}


