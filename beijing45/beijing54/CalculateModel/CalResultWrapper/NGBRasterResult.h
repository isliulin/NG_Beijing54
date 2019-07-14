#pragma once
#include "INGRasterResult.h"
#include "../HDFSFileWR/IFileManager.h"

#ifdef _MSC_VER
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif // _MSC_VER
struct NGBRasterHeader
{
	unsigned int w; //宽
	unsigned int h; //高

	//位置坐标
	double leftPos; //左基准值
	double bottomPos;//下基准值
	double xResolution; //x方向分辨率
	double yResolution;//y方向分辨率
	int geoSys;//系统坐标系

	//数值标识
	float factor; //数据缩放比例
	ECoverResultType eResultType;
	CalResult_Unit eResultUnit;
	short dataDefault;//数据默认值
	short dataVersion;//数据版本
};

#ifdef _MSC_VER
#pragma pack(pop)
#else
#pragma pack()
#endif // _MSC_VER

//栅格结果
class RESULT_API NGBRasterResult:public INGRaterResult
{

public:
	NGBRasterResult();
	~NGBRasterResult();

public:
	static bool CheckFile(const char * ifilename);
public:
	virtual NGRasterResultFormat GetRsultFormat() const {return RASTER_NGB;}
public:
	//创建一个栅格结果
	virtual int GenerateEmptyRaster(ECoverResultType iResultType,CalResult_DataType dataType,CalResult_Unit iResultUnit,
		int iGeoSys,double iLeft,double iBottom,unsigned int iw,unsigned int ih,double iXResolution,
		double iYResolution,float ifactor=10.0f);
	//栅格结果文件读写
	int ReadRaster(const char* filename);

	int ReadRasterBound(const char* filename);

	int WriteRaster(const char* filename);

	bool IsValid() const {return p_RasterData!=0;}
	//////////////////////////////////////////////////////////////////////////



protected:
	//空间尺寸
	NGBRasterHeader head;

	unsigned int pCount;//分组数目
	short ** p_RasterData;
protected:
	unsigned dataCount;
public:
	void SetInvalidValue(double inValue){head.dataDefault = (short)inValue;} 
	double GetInValidValue() const  {return head.dataDefault;}
public:
	unsigned int GetWidth() const {return head.w;}
	unsigned int GetHeight() const{ return head.h;}

	void SetLeftBottom(double l,double b){head.leftPos = l;head.bottomPos = b;}
	void GetLowerLeftCorner(double &l,double &b) const {l=head.leftPos; b=head.bottomPos;}
	void SetResolution(double xRes,double yRes){head.xResolution = xRes;head.yResolution = yRes;}
	void GetResolution(double &xRes,double &yRes) const {xRes = head.xResolution;yRes=head.yResolution;}
	void SetGeoSys(int sys) {head.geoSys = sys;}
	int GetCoordSysNumber() const {return head.geoSys;}
	virtual double GetResolutionX() const {return head.xResolution;}
	virtual double GetResolutionY() const {return head.yResolution;}
	virtual float GetDataFactor() const {return head.factor;}

	//
	void SetResultType(ECoverResultType iResultType) {head.eResultType = iResultType;}
	ECoverResultType GetCalResultType() const {return head.eResultType;}
	void SetResultUint(CalResult_Unit iResultUnit){head.eResultUnit = iResultUnit;}
	CalResult_Unit GetCalResultDataUnit() const {return head.eResultUnit;}
	NGBRasterHeader GetHead() const {return head;}

public:
	//获取到的实际值，非放大后的值
	double GetValueAsDouble(int x, int y) const  ;

	//传入实际值，非放大后的值
	void SetValue(int x,int y,double v);

	//获取到的实际值，非放大后的值
	bool GetValueByPos(double posX,double posY,double& val) const {return GetDataByPos(posX,posY,val);}

	void GetBound(double &l,double &b, double &r, double &t, int sys) const ;

public: 
	int CreateEmptyData(ECoverResultType iResultType,CalResult_Unit iResultUnit,int iGeoSys,double iLeft,double iBottom,
		double iXResolution,double iYResolution,unsigned int iw,unsigned int ih,float ifactor=10.0f);
	void ReleaseData();
	int CreateData(unsigned int iw,unsigned int ih,bool setDefalut = true,float ifactor = 10.0f);
	void SetDataByIndex(unsigned int x, unsigned int y,double val);
	void GetDataByIndex(unsigned int x, unsigned int y,double& val) const;

	void GetDataOnResolutionByIndex(unsigned int x, unsigned int y,double resolution,double& val) const;
	//
	bool SetDataByPos(double xpos,double ypos, double val);
	bool GetDataByPos(double xpos,double ypos, double &val) const;
	bool GetDataByPos(double xpos,double ypos, int sys,double &val) const;
	bool GetDataOnResolutionByPos( double xpos, double ypos,int sys,double resolution,double& val) const;



public: //file 
	int ReadHeaderInfoInFile(IFileReader * ifr);
	int ReadDataFromFile(IFileReader * ifr);
	int ReadIndexDataFromFile(const char * ifilename,int x, int y,double & dVal);
	int ReadIndexDataFromFile(IFileReader * ifr,int x, int y,double & dVal);

	int ReadPosDataFromFile(const char * ifilename,double xpos, double ypos,double & dVal,int sys =0);
	int ReadPosDataFromFile(IFileReader * ifr,double xpos, double ypos,double & dVal,int sys=0);

	int WriteDataToFile(IFileWriter *ifw);

protected:
	static void SwapHead(NGBRasterHeader & head);
	void SwapData();

};

 