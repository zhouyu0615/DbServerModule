#ifndef __THREAD_H__
#define __THREAD_H__

#include <string>
#include "stdafx.h"

#include   <windows.h>
#include   <process.h>

class CTask
{
public:
	CTask(){};
	virtual ~CTask() {};
	virtual void Run() = 0;

	void SetTaskId(int id){ m_id = id; };
	int  GetTaskId() { return m_id; };
private:
	int m_id;
};

class CThread : public CTask
{
private:
	explicit CThread(const CThread & rhs);

public:
	CThread();
	CThread(CTask * pTask);
	CThread(const char * ThreadName, CTask * pTask = NULL);
	CThread(CString ThreadName, CTask * pTask = NULL);
	~CThread(void);

	/**
	开始运行线程
	@arg bSuspend 开始运行时是否挂起
	**/
	bool Start(bool bSuspend = false);

	/**
	运行的线程函数，可以使用派生类重写此函数
	**/
	virtual void Run();

	/**
	当前执行此函数线程等待线程结束
	@arg timeout 等待超时时间，如果为负数，等待无限时长
	**/
	void Join(int timeout = -1);
	/**
	恢复挂起的线程
	**/
	void Resume();
	/**
	挂起线程
	**/
	void Suspend();
	/**
	终止线程的执行
	**/
	bool Terminate(unsigned long ExitCode);

	unsigned int GetThreadID();
	CString GetThreadName();
	void SetThreadName(CString ThreadName);
	void SetThreadName(const char * ThreadName);
	void SetThreadPriority(int ThreadPriority);



	BOOL GetThreadCurrentRunState();

private:
	static unsigned int WINAPI StaticThreadFunc(void * arg);

private:
	HANDLE m_handle;
	CTask * const m_pTask;
	unsigned int m_ThreadID;
	CString m_ThreadName;
	volatile bool m_bRun;
};

#endif