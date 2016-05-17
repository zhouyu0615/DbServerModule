#pragma once
#include "Thread.h"
#include <WinSock2.h>
#include "MyThreadPool.h"

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
	bool CloseSocket();                        //¹Ø±ÕSocket


	virtual void taskProc();


	CMyThreadPool* m_pthreadPool;

};

