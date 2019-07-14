#ifndef __CAL__RASTER__RESULT__H__
#define __CAL__RASTER__RESULT__H__

#include "INGRasterResult.h"

#ifdef _MSC_VER
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif // _MSC_VER
struct NGZRasterHeader
{	
	ECoverResultType eResultType;
	CalResult_Unit eResultUnit;
	CalResult_DataType eDataType;
	int geoSys;//系统坐标系

	//位置坐标
	double leftPos; //左基准值
	double bottomPos;//下基准值
	double xResolution; //x方向分辨率
	double yResolution;//y方向分辨率

	unsigned int w; //宽
	unsigned int h; //高
};

#ifdef _MSC_VER
#pragma pack(pop)
#else
#pragma pack()
#endif // _MSC_VER


//栅格结果
class RESULT_API NGZRasterResult:public INGRaterResult
{

public:
	NGZRasterResult();
	~NGZRasterResult();
public:
	static bool CheckFile(const char * ifilename);
public:
	virtual NGRasterResultFormat GetRsultFormat() const {return RASTER_NGZ;}
protected:
	NGZRasterHeader head; //文件头
protected:
	unsigned int pCount;//分组数目
	void ** p_RasterData;
protected:
	unsigned dataCount;
public:
	void ReleaseData();

public:
	//创建一个栅格结果,忽视放大因子
	virtual int GenerateEmptyRaster(ECoverResultType iResultType,CalResult_DataType dataType,CalResult_Unit iResultUnit,
		int iGeoSys,double iLeft,double iBottom,unsigned int iw,unsigned int ih,double iXResolution,
		double iYResolution,float ifactor=1.0f);

	int CreateData(unsigned iw,unsigned ih,bool setDefault);

	//栅格结果文件读写
	int ReadRaster(const char* filename);

	int ReadRasterBound(const char* filename);

	int WriteRaster(const char* filename);

	bool IsValid() const {return p_RasterData!=0;}

public:
	virtual int GetCoordSysNumber() const {return head.geoSys;}
	virtual void GetLowerLeftCorner (double &x,double &y) const {x=head.leftPos,y=head.bottomPos;}
	virtual unsigned GetWidth() const { return head.w;}
	virtual unsigned GetHeight()const {return head.h;}
	virtual double GetResolutionX()const {return head.xResolution;}
	virtual double GetResolutionY()const {return head.yResolution;}

	virtual ECoverResultType GetCalResultType() const {return head.eResultType;}
	virtual CalResult_Unit GetCalResultDataUnit() const {return head.eResultUnit;}

	virtual float GetDataFactor() const {return 1;}

public:
	virtual double GetValueAsDouble(int x, int y) const;
	virtual void SetValue(int x,int y,double v);
	virtual bool GetValueByPos(double posX,double posY,double& val) const;

	//以一定分辨率取以x,y为中心，指定resolution的均值
	virtual void GetDataOnResolutionByIndex(unsigned int x, unsigned int y,double resolution,double& val) const;
	//以指定坐标系取值，sys=0时表示自身坐标系
	virtual bool GetDataByPos(double xpos,double ypos, int sys,double &val) const;

	//以指定坐标系获取结果范围，sys=0时表示自身坐标系
	virtual void GetBound(double &l,double &b, double &r, double &t, int sys) const;

	//直接从文件中读取数值
	int ReadIndexDataFromFile(const char * ifilename,int x, int y,double &val);
	int ReadPosDataFromFile(const char * ifilename,double xpos, double ypos,double &val,int sys=0);

protected:
	static void SwapHead(NGZRasterHeader & head);

	void SwapData();
};


#endif   