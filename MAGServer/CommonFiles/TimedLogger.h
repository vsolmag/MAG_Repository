#pragma once
#include "DateTime.h"
#include "Logger.h"
#include "globals.h"

class CTimedLogger : public CLogger
{
private:
	CDateTime dtFileOpened;						// date and time on which the file was opened
	char cDateFileOpened [MAX_STRING_LENGTH];	// file opened date in string form

public:
	CTimedLogger(const char *cFilename, int iDebugLevel = 3, int iDbgFileSize=500, bool redirectStdErr=false);
	virtual void createFile (bool init=false);
	virtual ~CTimedLogger(void);

protected:
	/**
	* Is New File Required
	*/
	virtual bool isNewFileRequired (); 
};
