#pragma once
#include "Thread.h"
#include <WinSock2.h>

class CTCPServer:public CTask
{
public:
	CTCPServer();
	~CTCPServer();



	bool StartUp();

private:
	SOCKET m_Socket;
	CThread *m_pWorkThread;

	int    m_nPort;

	sockaddr_in m_ServerAddr;
	int InitSocket();
	bool BindSocket();
	bool CloseSocket();                        //关闭Socket


	/**
	运行的线程函数，可以使用派生类重写此函数
	**/
	void CreateWorkThread();
	void StartWorkThread();
	void ResumeWorkThread();
	void SuspendWorkThread();
	virtual void Run();


};

