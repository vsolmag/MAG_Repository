#include "stdafx.h"
#include "timedlogger.h"
#include "Directory.h"

CTimedLogger::CTimedLogger(const char *cFilename, int iDebugLevel, int iDbgFileSize, bool redirectStdErr) : 
CLogger (cFilename, iDebugLevel, iDbgFileSize,redirectStdErr)
{
	iFileIndex=0;
	CTimedLogger::createFile (true);
}

CTimedLogger::~CTimedLogger(void)
{
}

/**
* Create File
*/
void CTimedLogger::createFile (bool init)
{
	char cTimePart [MAX_STRING_LENGTH];
	char cFilename [MAX_STRING_LENGTH];
	char cExtension [MAX_STRING_LENGTH];

	dtFileOpened.refresh();
	dtFileOpened.toDateString (cDateFileOpened);
	strcpy (cTimePart, cDateFileOpened+4);	// copy only month and day

	// break file name into extension and filename and then append the date part
	
	CDirectory::breakFilename (cLogFileName, cFilename, cExtension);
	sprintf (cInternalFileName, "%s%s.%s", cFilename,cTimePart, cExtension);
	CLogger::createFile (init);
}

bool CTimedLogger::isNewFileRequired ()
{
	char cDateNow [MAX_STRING_LENGTH];	// current date time in string form
	CDateTime dtNow;
	dtNow.toDateString (cDateNow);
	bool bNewFileRequired = _strcmpi (cDateNow, cDateFileOpened) > 0;
	if(!bNewFileRequired)
	{
		bNewFileRequired=CLogger::isNewFileRequired();
	}
	else
	{
		iFileIndex=0;
	}
	return bNewFileRequired;
}