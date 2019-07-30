#include <math.h>
#include <map>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "NGMapGeo.h"
#include "../CommonTools/StringTools.h"
#include "../CommonTools/FileTools.h"

#include "ComplexMatricx.h"

#include <assert.h>


#ifndef _ASSERT
#define _ASSERT assert
#endif

#pragma warning(disable:4996)

//�ж�ϵͳ�ֽ���
EByteOrder CheckByteOrder()
{
	unsigned short sV = 0x0001;
	if(*((char*)&sV)>0)
		return eLittleEndian;
	else
		return eBigEndian;	
}

//��ȡָ��bittype��
int GetBitTypeByteCounts(BitType eBitType)
{
	//Ĭ���ֽ�������Ϊ2
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


#define sw16(x) ( ((short)(x>>8)&0x00ff) | (((short)x&0x00ff)<<8) )




TILEINFO::TILEINFO()
{
	m_xInd = -1;
	m_yInd = -1;
	m_pManager = NULL;
	bInMemory = false;			//��ʼ��ʱδ���ؽ��ڴ�
	pTileMatrix = NULL;
	omp_init_lock(&m_omplock);

}

TILEINFO::~TILEINFO()
{
	ReleaseData();
	omp_destroy_lock(&m_omplock);
}

short TILEINFO::ShortElement( int x,int y )
{
	if(bInMemory)
	{
		return ShortValueInMemory(x,y);
	}
	else
	{
		short v = m_DefaultValue;
		omp_set_lock(&m_omplock);
		if(!bInMemory)
			ReadDataFromMap();	
		v = ShortValueInMemory(x,y);
		omp_unset_lock(&m_omplock);
		return v;
	}
}

void TILEINFO::SetShortElement( int x,int y, short val )
{
	if(bInMemory)
	{
		SetShortValueInMemory(x, y, val);
	}
	else
	{
		omp_set_lock(&m_omplock);
		if(!bInMemory)
			ReadDataFromMap();	
		SetShortValueInMemory(x, y, val);
		omp_unset_lock(&m_omplock);
	}
}

void TILEINFO::InitMapInfo( CNGMapGeo *pManager,int xindex,int yindex )
{
	if(pManager)
	{
		m_pManager = pManager;
		m_xInd = xindex;
		m_yInd = yindex;
		m_DefaultValue = m_pManager->m_DefaultValue;
	}
	
}

short TILEINFO::ShortValueInMemory( int x,int y )
{
	
	if(m_pManager && pTileMatrix)
	{
		int  w = m_pManager->m_Tile_nX;
		int h = m_pManager->m_Tile_nY;
		if((x >= w) || (x< 0) || (y >= h) || (y < 0))
		{
			return m_DefaultValue;
		}
		switch(m_pManager->m_eBitType)
		{
		case _16BitSigned: return ((short *)pTileMatrix)[y * w + x]; break;//�õ��õ�����ֵ
		case _8Bit: return (short)((char*)pTileMatrix)[y* w + x]; break;
		case _8BitUnsigned: return (short)((unsigned char*)pTileMatrix)[y* w + x]; break;
		}
	}
	return m_DefaultValue;
}


void TILEINFO::SetShortValueInMemory( int x,int y, short val )
{
	
	if(m_pManager && pTileMatrix)
	{
		int  w = m_pManager->m_Tile_nX;
		int h = m_pManager->m_Tile_nY;
		if((x >= w) || (x< 0) || (y >= h) || (y < 0))
		{
			return ;
		}
		switch(m_pManager->m_eBitType)
		{
		case _16BitSigned: ((short *)pTileMatrix)[y * w + x] = val; break; //��������ֵ
		case _8Bit: ((char*)pTileMatrix)[y* w + x] = val; break;
		case _8BitUnsigned: ((unsigned char*)pTileMatrix)[y* w + x] = val; break;
		}
	}
}

void TILEINFO::ReadDataFromMap()
{

	if(!m_pManager) return;
	char blockfile[300] = {0};
	sprintf(blockfile,m_pManager->m_strDataFileFormat.c_str(),m_xInd+1,m_yInd+1);
	FILE* fp = fopen(blockfile, "r+b");
	if(fp == 0)
	{
		bInMemory = true;
		return;
	}

	int m_nWidth = m_pManager->m_Tile_nY;
	int m_nHeight = m_pManager->m_Tile_nY;

	long nDataNumber  = m_nWidth * m_nHeight;	//���ݸ���
	int nByteCounts = GetBitTypeByteCounts( m_pManager->m_eBitType);
	char* szbuffer = NULL;
	int trycount = 3;
	while(--trycount)
	{
		szbuffer = (char*)malloc(nDataNumber * nByteCounts);
		if((szbuffer == NULL) && m_pManager)
			m_pManager->ReleaseParticalTitle(m_xInd,m_yInd,3+trycount);//�ͷ��ܱ߿�,����ڴ���Դ
		else
			break;
	}
	if (szbuffer == NULL)return;
	//���ļ�
	try
	{
		fread(szbuffer, nByteCounts, nDataNumber, fp);
		fclose(fp);
		pTileMatrix = (void*)szbuffer;
	}
	catch(...)
	{
		free(szbuffer);
		pTileMatrix = NULL;
		return;
	}

	switch(m_pManager->m_eDirection)
	{
	case eRowsTopToBottom:
		{
			//����ط���ʵ��Ҫ����һ���ֽ�˳����ж�
			if(nByteCounts == 2)
			{
				if(m_pManager->m_eByteOrder != CheckByteOrder())
				{
					short* pMapAddr = (short* )pTileMatrix;
					short nTmp1 = 0,nTmp2=0;
					int k = 0;
					for ( k= 0; k < m_nHeight/2; k++)
					{
						int bk = m_nHeight-1-k;
						for (int m = 0; m < m_nWidth; m++)
						{
							nTmp1 = (short)sw16(pMapAddr[k*m_nWidth+m]);
							nTmp2 = (short)sw16(pMapAddr[bk*m_nWidth+m]);

							pMapAddr[k * m_nWidth + m] = nTmp2;
							pMapAddr[bk * m_nWidth+m] = nTmp1;
						}
					}
					if(m_nHeight%2!=0)
					{
						for (int m = 0; m < m_nWidth; m++)
						{
							nTmp1 = (short)sw16(pMapAddr[k*m_nWidth+m]);
							pMapAddr[k * m_nWidth + m] = nTmp1;
						}
					}
				}
				else
				{
					short* pMapAddr = (short* )pTileMatrix;
					for (int k = 0; k < m_nHeight/2; k++)
					{
						int bk = m_nHeight-1-k;
						for(int m=0;m<m_nWidth;m++)
						{
							short nTmp = pMapAddr[k*m_nWidth+m];
							pMapAddr[k*m_nWidth+m] = pMapAddr[bk*m_nWidth+m];
							pMapAddr[bk*m_nWidth+m] = nTmp;
						}
					}
				}
			}
			else//nByteCounts = 1
			{
				char* pMapAddr = (char* )pTileMatrix;
				for (int k = 0; k < m_nHeight/2; k++)
				{
					int bk = m_nHeight-1-k;
					for(int m=0;m<m_nWidth;m++)
					{
						char nTmp = pMapAddr[k*m_nWidth+m];
						pMapAddr[k*m_nWidth+m] = pMapAddr[bk*m_nWidth+m];
						pMapAddr[bk*m_nWidth+m] = nTmp;
					}
				}
			}
			break;
		}

	case eRowsBottomToTop:
	default:
		{
			//����ط���ʵ��Ҫ����һ���ֽ�˳����ж�
			if((nByteCounts == 2) && m_pManager->m_eByteOrder != CheckByteOrder())
			{
				short* pBuffer = (short*)szbuffer;
				int nTmp = 0;
				for (int k = 0; k < m_nHeight; k++)
				{
					for (int m = 0; m < m_nWidth; m++)
					{
						nTmp = (short)sw16(pBuffer[k * m_nWidth + m]);
						pBuffer[k * m_nWidth + m] = nTmp;
					}
				}
			}
			break;
		}
	}
	//
	bInMemory = true;
	
	
	
	//
	if (m_pManager->m_bReadOnlyFlag == true)
	{
		CheckSameValue();//��������е�ֵһ��,�ͷſռ䣬��Ĭ��ֵ���
	}
}

void TILEINFO::ReleaseData()
{
	omp_set_lock(&m_omplock);

	if(pTileMatrix)
	{
		if (m_pManager->m_bReadOnlyFlag != true)	// update map files when not read only
		{
			char blockfile[300] = {0};
			sprintf(blockfile,m_pManager->m_strDataFileFormat.c_str(),m_xInd+1,m_yInd+1);
			FILE* fp = fopen(blockfile, "w+b");
			if(fp != NULL)
			{
				int m_nWidth = m_pManager->m_Tile_nY;
				int m_nHeight = m_pManager->m_Tile_nY;

				long nDataNumber  = m_nWidth * m_nHeight;	//���ݸ���
				int nByteCounts = GetBitTypeByteCounts( m_pManager->m_eBitType);

				if((nByteCounts == 2) && m_pManager->m_eByteOrder != CheckByteOrder())
				{
					short* szbuffer = (short*)(pTileMatrix);

					short* pBuffer = NULL;

					pBuffer = (short*)szbuffer;
					int nTmp = 0;
					for (int k = 0; k < m_nHeight; k++)
					{
						for (int m = 0; m < m_nWidth; m++)
						{
							nTmp = (short)sw16(pBuffer[k * m_nWidth + m]);
							pBuffer[k * m_nWidth + m] = nTmp;
						}
					}

					if (szbuffer != NULL)
					{
						fwrite(szbuffer,nByteCounts,nDataNumber,fp);
						fclose(fp);
					}
				}		
			}
		}

		free(pTileMatrix);
		pTileMatrix = NULL;
		bInMemory = false;  //�����������ռ䣬ֱ��ָ�����������ڴ�
	}
	omp_unset_lock(&m_omplock);
}

void TILEINFO::CheckSameValue()
{	
	if(pTileMatrix)
	{
		int m_nWidth = m_pManager->m_Tile_nX;
		int m_nHeight = m_pManager->m_Tile_nY;
		short v = m_DefaultValue;
		short tmpv = m_DefaultValue;
		switch(m_pManager->m_eBitType)
		{
		case _16BitSigned: v =  ((short *)pTileMatrix)[0]; break;
		case _8Bit: v= (short)((char*)pTileMatrix)[0]; break;
		case _8BitUnsigned: v=(short)((unsigned char*)pTileMatrix)[0]; break;
		}

		for(int x=0;x<m_nWidth;x++)
		{
			for(int y=0;y<m_nHeight;y++)
			{
				switch(m_pManager->m_eBitType)
				{
				case _16BitSigned: tmpv = ((short *)pTileMatrix)[y * m_nWidth + x]; break;	//�õ��õ�����ֵ
				case _8Bit: tmpv =  (short)((char*)pTileMatrix)[y* m_nWidth + x]; break;
				case _8BitUnsigned: tmpv =  (short)((unsigned char*)pTileMatrix)[y* m_nWidth + x]; break;
				}
				if(tmpv!=v)
					break;
			}
			if(tmpv!=v)
				break;
		}
		//���ֵ����ͬ,ɾ���ռ�,��ֵ��ΪĬ��ֵ
		if(tmpv == v)
		{
			m_DefaultValue = v;
			free(pTileMatrix);
			pTileMatrix = NULL;
		}
		
	}
}
