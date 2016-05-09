#pragma once


/**
* �������log�ļ�����.
*/


#ifndef LOG_H  
#define LOG_H  


//log�ļ�·��
#define LOG_FILE_NAME "log.txt"

//���ÿ���
#define LOG_ENABLE

#include <fstream>  
#include <string>  
#include <ctime>  

using namespace std;

class CLog
{
	CLog();
	CLog(CEdit* logWin) :m_LogWin(logWin){};
	~CLog();

	CEdit* m_LogWin;
public:
	static void GetLogFilePath(CHAR* szPath)
	{
		GetModuleFileNameA(NULL, szPath, MAX_PATH);
		ZeroMemory(strrchr(szPath, _T('\\')), strlen(strrchr(szPath, _T('\\')))*sizeof(CHAR));
	
		strcat(szPath, "\\");
		strcat(szPath, LOG_FILE_NAME);
	}
	//���һ�����ݣ��������ַ���(ascii)����������������������ö��
	//��ʽΪ��[2011-11-11 11:11:11] aaaaaaa������
	template <class T>
	static void WriteLog(T x)
	{
		CHAR szPath[MAX_PATH] = { 0 };
		GetLogFilePath(szPath);

		ofstream fout(szPath, ios::app);
		fout.seekp(ios::end);
		fout << GetSystemTime() << x << endl;
		fout.close();
	}

	//���2�����ݣ��ԵȺ����ӡ�һ������ǰ����һ�������������ַ�������������������ֵ
	template<class T1, class T2>
	static void WriteLog2(T1 x1, T2 x2)
	{
		CHAR szPath[MAX_PATH] = { 0 };
		GetLogFilePath(szPath);
		ofstream fout(szPath, ios::app);
		fout.seekp(ios::end);
		fout << GetSystemTime() << x1 << " = " << x2 << endl;
		fout.close();
	}

	//���һ�е�ǰ������ʼ�ı�־,�괫��__FUNCTION__
	template <class T>
	static void WriteFuncBegin(T x)
	{
		CHAR szPath[MAX_PATH] = { 0 };
		GetLogFilePath(szPath);
		ofstream fout(szPath, ios::app);
		fout.seekp(ios::end);
		fout << GetSystemTime() << "	--------------------" << x << "  Begin--------------------" << endl;
		fout.close();
	}

	//���һ�е�ǰ���������ı�־���괫��__FUNCTION__
	template <class T>
	static void WriteFuncEnd(T x)
	{
		CHAR szPath[MAX_PATH] = { 0 };
		GetLogFilePath(szPath);
		ofstream fout(szPath, ios::app);
		fout.seekp(ios::end);
		fout << GetSystemTime() << "--------------------" << x << "  End  --------------------" << endl;
		fout.close();
	}


private:
	//��ȡ����ʱ�䣬��ʽ��"[2011-11-11 11:11:11] "; 
	static string GetSystemTime()
	{
		time_t tNowTime;
		time(&tNowTime);
		tm* tLocalTime = localtime(&tNowTime);
		char szTime[30] = { '\0' };
		strftime(szTime, 30, "[%Y-%m-%d %H:%M:%S] ", tLocalTime);
		string strTime = szTime;
		return strTime;
	}

};

#ifdef LOG_ENABLE

//��������Щ����ʹ�ñ��ļ�
#define LOG(x)				CLog::WriteLog(x);			//�����ڿ������ַ���(ascii)����������������bool��
#define LOG2(x1,x2)		CLog::WriteLog2(x1,x2);
#define LOG_FUNC		LOG(__FUNCTION__)				//�����ǰ���ں�����
#define LOG_LINE		LOG(__LINE__)						//�����ǰ�к�
#define LOG_FUNC_BEGIN  CLog::WriteFuncBegin(__FUNCTION__);		//��ʽ�磺[ʱ��]"------------FuncName  Begin------------"
#define LOG_FUNC_END     CLog::WriteFuncEnd(__FUNCTION__);		//��ʽ�磺[ʱ��]"------------FuncName  End------------"

#else

#define LOG(x)				
#define LOG2(x1,x2)		
#define LOG_FUNC		
#define LOG_LINE		
#define LOG_FUNC_BEGIN  
#define LOG_FUNC_END    

#endif

#endif  



