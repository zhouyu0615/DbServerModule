#include "stdafx.h"
#include "ReceiveFileTask.h"
#include "Log.h"




CReceiveFileTask::CReceiveFileTask(SOCKET& ReceiveSocket) :m_socket(ReceiveSocket)
{
}


CReceiveFileTask::~CReceiveFileTask()
{

}


void CReceiveFileTask::StartUp()
{

}

void CReceiveFileTask::taskProc()
{
	char fileNameBuff[100];
	memset(fileNameBuff, 0, 100);

	FILE *fp = NULL;
	if (recv(m_socket, fileNameBuff, 100, 0))
	{
		fp = fopen(fileNameBuff, "wb");
		LOG2("Receive file name:", fileNameBuff);
	}
	size_t fileLen = 0;
	if (recv(m_socket, (char *)&fileLen, sizeof(size_t), 0))
	{
		LOG2("Server Accept Failed:", WSAGetLastError());
	}

	size_t recvFileLen = 0;
	char fileBuff[4096];

	while (recvFileLen < fileLen)
	{
		int temp = recv(m_socket, fileBuff, 4096, 0);
		fwrite(fileBuff, sizeof(char), temp, fp);
		recvFileLen += temp;
		memset(fileBuff, 0, 4096);
	}

	if (recvFileLen == fileLen)
	{
		LOG2("Receive Success,recvFileLen=", recvFileLen);
		fflush(fp);
	}

	fclose(fp);
	closesocket(m_socket);
}
