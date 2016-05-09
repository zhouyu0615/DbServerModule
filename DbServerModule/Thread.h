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
	��ʼ�����߳�
	@arg bSuspend ��ʼ����ʱ�Ƿ����
	**/
	bool Start(bool bSuspend = false);

	/**
	���е��̺߳���������ʹ����������д�˺���
	**/
	virtual void Run();

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