// Logger.cpp: implementation of the CLogger class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Logger.h"
#include "Directory.h"

CLogger::CLogger(const char *cDbgFile, int iDbgLvl, int iDbgFileSize,bool redirectStdErr)
{
	hFile = INVALID_HANDLE_VALUE;
	hMutex = NULL;
	m_redirectStdErr = redirectStdErr;
	char cMutexName [1024];
	strcpy (cMutexName, cDbgFile);
	for (int i=0; i<(int) strlen (cMutexName); i++)
	{
		if (cMutexName[i] == '\\' || cMutexName[i] == ':' || cMutexName[i] == '.') 
		{
			cMutexName[i] = '_';
		}
	}

	hMutex = CreateMutexA (NULL, FALSE, cMutexName);
	if (hMutex == NULL) 
		throw "error";
	strcpy (cLogFileName, cDbgFile);
	strcpy (cInternalFileName, cDbgFile);
	char cDirectory[MAX_STRING_LENGTH];
	char cFileName[MAX_STRING_LENGTH];
	if(CDirectory::breakQualifiedName(cDbgFile,cDirectory,cFileName)==true)
	{
		CDirectory::createFolder(cDirectory);
	}
	iDebugLevel = iDbgLvl;
	iDebugFileSize = iDbgFileSize;
	iFileIndex = 0;

	CLogger::createFile (true);
}

void CLogger::createFile (bool init)
{
	char tempStr[2048];
	char cFilename [MAX_STRING_LENGTH];
	char cExtension [MAX_STRING_LENGTH];
	char cFile [MAX_STRING_LENGTH];

	do
	{
		iFileIndex++;
		CDirectory::breakFilename (cInternalFileName, cFilename, cExtension);
		sprintf (cFile, "%s-%d.%s", cFilename,iFileIndex, cExtension);

		if(hFile!=INVALID_HANDLE_VALUE)
		{
			if(!init)
			{
				sprintf (tempStr , "\r\n\r\nMoving to new file: [%s]\r\n", cFile);
				WriteToFile (tempStr, strlen (tempStr));
			}
			CloseHandle(hFile);
			hFile=INVALID_HANDLE_VALUE;
		}

		hFile = CreateFileA (cFile, GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, 
														OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile == INVALID_HANDLE_VALUE) 
		{
			throw "error";
		}

		m_iFileSize.QuadPart=0;
		if(GetFileSizeEx(hFile,&m_iFileSize)==FALSE)
		{
			m_iFileSize.QuadPart=0;
		}

		if(CLogger::isNewFileRequired())
		{
			continue;
		}
		else
		{
			sprintf (tempStr , "\r\nOpened debug file: [%s] with debug level: [%d]\r\n", cFile, iDebugLevel);
			WriteToFile (tempStr, strlen (tempStr));
			if(m_redirectStdErr)
			{
				_CrtSetReportMode( _CRT_ERROR, _CRTDBG_MODE_FILE);
				_CrtSetReportFile( _CRT_ERROR, hFile );
				_CrtSetReportMode( _CRT_ASSERT, _CRTDBG_MODE_FILE);
				_CrtSetReportFile( _CRT_ASSERT, hFile );
				_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_FILE);
				_CrtSetReportFile( _CRT_WARN, hFile );
			}
			break;
		}
	}
	while(true);
}


char* CLogger::getFilename ()
{
	return cLogFileName;
}


CLogger::~CLogger ()
{
	Log (0, 0, "~CLogger", "Inside CLogger Destructor. Closing debug file.");
	if(hFile != INVALID_HANDLE_VALUE)
	{
		CloseHandle (hFile);
	}
	CloseHandle (hMutex);
	hFile = INVALID_HANDLE_VALUE;
	hMutex = NULL;
}


void CLogger::HexLog(int iMsgLevel, int iThreadNo, const unsigned char *cDebugMsg, int iMsgLen)
{
	if (iMsgLevel > iDebugLevel) 
	{
		return;
	}

	WaitForSingleObject (hMutex, INFINITE);

	try
	{
		char tempStr[2048];
		char tempchar [25];
		try 
		{
			if(hFile!=INVALID_HANDLE_VALUE)
			{
				if(isNewFileRequired())
				{
					createFile ();
				}
			}
			else
			{
				createFile ();
			}
		}
		catch (...)
		{
			ReleaseMutex (hMutex);
			return;
		}
		
		getTimeStamp(tempchar);
		sprintf (tempStr, "%s|%d|%03d|%-20.20s| %s\r\n", tempchar, iMsgLevel, iThreadNo, "", "-----HEX DUMP START HERE-----");
		WriteToFile(tempStr,strlen(tempStr));

		char logHexString[MAX_STRING_LENGTH*2], logCharString[MAX_STRING_LENGTH*2];
		int i,j;
		char ch;
		
		for (i=0,j=0; i<iMsgLen; i++,j++) 
		{
			sprintf (&logHexString[j*3], "%.2X ", cDebugMsg[i]);
			ch = cDebugMsg[i];
			if (ch == 0x00 || ch == 0x0D || ch == 0x0A) ch = '.';
			sprintf (&logCharString[j*2], "%c ", ch);
			if (j == 15) 
			{
				sprintf(tempStr, " | %-32.32s| %s\r\n", logCharString, logHexString);
				WriteToFile (tempStr, strlen(tempStr));
				j= -1;
			}
		}
			
		if (j>0) 
		{
			sprintf(tempStr, " | %-32.32s| %s\r\n", logCharString, logHexString);
			WriteToFile (tempStr, strlen(tempStr));
		}
		
		sprintf (tempStr, "%s|%d|%03d|%-20.20s| %s\r\n", tempchar, iMsgLevel, iThreadNo, "", "-----HEX DUMP END  HERE-----");
		WriteToFile(tempStr,strlen(tempStr));
	}
	catch(...)
	{
	}

	ReleaseMutex (hMutex);
}


void CLogger::Log (int iMsgLevel, int iThreadNo, const char* cFuncName, const char* cFormat, ...)
{
	if (iMsgLevel > iDebugLevel) 
	{
		return;
	}

	WaitForSingleObject (hMutex, INFINITE);

	try
	{
		char tempStr[3000];
		char logCharString[2500];
		char tempchar [25];
		try 
		{
			if(hFile!=INVALID_HANDLE_VALUE)
			{
				if(isNewFileRequired())
				{
					createFile ();
				}
			}
			else
			{
				createFile ();
			}
		}
		catch (...)
		{
			ReleaseMutex (hMutex);
			return;
		}

		getTimeStamp(tempchar);
		va_list arglist;
		va_start(arglist, cFormat);
		vsnprintf(logCharString,sizeof(logCharString)-2, cFormat, arglist);
		logCharString[sizeof(logCharString)-2]=0;
		va_end(arglist);
		
		sprintf (tempStr, "%s|%d|%03d|%-20.20s| %s\r\n", tempchar, iMsgLevel, iThreadNo, cFuncName, logCharString);    
		WriteToFile (tempStr, strlen(tempStr));
	}
	catch(...)
	{
	}

	ReleaseMutex (hMutex);
}

void CLogger::LogString (int iMsgLevel, int iThreadNo, const char* cFuncName, const char* cFormat)
{
	if (iMsgLevel > iDebugLevel) 
	{
		return;
	}

	WaitForSingleObject (hMutex, INFINITE);

	try
	{
		try 
		{
			if(hFile!=INVALID_HANDLE_VALUE)
			{
				if(isNewFileRequired())
				{
					createFile ();
				}
			}
			else
			{
				createFile ();
			}
		}
		catch (...)
		{
			ReleaseMutex (hMutex);
			return;
		}

		char tempStr[3000];
		char logCharString[2500];
		char tempchar [25];

		getTimeStamp(tempchar);
		strncpy (logCharString, cFormat,sizeof(logCharString)-2);
		logCharString[sizeof(logCharString)-2]=0;

		sprintf (tempStr, "%s|%d|%03d|%-20.20s| %s\r\n", tempchar, iMsgLevel, iThreadNo, cFuncName, logCharString);    
		WriteToFile (tempStr, strlen(tempStr));
	}
	catch(...)
	{
	}
	ReleaseMutex (hMutex);
}

void CLogger::changeDebugLevel(int iNewDebugLevel)
{
	iDebugLevel = iNewDebugLevel;
}

bool CLogger::isNewFileRequired()
{
	if(m_iFileSize.QuadPart>iDebugFileSize*1024*1024)
	{
		return true;
	}
	return false;
}

void CLogger::WriteToFile(LPCVOID buffer,DWORD count)
{
	if(hFile!=INVALID_HANDLE_VALUE)
	{
		unsigned long iBytesWritten=0;
		SetFilePointer (hFile, NULL, NULL, FILE_END);
		if(WriteFile(hFile,buffer,count,&iBytesWritten,NULL))
		{
			m_iFileSize.QuadPart+=iBytesWritten;
		}
	}
}