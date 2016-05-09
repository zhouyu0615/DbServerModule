#include "stdafx.h"
#include "Thread.h"

CThread::CThread(void) :
m_pTask(NULL),
m_bRun(false)
{
	m_handle = NULL;
}

CThread::~CThread(void)
{
	
}

CThread::CThread(CTask * pTask) :
m_ThreadName(""),
m_pTask(pTask),
m_bRun(false)
{
	m_handle = NULL;
}

CThread::CThread(const char * ThreadName, CTask * pTask) :
m_ThreadName(ThreadName),
m_pTask(pTask),
m_bRun(false)
{
	m_handle = NULL;
}

CThread::CThread(CString ThreadName, CTask * pTask) :
m_ThreadName(ThreadName),
m_pTask(pTask),
m_bRun(false)
{
	m_handle = NULL;
}

bool CThread::Start(bool bSuspend)
{
	if (m_bRun)
	{
		return true;
	}
	if (bSuspend)
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, StaticThreadFunc, this, CREATE_SUSPENDED, &m_ThreadID);
	}
	else
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 0, StaticThreadFunc, this, 0, &m_ThreadID);
	}
	m_bRun = (NULL != m_handle);
	return m_bRun;
}


BOOL CThread::GetThreadCurrentRunState()
{
	return m_bRun;
}

void CThread::Run()
{
	if (!m_bRun)
	{
		return;
	}
	if (NULL != m_pTask)
	{
		m_pTask->Run();
	}
	m_bRun = false;
}

void CThread::Join(int timeout)
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	if (timeout <= 0)
	{
		timeout = INFINITE;
	}
	::WaitForSingleObject(m_handle, timeout);
}

void CThread::Resume()
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	::ResumeThread(m_handle);
}

void CThread::Suspend()
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	::SuspendThread(m_handle);
}

bool CThread::Terminate(unsigned long ExitCode)
{
	if (NULL == m_handle || !m_bRun)
	{
		return true;
	}
	if (::TerminateThread(m_handle, ExitCode))
	{
		::CloseHandle(m_handle);
		return true;
	}
	return false;
}

unsigned int CThread::GetThreadID()
{
	return m_ThreadID;
}

CString CThread::GetThreadName()
{
	return m_ThreadName;
}

void CThread::SetThreadName(CString ThreadName)
{
	m_ThreadName = ThreadName;
}

void CThread::SetThreadName(const char * ThreadName)
{
	if (NULL == ThreadName)
	{
		m_ThreadName = "";
	}
	else
	{
		m_ThreadName = ThreadName;
	}
}

void CThread::SetThreadPriority(int ThreadPriority)
{
	if (NULL == m_handle || !m_bRun)
	{
		return;
	}
	::SetThreadPriority(m_handle,ThreadPriority);

}

unsigned int CThread::StaticThreadFunc(void * arg)
{
	CThread * pThread = (CThread *)arg;
	pThread->Run();
	return 0;
}