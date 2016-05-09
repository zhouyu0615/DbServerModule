#include "stdafx.h"
#include "TCPServer.h"
#include "Log.h"
#include "ReceiveFileTask.h"

#pragma comment(lib, "WS2_32") 


CTCPServer::CTCPServer()
{
	m_nPort = 8888;
}


CTCPServer::~CTCPServer()
{
	CloseSocket();
	WSACleanup();
}


bool CTCPServer::StartUp()
{
	CreateWorkThread();
	StartWorkThread();
	return true;
}


void CTCPServer::CreateWorkThread()
{
	m_pWorkThread = new CThread(this);
	m_pWorkThread->SetThreadPriority(THREAD_PRIORITY_NORMAL);

}

void CTCPServer::StartWorkThread()
{
	m_pWorkThread->Start();
}
void CTCPServer::ResumeWorkThread()
{
	m_pWorkThread->Resume();
}
void CTCPServer::SuspendWorkThread()
{
	m_pWorkThread->Suspend();
}


int CTCPServer::InitSocket()
{
	// 初始化socket dll 
	WSADATA wd;
	if (WSAStartup(MAKEWORD(2, 1), &wd) != 0)
	{
		LOG("Init socket dll error!");
		return -1;
	}


	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == m_Socket)
	{
		LOG("Create Socket Error!");
		return false;
	}

	
	m_ServerAddr.sin_family = AF_INET;
	m_ServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	m_ServerAddr.sin_port = htons(m_nPort);

	return 0;
}




bool CTCPServer::BindSocket()
{

	//绑定socket和服务端(本地)地址 
	if (SOCKET_ERROR == bind(m_Socket, (LPSOCKADDR)&m_ServerAddr, sizeof(m_ServerAddr)))
	{
		LOG2("Server Bind Failed:", WSAGetLastError());
		return false;
	}

	
	return TRUE;
}

bool CTCPServer::CloseSocket()
{
	//关闭Socket，释放资源
	int nErr = closesocket(m_Socket);
	if (nErr == SOCKET_ERROR)
	{
		return FALSE;
	}
	return TRUE;
}



void CTCPServer::Run()
{
	InitSocket();
	if (BindSocket())
	{

		//监听 
		if (SOCKET_ERROR == listen(m_Socket, 10))
		{
			LOG2("Server Listen Failed:", WSAGetLastError());
			return;
		}
		LOG("Server is listening...");
		while (TRUE)
		{ 
			sockaddr_in clientAddr;
			int AddrLen = sizeof(clientAddr);
			SOCKET m_New_Socket = accept(m_Socket, (sockaddr *)&clientAddr, &AddrLen);
			if (SOCKET_ERROR == m_New_Socket)
			{
				LOG2("Server Accept Failed:", WSAGetLastError());
				closesocket(m_New_Socket);
			    break;
			}

			CReceiveFileTask* m_pReceivefile = new CReceiveFileTask(m_New_Socket);
			CThread* m_pThread = new CThread(m_pReceivefile);
			m_pThread->Start();

			/*
			char fileNameBuff[100];
			memset(fileNameBuff, 0, 100);

			FILE *fp = NULL;
			if (recv(m_New_Socket, fileNameBuff, 100, 0))
			{
				 fp= fopen(fileNameBuff, "wb");
				 LOG2("Receive file name:", fileNameBuff);
			}
			size_t fileLen=0;
			if (recv(m_New_Socket,(char *)&fileLen,sizeof(size_t),0))
			{   			
				LOG2("Server Accept Failed:", WSAGetLastError());
			}

			size_t recvFileLen=0;
			char fileBuff[4096];

			while (recvFileLen<fileLen)
			{
				int temp= recv(m_New_Socket, fileBuff, 4096, 0);
				fwrite(fileBuff, sizeof(char), temp, fp);
				recvFileLen += temp;
				memset(fileBuff, 0, 4096);
			}
			
			if (recvFileLen==fileLen)
			{
				LOG2("Receive Success,recvFileLen=", recvFileLen);
				fflush(fp);
			}
			
			fclose(fp);
			*/

			//closesocket(m_New_Socket);
		}
		
	}

}