#include "XMutexSem.h"

//#define POSIX_SEM
#define SYSTEM_V_SEM

#if defined(_WIN32)||defined(_WIN64)
#define __USE_WINDOWS 1
#include <Windows.h>
#elif defined(POSIX_SEM)
#define __USE_SEM
#include <fcntl.h>
#include <semaphore.h>
#elif defined(SYSTEM_V_SEM)
#define __USE_UNIX_SEM
#include <sys/ipc.h>
#include <sys/sem.h>
#endif


#define SEM_PERM 0600


CXMutexSem::CXMutexSem(const char*name)
{
	semid = -1;
	m_pObj = 0;
	if(name!=0)
		m_name = name;
	else
		m_name = "XMutexSem";
	size_t findSpace =0;
	while((findSpace=m_name.find(' '))!=std::string::npos)
	{
		m_name.erase(findSpace,1);
	}
}

CXMutexSem::~CXMutexSem(void)
{
	if(m_pObj||semid!=-1)
	{
#ifdef __USE_WINDOWS

	CloseHandle(m_pObj);
#elif defined(__USE_SEM)
	sem_close((sem_t*)m_pObj);
	sem_unlink(m_name.c_str());
#elif defined(__USE_UNIX_SEM)
	int sem_val = semctl(semid,0,GETVAL,0);
	if(sem_val == 0)
		semctl(semid,0,IPC_RMID,0);
#endif
	}

}

void CXMutexSem::Lock()
{
	CreateMutexObj();

	if(m_pObj||semid!=-1)
	{
#ifdef __USE_WINDOWS
	WaitForSingleObject(m_pObj,INFINITE);
#elif defined(__USE_SEM)
	sem_wait((sem_t*)m_pObj);
#elif defined(__USE_UNIX_SEM)
	static struct sembuf LockOp[2] =
	{
		0,0,0,
		0,1,SEM_UNDO
	};
	semop(semid,&LockOp[0],2);
#endif
	}
}

void CXMutexSem::UnLock()
{
	if(m_pObj||semid!=-1)
	{
#ifdef __USE_WINDOWS
	ReleaseMutex(m_pObj);
#elif defined(__USE_SEM)
	sem_post((sem_t*)m_pObj);
#elif defined(__USE_UNIX_SEM)
	static struct sembuf UnlockOp[1]=
	{
		0,-1,(IPC_NOWAIT|SEM_UNDO)
	};
	semop(semid,&UnlockOp[0],1);
#endif
	}
}

bool CXMutexSem::IsValidObj() const
{
	return m_pObj!=0;
}

void CXMutexSem::CreateMutexObj()
{
#ifdef __USE_WINDOWS
	if(m_pObj!=NULL)
		return;
	m_pObj = CreateMutexA(NULL,FALSE,m_name.c_str());
	if(m_pObj==NULL)
	{
		size_t length = m_name.size();
		for(size_t off = 0;off<length;off++)
		{
			char ch = m_name.at(off);
			if(ch<0||ch=='/'||ch==':'||ch=='\\')
			{
				m_name.erase(off,1);
				off--;
				length--;
			}
		}

		m_pObj = CreateMutexA(NULL,FALSE,m_name.c_str());
	}

#elif defined(__USE_SEM)
	if(m_pObj!=NULL)
		return;
	m_pObj = sem_open(m_name.c_str(),O_RDWR|O_CREAT,0644,1);
	if(m_pObj==NULL)
	{
		size_t length = m_name.size();
		for(size_t off = 0;off<length;off++)
		{
			char ch = m_name.at(off);
			if(ch<0||ch=='/'||ch==':'||ch=='\\')
			{
				m_name.erase(off,1);
				off--;
				length--;
			}
		}

		m_pObj = sem_open(m_name.c_str(),O_RDWR|O_CREAT,0644,1);

	}
	/*if(m_pObj)
    {
        int val = 0;
        sem_getvalue((sem_t*)m_pObj,&val);
        if(val==0)
            sem_init((sem_t*)m_pObj,0,1);
    }*/
#elif defined(__USE_UNIX_SEM)
	if(semid!=-1)
	{
		int sem_val = semctl(semid,0,GETVAL,0);
		if(sem_val==-1)
			semid = -1;
	}
	if(semid==-1)
	{
		key_t sem_key=0;
		size_t length = m_name.size();
		for(size_t off = 0;off<length;off++)
		{
			unsigned char ch = m_name.at(off);
			sem_key += ch;
		}
		semid = semget(sem_key,1,SEM_PERM|IPC_CREAT);
	}
#endif

}
