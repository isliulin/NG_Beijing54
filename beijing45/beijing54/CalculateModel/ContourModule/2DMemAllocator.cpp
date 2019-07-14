// 2DMemAllocator.cpp: implementation of the C2DMemAllocator class.
//
//////////////////////////////////////////////////////////////////////

#include "2DMemAllocator.h"
#include "HeadDefine.h"

/*~~~~~~~二维数组数据动态分配~~~~~~~~~~~~*/
//分配函数:
//AllocMemory2D(T ** &p,int rows,int columns)
//
//释放函数:
//FreeMemory2D(T **&pp)
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


C2DMemAllocator::C2DMemAllocator()
{

}

C2DMemAllocator::~C2DMemAllocator()
{

}

void C2DMemAllocator::FreeMemory2D(float **&pp)
{
	//TRACE("in FreeMemory2D\n");
	if(pp)
	{//释放顺序::一维指针-->二维指针
		
		delete []pp[0];
		pp[0]=NULL;
		
		delete []pp;
		pp=NULL;
	}
}


bool C2DMemAllocator::AllocMemory2D(float ** &p,int rows,int columns)
{
	float **pp;
	pp=0;
	pp= new float*[rows];
	if (!pp)
	{
		return false;
	}
	int size = rows*columns;
	pp[0]=new float[size];//allocate a big block
	if (!pp[0])
	{
		return false;
	}
	for(int i=1;i<rows;i++)
	{
		pp[i]=pp[0]+(int)columns*i;
	}
    
	p = pp;
	
	return true;
}
