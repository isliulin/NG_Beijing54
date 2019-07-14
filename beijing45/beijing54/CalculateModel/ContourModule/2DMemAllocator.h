// 2DMemAllocator.h: interface for the C2DMemAllocator class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __2DMEMALLOCATOR_H__
#define __2DMEMALLOCATOR_H__


/***********************************************************************
//        C2DMemAllocator    
//        
//        ��ά���鶯̬���䣨������������䣬��ָ�붨λ˼�룩
//
//        ���亯��:
//        AllocMemory2D(T ** &p,int rows,int columns)
//        �ͷź���:
//        FreeMemory2D(T **&pp)        
//
//----------------------------------------------
//        ֣Ԫ��   jeny_man
//        2004/01/14 
***********************************************************************/

class C2DMemAllocator  
{
public:
	C2DMemAllocator();
	~C2DMemAllocator();

    
	/*~~~~~~~~~���亯��~~~~~~~~~~~~~~~~~*/
	//����������
	//   p: [out],�ú�������ɹ���ָ�����ø�p
	//rows: [in], ����
	//cols: [in], ����
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	static bool AllocMemory2D(float ** &p,int rows,int cols);


	/*~~~~~~~~~�ͷź���~~~~~~~~~~~~~~~~~*/
	//�ͷ���AllocMemory2D()����ɹ����ڴ�ռ�
	//һ��������
	//   pp: [in],��AllocMemory2D()������ڴ�ָ��
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	static void FreeMemory2D(float **&pp);

};

#endif // !defined(C2DMEMALLOCATOR_H_INCLUDED_)
