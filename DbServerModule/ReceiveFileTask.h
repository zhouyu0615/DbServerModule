#pragma once

#include "Thread.h"
#include <WinSock2.h>

class CReceiveFileTask :public CTask
{
public:
	CReceiveFileTask(SOCKET& ReceiveSocket,CString& FileSavePath);
	~CReceiveFileTask();
private:
	SOCKET m_socket;
	CString m_fileSavePath;

	virtual void taskProc();		


public:
	void StartUp();
};

