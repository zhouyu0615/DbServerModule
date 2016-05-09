#pragma once

#include "Thread.h"
#include <WinSock2.h>

class CReceiveFileTask :public CTask
{
public:
	CReceiveFileTask(SOCKET& ReceiveSocket);
	~CReceiveFileTask();
private:
	SOCKET m_socket;
	CString m_fileSavePath;

	virtual void Run();		


public:
	void StartUp();
};

