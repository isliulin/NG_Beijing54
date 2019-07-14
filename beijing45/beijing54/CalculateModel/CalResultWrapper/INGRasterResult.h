#pragma once
#include "CalResultWrapper.h"

//目前NG的几种二进制栅格文件格式

enum NGRasterResultFormat
{
	RASTER_NULL, //表示未知的格式
	RASTER_NGZ, //压缩格式的ngz文件
	RASTER_NGZS,//有放大因子的ngz文件
	RASTER_NGB, //非压缩格式的ngb文件
	RASTER_NGR // NGRadioPlan的二进制结果文件
};

enum EValueAverageType
{
	RANGE_AVERAGE, //在范围内的值直接平均
	RANGE_AVERAGE_POW, //转成自然数值，10log
	RANGE_AVERAGE_POW2,//转成自然数值，20log
	RANGE_MAX,//取最大值
};

//判断值是否无效的判决条件
#define IS_VALID_RASTER_VALUE(x) ((x)>-9000&&(x)<9000)

#ifndef NG_DELETE_SINGLE
#define  NG_DELETE_SINGLE(P) if(P) delete P; P=0;
#endif

class RESULT_API INGRaterResult
{

public:
	//根据需要格式创建对象
	static INGRaterResult * CreateRaster(NGRasterResultFormat format);
	//获取文件的格式
	static NGRasterResultFormat CheckRasterFileFormat(const char * file);
	//释放由该dll创建的对象
	static void DestroyRaster(INGRaterResult*& pRaster);

public:
	INGRaterResult(void){}
	virtual ~INGRaterResult(void){}
public:
	virtual NGRasterResultFormat GetRsultFormat() const = 0;
public:
	//初始化栅格结果结构数据,如果成功返回0,否则非零值
	virtual int GenerateEmptyRaster(ECoverResultType iResultType,CalResult_DataType dataType,CalResult_Unit iResultUnit,
		int iGeoSys,double iLeft,double iBottom,unsigned int iw,unsigned int ih,double iXResolution,
		double iYResolution,float ifactor=10.0f) = 0;

	//栅格结果文件读写,成功返回0,否则非零值
	virtual int ReadRaster(const char* filename) = 0;
	virtual int WriteRaster(const char* filename) = 0;
	//只读文件头信息,不读实体数据,成功返回0,否则非零
	virtual int ReadRasterBound(const char* filename) = 0;
	//判断实体数据是否存在
	virtual bool IsValid() const = 0;


	//基本属性获取
	//获取数据的地理坐标系统
	virtual int GetCoordSysNumber() const =0;
	//获取结果地理坐标左下值
	virtual void GetLowerLeftCorner(double &x,double &y) const = 0;
	virtual unsigned GetWidth()const=0;
	virtual unsigned GetHeight()const=0;
	virtual double GetResolutionX()const = 0;
	virtual double GetResolutionY()const = 0;
	virtual ECoverResultType GetCalResultType()const = 0;
	virtual CalResult_Unit GetCalResultDataUnit() const= 0;
	virtual float GetDataFactor()const=0;

	//获取设置值
	virtual double GetValueAsDouble(int x, int y) const =0;
	virtual void SetValue(int x,int y,double v)=0;
	
	//直接从文件中读取数值,成功返回0,否则非零值
	virtual int ReadIndexDataFromFile(const char * ifilename,int x, int y,double &val) = 0;
	virtual int ReadPosDataFromFile(const char * ifilename,double xpos, double ypos,double &val,int sys=0) =0;

	//一些扩展功能，可以由基类实现
	virtual bool GetValueByPos(double posX,double posY,double& val) const;
	//使用一定的分辨率取值,取值可以是最大值或平均值
	virtual bool GetValueByPos(double posX,double posY,double xRes,double yRes,EValueAverageType averageType, double &val) const;
	//以指定坐标系取值，sys=0时表示自身坐标系
	virtual bool GetDataByPos(double xpos,double ypos, int sys,double &val) const;
	//使用一定的分辨率取值,取值可以是最大值或平均值,分辨率使用与坐标系一致的表示方式
	virtual bool GetValueByPos(double posX,double posY,double xRes,double yRes,EValueAverageType averageType,int sys, double &val) const;

	//以指定坐标系获取结果范围，sys=0时表示自身坐标系
	virtual void GetBound(double &l,double &b, double &r, double &t, int sys=0) const;

	//设置默认值
	virtual void SetDefaultValue(double defaltValue);
	
};

