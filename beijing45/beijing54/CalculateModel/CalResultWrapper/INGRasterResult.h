#pragma once
#include "CalResultWrapper.h"

//ĿǰNG�ļ��ֶ�����դ���ļ���ʽ

enum NGRasterResultFormat
{
	RASTER_NULL, //��ʾδ֪�ĸ�ʽ
	RASTER_NGZ, //ѹ����ʽ��ngz�ļ�
	RASTER_NGZS,//�зŴ����ӵ�ngz�ļ�
	RASTER_NGB, //��ѹ����ʽ��ngb�ļ�
	RASTER_NGR // NGRadioPlan�Ķ����ƽ���ļ�
};

enum EValueAverageType
{
	RANGE_AVERAGE, //�ڷ�Χ�ڵ�ֱֵ��ƽ��
	RANGE_AVERAGE_POW, //ת����Ȼ��ֵ��10log
	RANGE_AVERAGE_POW2,//ת����Ȼ��ֵ��20log
	RANGE_MAX,//ȡ���ֵ
};

//�ж�ֵ�Ƿ���Ч���о�����
#define IS_VALID_RASTER_VALUE(x) ((x)>-9000&&(x)<9000)

#ifndef NG_DELETE_SINGLE
#define  NG_DELETE_SINGLE(P) if(P) delete P; P=0;
#endif

class RESULT_API INGRaterResult
{

public:
	//������Ҫ��ʽ��������
	static INGRaterResult * CreateRaster(NGRasterResultFormat format);
	//��ȡ�ļ��ĸ�ʽ
	static NGRasterResultFormat CheckRasterFileFormat(const char * file);
	//�ͷ��ɸ�dll�����Ķ���
	static void DestroyRaster(INGRaterResult*& pRaster);

public:
	INGRaterResult(void){}
	virtual ~INGRaterResult(void){}
public:
	virtual NGRasterResultFormat GetRsultFormat() const = 0;
public:
	//��ʼ��դ�����ṹ����,����ɹ�����0,�������ֵ
	virtual int GenerateEmptyRaster(ECoverResultType iResultType,CalResult_DataType dataType,CalResult_Unit iResultUnit,
		int iGeoSys,double iLeft,double iBottom,unsigned int iw,unsigned int ih,double iXResolution,
		double iYResolution,float ifactor=10.0f) = 0;

	//դ�����ļ���д,�ɹ�����0,�������ֵ
	virtual int ReadRaster(const char* filename) = 0;
	virtual int WriteRaster(const char* filename) = 0;
	//ֻ���ļ�ͷ��Ϣ,����ʵ������,�ɹ�����0,�������
	virtual int ReadRasterBound(const char* filename) = 0;
	//�ж�ʵ�������Ƿ����
	virtual bool IsValid() const = 0;


	//�������Ի�ȡ
	//��ȡ���ݵĵ�������ϵͳ
	virtual int GetCoordSysNumber() const =0;
	//��ȡ���������������ֵ
	virtual void GetLowerLeftCorner(double &x,double &y) const = 0;
	virtual unsigned GetWidth()const=0;
	virtual unsigned GetHeight()const=0;
	virtual double GetResolutionX()const = 0;
	virtual double GetResolutionY()const = 0;
	virtual ECoverResultType GetCalResultType()const = 0;
	virtual CalResult_Unit GetCalResultDataUnit() const= 0;
	virtual float GetDataFactor()const=0;

	//��ȡ����ֵ
	virtual double GetValueAsDouble(int x, int y) const =0;
	virtual void SetValue(int x,int y,double v)=0;
	
	//ֱ�Ӵ��ļ��ж�ȡ��ֵ,�ɹ�����0,�������ֵ
	virtual int ReadIndexDataFromFile(const char * ifilename,int x, int y,double &val) = 0;
	virtual int ReadPosDataFromFile(const char * ifilename,double xpos, double ypos,double &val,int sys=0) =0;

	//һЩ��չ���ܣ������ɻ���ʵ��
	virtual bool GetValueByPos(double posX,double posY,double& val) const;
	//ʹ��һ���ķֱ���ȡֵ,ȡֵ���������ֵ��ƽ��ֵ
	virtual bool GetValueByPos(double posX,double posY,double xRes,double yRes,EValueAverageType averageType, double &val) const;
	//��ָ������ϵȡֵ��sys=0ʱ��ʾ��������ϵ
	virtual bool GetDataByPos(double xpos,double ypos, int sys,double &val) const;
	//ʹ��һ���ķֱ���ȡֵ,ȡֵ���������ֵ��ƽ��ֵ,�ֱ���ʹ��������ϵһ�µı�ʾ��ʽ
	virtual bool GetValueByPos(double posX,double posY,double xRes,double yRes,EValueAverageType averageType,int sys, double &val) const;

	//��ָ������ϵ��ȡ�����Χ��sys=0ʱ��ʾ��������ϵ
	virtual void GetBound(double &l,double &b, double &r, double &t, int sys=0) const;

	//����Ĭ��ֵ
	virtual void SetDefaultValue(double defaltValue);
	
};

