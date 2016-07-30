// Logger.h: interface for the CLogger class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdarg.h>
#include <windows.h>
#include "globals.h"

class CLogger {
public:
	CLogger (const char *cDbgFile, int iDbgLvl=3, int iDbgFileSize=500, bool redirectStdErr=false);
	virtual ~CLogger();

	virtual void HexLog(int iMsgLevel, int iThreadNo, const unsigned char *cDebugMsg, int iMsgLen);
	virtual void Log (int iMsgLevel, int iThreadNo, const char* cFuncName, const char* cFormat, ...);
	virtual void LogString (int iMsgLevel, int iThreadNo, const char* cFuncName, const char* cFormat);
	
	void changeDebugLevel(int iNewDebugLevel);
	
	char *getFilename ();

protected:
	HANDLE hFile;
	HANDLE hMutex;
	bool m_redirectStdErr;
	char cLogFileName[MAX_STRING_LENGTH];
	char cInternalFileName[MAX_STRING_LENGTH];
	int	iDebugLevel;
	int iDebugFileSize;
	int iFileIndex;
	virtual void createFile (bool init=false);
	void WriteToFile(LPCVOID buffer,DWORD count);
private:
	LARGE_INTEGER m_iFileSize;
	inline void getTimeStamp (char *cTime)
	{

		SYSTEMTIME systemTime;
		GetLocalTime  (&systemTime);


		char cYear[10];
		char cMilliSec[10];

		sprintf (cYear, "%d", systemTime.wYear);
		sprintf (cMilliSec, "%03d", systemTime.wMilliseconds);
		sprintf(cTime,"%.2s/%.2d/%.2d %.2d:%.2d:%.2d.%.3s"
									,cYear + 2
									,systemTime.wMonth
									,systemTime.wDay
									,systemTime.wHour 
									,systemTime.wMinute 
									,systemTime.wSecond
									,cMilliSec);
	}
protected:
	virtual bool isNewFileRequired();
};

#endif