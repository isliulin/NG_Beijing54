#pragma once
//#include "Pthreads/include/pthread.h"
#include <omp.h>
class CNGLook
{
public:
	CNGLook(void);
	virtual ~CNGLook(void);
protected:
	//pthread_mutex_t gDb_Mutex;
	omp_lock_t gDb_Mutex;
public:
	void Look();
	void UnLook();
};
