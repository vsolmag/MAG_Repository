// DateTime.h: interface for the CDateTime class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _DATE_TIME_H
#define _DATE_TIME_H


#include <windows.h>


// Time related constants
#define _SECOND ((INT64) 10000000)
#define _MINUTE (60 * _SECOND)
#define _HOUR   (60 * _MINUTE)
#define _DAY    (24 * _HOUR) 


class CDateTime  
{
private:
	SYSTEMTIME systemTime;

public:
	CDateTime ();
	CDateTime (SYSTEMTIME &timeStruct);
	CDateTime (char *cDateTimeString);
		
	ULONG64 getTicks();
	bool refresh ();
	bool addSeconds (unsigned int iSeconds);
	bool addDays (int iDays);
	bool getWeekDay (char *cBuffer);
	bool toString (char *cBuffer);
	bool toGMTString (char *cBuffer);
	bool toDateString (char *cBuffer);
	bool toTimeString (char *cBuffer);
	bool toFormattedString (char *cBuffer);
	SYSTEMTIME getSystemTime(void);
	virtual ~CDateTime();
};

#endif 
