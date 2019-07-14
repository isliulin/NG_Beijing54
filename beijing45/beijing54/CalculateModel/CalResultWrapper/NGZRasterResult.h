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
	int geoSys;//ϵͳ����ϵ

	//λ������
	double leftPos; //���׼ֵ
	double bottomPos;//�»�׼ֵ
	double xResolution; //x����ֱ���
	double yResolution;//y����ֱ���

	unsigned int w; //��
	unsigned int h; //��
};

#ifdef _MSC_VER
#pragma pack(pop)
#else
#pragma pack()
#endif // _MSC_VER


//դ����
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
	NGZRasterHeader head; //�ļ�ͷ
protected:
	unsigned int pCount;//������Ŀ
	void ** p_RasterData;
protected:
	unsigned dataCount;
public:
	void ReleaseData();

public:
	//����һ��դ����,���ӷŴ�����
	virtual int GenerateEmptyRaster(ECoverResultType iResultType,CalResult_DataType dataType,CalResult_Unit iResultUnit,
		int iGeoSys,double iLeft,double iBottom,unsigned int iw,unsigned int ih,double iXResolution,
		double iYResolution,float ifactor=1.0f);

	int CreateData(unsigned iw,unsigned ih,bool setDefault);

	//դ�����ļ���д
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

	//��һ���ֱ���ȡ��x,yΪ���ģ�ָ��resolution�ľ�ֵ
	virtual void GetDataOnResolutionByIndex(unsigned int x, unsigned int y,double resolution,double& val) const;
	//��ָ������ϵȡֵ��sys=0ʱ��ʾ��������ϵ
	virtual bool GetDataByPos(double xpos,double ypos, int sys,double &val) const;

	//��ָ������ϵ��ȡ�����Χ��sys=0ʱ��ʾ��������ϵ
	virtual void GetBound(double &l,double &b, double &r, double &t, int sys) const;

	//ֱ�Ӵ��ļ��ж�ȡ��ֵ
	int ReadIndexDataFromFile(const char * ifilename,int x, int y,double &val);
	int ReadPosDataFromFile(const char * ifilename,double xpos, double ypos,double &val,int sys=0);

protected:
	static void SwapHead(NGZRasterHeader & head);

	void SwapData();
};


#endif   