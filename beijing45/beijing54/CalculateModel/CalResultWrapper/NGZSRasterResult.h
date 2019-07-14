#pragma once
#include "INGRasterResult.h"
#include "../../HDFSFileWR/IFileManager.h"

#ifdef _MSC_VER
#pragma pack(push, 1)
#else
#pragma pack(1)
#endif // _MSC_VER
struct NGZSRasterHeader
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

	short factor;
	short version;
	short reserved1;
	short reserved2;

	bool bHasData;
};

#ifdef _MSC_VER
#pragma pack(pop)
#else
#pragma pack()
#endif // _MSC_VER

//դ����
class RESULT_API NGZSRasterResult:public INGRaterResult
{

public:
	NGZSRasterResult();
	~NGZSRasterResult();
public:
	static NGZSRasterResult * Create(){return new NGZSRasterResult;}
	static void Destroy(NGZSRasterResult*& pRaster) {NG_DELETE_SINGLE(pRaster);}

public:
	static bool CheckFile(const char * ifilename);
public:
	virtual NGRasterResultFormat GetRsultFormat() const {return RASTER_NGZS;}
public:
	//����һ��դ����
	virtual int GenerateEmptyRaster(ECoverResultType iResultType,CalResult_DataType dataType,CalResult_Unit iResultUnit,
		int iGeoSys,double iLeft,double iBottom,unsigned int iw,unsigned int ih,double iXResolution,
		double iYResolution,float ifactor=10.0f);
	//դ�����ļ���д
	int ReadRaster(const char* filename);

	int ReadRasterBound(const char* filename);

	int WriteRaster(const char* filename);

	bool IsValid() const {return p_RasterData!=0;}
	//////////////////////////////////////////////////////////////////////////



protected:
	//�ռ�ߴ�
	NGZSRasterHeader head;

	unsigned int pCount;//������Ŀ
	short ** p_RasterData;
	double m_dfactorReciprocal;
protected:
	unsigned dataCount;
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
	short** GetData() {return p_RasterData;}

	//
	void SetResultType(ECoverResultType iResultType) {head.eResultType = iResultType;}
	ECoverResultType GetCalResultType() const {return head.eResultType;}
	void SetResultUint(CalResult_Unit iResultUnit){head.eResultUnit = iResultUnit;}
	CalResult_Unit GetCalResultDataUnit() const {return head.eResultUnit;}

public:
	//��ȡ����ʵ��ֵ���ǷŴ���ֵ
	double GetValueAsDouble(int x, int y) const  ;

	//����ʵ��ֵ���ǷŴ���ֵ
	void SetValue(int x,int y,double v);

	//��ȡ����ʵ��ֵ���ǷŴ���ֵ
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
	static void SwapHead(NGZSRasterHeader & head);
	void SwapData();

public:
	static NGZSRasterResult * CreateArray(int n);
	static void DestroyArray(NGZSRasterResult *& pRasterResult);
};
 