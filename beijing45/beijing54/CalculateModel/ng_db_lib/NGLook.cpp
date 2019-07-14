#include "NGLook.h"

CNGLook::CNGLook(void)
{
	//pthread_mutex_init(&gDb_Mutex,NULL);
	gDb_Mutex = 0;
	omp_init_lock(&gDb_Mutex);
}

CNGLook::~CNGLook(void)
{
	//pthread_mutex_destroy(&gDb_Mutex);
	omp_destroy_lock(&gDb_Mutex);
}

void CNGLook::Look()
{
	//pthread_mutex_lock(&gDb_Mutex);
	omp_set_lock(&gDb_Mutex);
}

void CNGLook::UnLook()
{
	//pthread_mutex_unlock(&gDb_Mutex);
	omp_unset_lock(&gDb_Mutex);
}
