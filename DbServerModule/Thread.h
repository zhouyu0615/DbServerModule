#ifndef __THREAD_H__
#define __THREAD_H__

#include <string>
#include "stdafx.h"

#include   <windows.h>
#include   <process.h>
#include  "Task.h"
#include "MyThreadPool.h"

class CBaseThreadPool;



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


	CThread(CBaseThreadPool* cb);

	/**
	��ʼ�����߳�
	@arg bSuspend ��ʼ����ʱ�Ƿ����
	**/
	bool StartThread(bool bSuspend = false);

	/**
	���е��̺߳���������ʹ����������д�˺���
	**/
	virtual void taskProc();

	/**
	��ǰִ�д˺����̵߳ȴ��߳̽���
	@arg timeout �ȴ���ʱʱ�䣬���Ϊ�������ȴ�����ʱ��
	**/
	void Join(int timeout = -1);
	/**
	�ָ�������߳�
	**/
	void Resume();
	/**
	�����߳�
	**/
	void Suspend();
	/**
	��ֹ�̵߳�ִ��
	**/
	bool Terminate(unsigned long ExitCode);

	unsigned int GetThreadID();
	CString GetThreadName();
	void SetThreadName(CString ThreadName);
	void SetThreadName(const char * ThreadName);
	void SetThreadPriority(int ThreadPriority);


	bool assignTask(CTask* pTask);
	bool startTask();
	

	BOOL GetThreadCurrentRunState();

private:
	static unsigned int WINAPI StaticThreadFunc(void * arg);

	void Init();

private:
	HANDLE m_handle;
	CTask *  m_pTask;
	unsigned int m_ThreadID;
	CString m_ThreadName;
	volatile bool m_bRun;

	HANDLE m_hEvent;
	CBaseThreadPool* m_pThreadPool;
};

#endif