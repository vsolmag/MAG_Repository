// MessageQueue.cpp: implementation of the CMessageQueue class.
//
//////////////////////////////////////////////////////////////////////


// includes
#include "stdafx.h"
#include "MessageQueue.h"

/**
* values for constants
*/
const int CMessageQueue::READ	= 0;
const int CMessageQueue::WRITE	= 1;
const int CMessageQueue::PEEK   = 2;
const int CMessageQueue::OPEN	= 0;
const int CMessageQueue::CLOSE	= 1;
HMODULE CMessageQueue::hModule=NULL;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/**
* Constructor
*/
CMessageQueue::CMessageQueue() {
	queueHandle = 0;
	iQueueState = CLOSE;
	if(hModule==NULL)
	{
		hModule = LoadLibrary(L"mqutil.dll");
	}
}


/**
* Destructor
*/
CMessageQueue::~CMessageQueue() {
	if (iQueueState == OPEN) closeQueue ();
}



/**
* Used internally to form name of a private queue.
*/
char *CMessageQueue::getPrivateQueueName (const char *cQueueName) {
	char *cPathName = new char [strlen (".\\PRIVATE$\\") + strlen (cQueueName) + 1];
	strcpy (cPathName, ".\\PRIVATE$\\");
	strcat (cPathName, cQueueName);
	return cPathName;
}


/**
* Create Queue
*/
BOOLEAN CMessageQueue::createQueue (char *cQueueName) {

	HRESULT hr;
	BOOLEAN blnSuccess = true;
	PSECURITY_DESCRIPTOR pSecurityDescriptor = NULL;
	DWORD dwCount = 0;	// property count

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values

	MQQUEUEPROPS	queueProps;	// queue properties
	QUEUEPROPID		aQueuePropertyIden [MAX_PROPERTIES];	// array of queue property identifiers


	// set member variables
	char *cPathName = getPrivateQueueName (cQueueName); //NOTE: delete the cPathName object after use

	wchar_t wcQueueName[MAX_QUEUE_NAME_LENGTH];
	wchar_t wcPathName[MAX_QUEUE_NAME_LENGTH];
	swprintf (wcPathName, L"%S", cPathName);
	swprintf (wcQueueName, L"%S", cQueueName);

	// set properties for creating a queue
	aQueuePropertyIden [dwCount] = PROPID_Q_PATHNAME;	// queue path name
	aPropertyValues [dwCount].vt = VT_LPWSTR;
	aPropertyValues [dwCount].pwszVal = wcPathName;		
	dwCount++;

	aQueuePropertyIden [dwCount] = PROPID_Q_LABEL;		// queue path label
	aPropertyValues [dwCount].vt = VT_LPWSTR;
	aPropertyValues [dwCount].pwszVal = wcQueueName;	
	dwCount++;


	// initialize the queue property structure 
	queueProps.cProp = dwCount;
	queueProps.aPropID = aQueuePropertyIden;
	queueProps.aPropVar = aPropertyValues;
	queueProps.aStatus = aStatus;


	// create queue
	// pSecurityDescriptor is NULL at present
	wchar_t wcFormattedName [MAX_FORMATTED_NAME_LENGTH];
	DWORD dwFormatNameLength = MAX_FORMATTED_NAME_LENGTH; 
	hr = MQCreateQueue (pSecurityDescriptor, &queueProps, wcFormattedName, &dwFormatNameLength);

	this->setLastError(hr);
	if (FAILED (hr) && (hr != MQ_ERROR_QUEUE_EXISTS)) 
		blnSuccess = false;

	// clean up things
	delete[] cPathName;

	return blnSuccess;
}


/**
* Takes a read/write mode and the name of the queue.
* For read mode, if a queue doesn't exist a false value is returned.
* For write mode, if a queue doesn't exist, a new one is created.
*/
BOOLEAN CMessageQueue::openQueue (int iModeReadWrite, const char *cQueueName)
{
	BOOLEAN blnSuccess = true;
	HRESULT hr;

	// set member variables
	strcpy (this->cQueueName, cQueueName);
	this->iModeReadWrite = iModeReadWrite;
	char *cPathName = getPrivateQueueName (cQueueName);//NOTE: delete the cPathName object after use

	DWORD dwFormatNameLength = MAX_FORMATTED_NAME_LENGTH;
	wchar_t wcFormatName[MAX_FORMATTED_NAME_LENGTH];
	wchar_t wcPathName[MAX_QUEUE_NAME_LENGTH];
	swprintf (wcPathName, L"%S", cPathName);

	// get formatted name using the API
	hr = MQPathNameToFormatName ( wcPathName, wcFormatName, &dwFormatNameLength);

	// open the queue
	if (iModeReadWrite == READ) {
		// changed to shared mode (in recieve)
		//hr = MQOpenQueue (wcFormatName, MQ_RECEIVE_ACCESS, MQ_DENY_RECEIVE_SHARE, &queueHandle);
		hr = MQOpenQueue (wcFormatName, MQ_RECEIVE_ACCESS, MQ_DENY_NONE, &queueHandle);
	}
	else if (iModeReadWrite == PEEK) {
		hr = MQOpenQueue (wcFormatName, MQ_PEEK_ACCESS, MQ_DENY_NONE, &queueHandle);
	}
	else if (iModeReadWrite == WRITE) {
		hr = MQOpenQueue (wcFormatName, MQ_SEND_ACCESS, MQ_DENY_NONE, &queueHandle);
	}


	// cleanup code
	delete[] cPathName;
	this->setLastError(hr);
	if (FAILED (hr)) {
		iQueueState = CLOSE;
		blnSuccess = false;
	}
	else {
		iQueueState = OPEN;
	}

	return blnSuccess;
}

/**
* Takes a read/write mode and the name of the queue and ip address of the remote machine.
*/
BOOLEAN CMessageQueue::openRemoteQueue (int iModeReadWrite,const char* cIP, const char *cQueueName)
{
	BOOLEAN blnSuccess = true;
	HRESULT hr;

	// set member variables
	strcpy (this->cQueueName, cQueueName);
	this->iModeReadWrite = iModeReadWrite;
	
	wchar_t wcFormatName[MAX_FORMATTED_NAME_LENGTH];
	if(isalpha(cIP[0])==0)
	{
		swprintf(wcFormatName,L"DIRECT=TCP:%S\\PRIVATE$\\%S",cIP,cQueueName);
	}
	else
	{
		swprintf(wcFormatName,L"DIRECT=OS:%S\\PRIVATE$\\%S",cIP,cQueueName);
	}

	// open the queue
	if (iModeReadWrite == READ) {
		// changed to shared mode (in recieve)
		//hr = MQOpenQueue (wcFormatName, MQ_RECEIVE_ACCESS, MQ_DENY_RECEIVE_SHARE, &queueHandle);
		hr = MQOpenQueue (wcFormatName, MQ_RECEIVE_ACCESS, MQ_DENY_NONE, &queueHandle);
	}
	else if (iModeReadWrite == PEEK) {
		hr = MQOpenQueue (wcFormatName, MQ_PEEK_ACCESS, MQ_DENY_NONE, &queueHandle);
	}
	else if (iModeReadWrite == WRITE) {
		hr = MQOpenQueue (wcFormatName, MQ_SEND_ACCESS, MQ_DENY_NONE, &queueHandle);
	}
	this->setLastError(hr);
	if (FAILED (hr)) {
		iQueueState = CLOSE;
		blnSuccess = false;
	}
	else {
		iQueueState = OPEN;
	}

	return blnSuccess;
}



/**
* Closes an open queue
*/
BOOLEAN CMessageQueue::closeQueue () {
	BOOLEAN blnSuccess = true;
	HRESULT hr;

	if (iQueueState == OPEN) {
		hr = MQCloseQueue (queueHandle);
		this->setLastError(hr);
		if (FAILED (hr)) 
			blnSuccess = false; 
		else 
			iQueueState=CLOSE;
	}
	else
		blnSuccess = false;

	return blnSuccess;
}



const char* CMessageQueue::getLastError () 
{
	return sErrorMsg.c_str();
}

void CMessageQueue::setLastError(HRESULT hr)
{
	if(FAILED(hr))
	{
		LPVOID lpMsgBuf;
		if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS,hModule,hr,MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR)&lpMsgBuf,512,NULL)!=0)
		{
			sErrorMsg=(char*)lpMsgBuf;
			LocalFree( lpMsgBuf );
			if(sErrorMsg.size()>=2)
			{
				sErrorMsg.resize(sErrorMsg.size()-2);
			}
		}
	}
	else
	{
		sErrorMsg="";
	}
}

/**
* Method for getting a message from the queue.
* Message label and body should already be created by the calling routine. 
* The size of the label and the body should be passed.
* Returns the number of label characters in iLabelLength.
* Returns the number of body characters in iBodyLength.
* Returns -1 if the api times out
*          0 if the function fails
*          1 if the function succeeds
*/
int CMessageQueue::getMessage (unsigned int & uiPriority, unsigned char *ucLabel, unsigned int &uiLabelLength, 
								   unsigned char *ucBody, unsigned int &uiBodyLength,
								   BOOLEAN blnPeek, int iTimeout, HANDLE hCursor, ULONGLONG &lookupid) {
	HRESULT hr;
	int iSuccess = 1;

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	MQMSGPROPS		msgProps;	// message properties


	if (iQueueState != OPEN)
	{
		sErrorMsg="Queue is not open";
		return 0;
	}


	// return error if trying to write or trying to read in a peek access mode
	if (iModeReadWrite != READ || (iModeReadWrite == PEEK && blnPeek == false)) {
		sErrorMsg="Queue is not in peek or read mode";
		return 0;
	}


	// set properties	
	DWORD dwTimeout = iTimeout;	// inifinite wait
	DWORD dwCount = 0;		// count variable used locally

	wchar_t wcLabel[MAX_LABEL_LENGTH];

	// set properties to fetch from queue
	aMsgPropertyIden[dwCount] = PROPID_M_BODY;	// message body
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caui.cElems = uiBodyLength;
	aPropertyValues [dwCount].caui.pElems = (USHORT*)ucBody;
	dwCount++;
	
	
	aMsgPropertyIden[dwCount] = PROPID_M_LABEL;	// message label
	aPropertyValues [dwCount].vt = VT_LPWSTR;
	aPropertyValues [dwCount].pwszVal = wcLabel;
	dwCount++;


	aMsgPropertyIden[dwCount] = PROPID_M_LABEL_LEN;	// message label length
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = MAX_LABEL_LENGTH;
	dwCount++;


	aMsgPropertyIden [dwCount] = PROPID_M_BODY_SIZE;	// message body size in bytes
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = uiBodyLength;
	dwCount++;

	aMsgPropertyIden [dwCount] = PROPID_M_PRIORITY;	// message priority
	aPropertyValues [dwCount].vt = VT_UI1;
	aPropertyValues [dwCount].bVal = uiPriority;
	dwCount++;

	unsigned char ucMessageID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_MSGID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucMessageID;
	dwCount++;

	unsigned char ucCorrelationID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_CORRELATIONID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucCorrelationID;
	dwCount++;

	aMsgPropertyIden [dwCount] = PROPID_M_LOOKUPID;
	aPropertyValues [dwCount].vt = VT_UI8;
	dwCount++;

	// set message structure
	msgProps.aPropID = aMsgPropertyIden;
	msgProps.aPropVar = aPropertyValues;
	msgProps.aStatus = aStatus;
	msgProps.cProp = dwCount;


	// receive messages using API
	if (blnPeek == TRUE) {
		hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_PEEK_CURRENT, &msgProps, 
			NULL, NULL, hCursor, NULL);
	}
	else {
		hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_RECEIVE, &msgProps, 
			NULL, NULL, hCursor, NULL);
	}
	this->setLastError(hr);
	if (FAILED (hr)) {
		if (hr == MQ_ERROR_IO_TIMEOUT)
			iSuccess = -1;
		else
			iSuccess = 0;
	}
	else {
	// set variable to return the number of bytes read
		uiBodyLength = aPropertyValues [3].ulVal;
		uiLabelLength = aPropertyValues [2].ulVal;	// label is in ASCII
		if(uiLabelLength!=0)
		{
			uiLabelLength--;
		}
		uiPriority= aPropertyValues [4].bVal;//get priority
		lookupid = aPropertyValues[7].uhVal.QuadPart;
		// convert wide characters to unsigned char
		wcstombs ((char *)ucLabel, wcLabel, MAX_LABEL_LENGTH);
	}

	return iSuccess;
}

/* getMessages that works on wchar
*/
int CMessageQueue::getMessage (wchar_t *wcLabel, unsigned int &uiLabelLength, 
								   wchar_t *wcBody, unsigned int &uiBodyLength,
								   BOOLEAN blnPeek, int iTimeout) {
	HRESULT hr;
	int blnSuccess = 1;

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	MQMSGPROPS		msgProps;	// message properties

	if (iQueueState != OPEN)
	{
		sErrorMsg="Queue is not open";
		return 0;
	}

	// return error if trying to write or trying to read in a peek access mode
	if (iModeReadWrite != READ || (iModeReadWrite == PEEK && blnPeek == false)) {
		sErrorMsg="Queue is not in read or peek mode";
		return 0;
	}


	// set properties
	uiBodyLength *= 2;
	
	DWORD dwTimeout = iTimeout;	// inifinite wait
	DWORD dwCount = 0;		// count variable used locally

	// set properties to fetch from queue
	aMsgPropertyIden [dwCount] = PROPID_M_BODY;	// message body
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caui.cElems = uiBodyLength;
	aPropertyValues [dwCount].caui.pElems = (USHORT*)wcBody;
	dwCount++;
	

	aMsgPropertyIden[dwCount] = PROPID_M_LABEL;	// message label
	aPropertyValues [dwCount].vt = VT_LPWSTR;
	aPropertyValues [dwCount].pwszVal = wcLabel;
	dwCount++;


	aMsgPropertyIden[dwCount] = PROPID_M_LABEL_LEN;	// message label length
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = MAX_LABEL_LENGTH;
	dwCount++;


	aMsgPropertyIden [dwCount] = PROPID_M_BODY_SIZE;	// message body size in bytes
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = uiBodyLength;
	dwCount++;

	unsigned char ucMessageID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_MSGID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucMessageID;
	dwCount++;

	unsigned char ucCorrelationID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_CORRELATIONID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucCorrelationID;
	dwCount++;


	// set message structure
	msgProps.aPropID = aMsgPropertyIden;
	msgProps.aPropVar = aPropertyValues;
	msgProps.aStatus = aStatus;
	msgProps.cProp = dwCount;


	// receive messages using API
	if (blnPeek == TRUE) {
		hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_PEEK_CURRENT, &msgProps, 
			NULL, NULL, NULL, NULL);
	}
	else {
		hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_RECEIVE, &msgProps, 
			NULL, NULL, NULL, NULL);
	}

	this->setLastError(hr);
	if (FAILED (hr)) {
		if (hr == MQ_ERROR_IO_TIMEOUT)
			blnSuccess = -1;
		else
			blnSuccess = 0;
	}
	else {
		// set variable to return the number of bytes read
		uiBodyLength = aPropertyValues [3].ulVal/2;
		uiLabelLength = aPropertyValues [2].ulVal;
		if(uiLabelLength!=0)
		{
			uiLabelLength--;
		}
	}

	return blnSuccess;
}



/**
* Method for reading a message from the queue.
* Reading a message removes it from the queue. Message buffer should already be created
* by the calling routine. The size of the buffers should be passed in bytes.
* Returns the label, the size of label, the body and the size of body.
* Returns -1 if the api times out
*          0 if the function fails
*          1 if the function succeeds
*/
int CMessageQueue::readMessageWithPriority (unsigned int & uiPriority,unsigned char *ucLabel, unsigned int &uiLabelLength, unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout)
{
	const int blnPeek = false;
	ULONGLONG lookupid=0;
	return getMessage (uiPriority,ucLabel, uiLabelLength, ucBody, uiBodyLength, blnPeek, iTimeout, NULL,lookupid);
}

int CMessageQueue::readMessage (unsigned char *ucLabel, unsigned int &uiLabelLength, unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout) 
{
	const int blnPeek = false;
	unsigned int uiPriority=0;
	ULONGLONG lookupid=0;
	return getMessage (uiPriority,ucLabel, uiLabelLength, ucBody, uiBodyLength, blnPeek, iTimeout, NULL,lookupid);
}

int CMessageQueue::readMessage (wchar_t *wcLabel, unsigned int &uiLabelLength, wchar_t *wcBody, unsigned int &uiBodyLength, int iTimeout) {
	const int blnPeek = false;
	return getMessage (wcLabel, uiLabelLength, wcBody, uiBodyLength, blnPeek,iTimeout);
}

/**
* Method to read a specific message based on the label search
* You can use * and ? in the searchLabel parameter
* Returns -1 if the api times out
*          0 if the function fails
*          1 if the function succeeds
*/
int CMessageQueue::readSpecificMessage (char *labelToSearch, unsigned char *ucLabel, unsigned int &uiLabelLength, 
											unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout) 
{
	HRESULT hr;
	int iSuccess = 0;

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	MQMSGPROPS		msgProps;	// message properties


	if (iQueueState != OPEN) 
	{
		sErrorMsg="Queue is not open";
		return 0;
	}

	// return error if trying to read in a non-read access mode
	if (iModeReadWrite != READ) 
	{
		sErrorMsg="Queue is not is read mode";
		return 0;
	}


	wchar_t wcLabel[MAX_LABEL_LENGTH];
	DWORD dwTimeout = iTimeout;
	DWORD dwCount = 0;		// count variable used locally
	DWORD dwCountLabelLength = 0;	// required bcz of the while loop

	// set properties to fetch from queue
	aMsgPropertyIden[dwCount] = PROPID_M_LABEL;	// message label
	aPropertyValues [dwCount].vt = VT_LPWSTR;
	aPropertyValues [dwCount].pwszVal = wcLabel;
	dwCount++;

	aMsgPropertyIden[dwCount] = PROPID_M_LABEL_LEN;	// message label length
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = MAX_LABEL_LENGTH;
	dwCountLabelLength = dwCount++;


	unsigned char ucMessageID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_MSGID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucMessageID;
	dwCount++;

	unsigned char ucCorrelationID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_CORRELATIONID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucCorrelationID;
	dwCount++;


	// set message structure
	msgProps.aPropID = aMsgPropertyIden;
	msgProps.aPropVar = aPropertyValues;
	msgProps.aStatus = aStatus;
	msgProps.cProp = dwCount;


	// peek messages using MSMQ API
	HANDLE cursorHandle;
	hr = MQCreateCursor (queueHandle, &cursorHandle);
	if (FAILED (hr)) return 0;

	hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_PEEK_CURRENT, &msgProps, 
			NULL, NULL, cursorHandle, NULL);
	this->setLastError(hr);
	if (FAILED (hr)) {
		if (hr == MQ_ERROR_IO_TIMEOUT)
			iSuccess = -1;
		else
			iSuccess = 0;
	}

	// check if this is the required message
	bool isFound = false;
	while (SUCCEEDED (hr)) 
	{	// hr is 0xc00e001c when cursor has reached the end
		// convert wide characters to unsigned char
		wcstombs ((char *)ucLabel, wcLabel, MAX_LABEL_LENGTH);

		//musharraf
		/*if (CUtilityFunctions::strMatch ((char*)ucLabel, labelToSearch) == 1) {
			iSuccess = 1;
			isFound = true;
			break;
		}*/

		msgProps.aPropVar[dwCountLabelLength].ulVal = MAX_LABEL_LENGTH;
		hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_PEEK_NEXT, &msgProps, 
			NULL, NULL, cursorHandle, NULL);

		iSuccess = (hr == MQ_ERROR_IO_TIMEOUT) ? -1 : 0;
	}


	if (isFound == false) {
		MQCloseCursor (cursorHandle);
		return iSuccess;
	}

	// else read the full message
	unsigned int uiPriority;
	ULONGLONG lookupid=0;
	iSuccess = getMessage (uiPriority,ucLabel, uiLabelLength, ucBody, uiBodyLength, false, iTimeout, cursorHandle,lookupid);
	MQCloseCursor (cursorHandle);
	return iSuccess;
}

int CMessageQueue::peekSpecificMessage (char *labelToSearch, unsigned char *ucLabel, unsigned int &uiLabelLength, 
											unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout) 
{
	HRESULT hr;
	int iSuccess = 0;

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	MQMSGPROPS		msgProps;	// message properties


	if (iQueueState != OPEN) 
	{
		sErrorMsg="Queue is not open";
		return 0;
	}

	// return error if trying to read in a non-read access mode
	if (iModeReadWrite != READ) 
	{
		sErrorMsg="Queue is not is read mode";
		return 0;
	}


	wchar_t wcLabel[MAX_LABEL_LENGTH];
	DWORD dwTimeout = iTimeout;
	DWORD dwCount = 0;		// count variable used locally
	DWORD dwCountLabelLength = 0;	// required bcz of the while loop

	// set properties to fetch from queue
	aMsgPropertyIden[dwCount] = PROPID_M_LABEL;	// message label
	aPropertyValues [dwCount].vt = VT_LPWSTR;
	aPropertyValues [dwCount].pwszVal = wcLabel;
	dwCount++;

	aMsgPropertyIden[dwCount] = PROPID_M_LABEL_LEN;	// message label length
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = MAX_LABEL_LENGTH;
	dwCountLabelLength = dwCount++;


	unsigned char ucMessageID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_MSGID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucMessageID;
	dwCount++;

	unsigned char ucCorrelationID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_CORRELATIONID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucCorrelationID;
	dwCount++;


	// set message structure
	msgProps.aPropID = aMsgPropertyIden;
	msgProps.aPropVar = aPropertyValues;
	msgProps.aStatus = aStatus;
	msgProps.cProp = dwCount;


	// peek messages using MSMQ API
	HANDLE cursorHandle;
	hr = MQCreateCursor (queueHandle, &cursorHandle);
	if (FAILED (hr)) return 0;

	hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_PEEK_CURRENT, &msgProps, 
			NULL, NULL, cursorHandle, NULL);
	this->setLastError(hr);
	if (FAILED (hr)) {
		if (hr == MQ_ERROR_IO_TIMEOUT)
			iSuccess = -1;
		else
			iSuccess = 0;
	}

	// check if this is the required message
	bool isFound = false;
	while (SUCCEEDED (hr)) 
	{	// hr is 0xc00e001c when cursor has reached the end
		// convert wide characters to unsigned char
		wcstombs ((char *)ucLabel, wcLabel, MAX_LABEL_LENGTH);

		//musharraf
		/*if (CUtilityFunctions::strMatch ((char*)ucLabel, labelToSearch) == 1) {
			iSuccess = 1;
			isFound = true;
			break;
		}*/

		msgProps.aPropVar[dwCountLabelLength].ulVal = MAX_LABEL_LENGTH;
		hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_PEEK_NEXT, &msgProps, 
			NULL, NULL, cursorHandle, NULL);

		iSuccess = (hr == MQ_ERROR_IO_TIMEOUT) ? -1 : 0;
	}


	if (isFound == false) {
		MQCloseCursor (cursorHandle);
		return iSuccess;
	}

	// else read the full message
	unsigned int uiPriority;
	ULONGLONG lookupid=0;
	iSuccess = getMessage (uiPriority,ucLabel, uiLabelLength, ucBody, uiBodyLength, true, iTimeout, cursorHandle,lookupid);
	MQCloseCursor (cursorHandle);
	return iSuccess;
}

/**
* Method to peek a message from the queue.
* Peeking a message doesn't remove it from the queue. Message buffer should already be created
* by the calling routine. The size of the buffers should be passed in bytes.
* Returns the label, the size of label, the body and the size of body.
* Returns -1 if the api times out
*          0 if the function fails
*          1 if the function succeeds
*/
int CMessageQueue::peekMessageWithPriority (ULONGLONG &lookupid,unsigned int & uiPriority,unsigned char *ucLabel, unsigned int &uiLabelLength, unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout) {
	const int blnPeek = true;
	return getMessage (uiPriority,ucLabel, uiLabelLength, ucBody, uiBodyLength, blnPeek, iTimeout, NULL,lookupid);
}
int CMessageQueue::peekMessage (ULONGLONG &lookupid,unsigned char *ucLabel, unsigned int &uiLabelLength, unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout) {
	const int blnPeek = true;
	unsigned int uiPriority=0;
	return getMessage (uiPriority,ucLabel, uiLabelLength, ucBody, uiBodyLength, blnPeek, iTimeout, NULL,lookupid);
}

int CMessageQueue::peekMessage (wchar_t *wcLabel, unsigned int &uiLabelLength, wchar_t *wcBody, unsigned int &uiBodyLength, int iTimeout) {
	const int blnPeek = true;
	return getMessage (wcLabel, uiLabelLength, wcBody, uiBodyLength, blnPeek,iTimeout);
}




/**
* Method to get the number of messages available in the queue.
*/
int CMessageQueue::getNumberOfMessages () {
	int nMessages = 0;	
	HRESULT hr;
	BOOLEAN blnSuccess = true;

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	MQMSGPROPS		msgProps;	// message properties

	if (iQueueState != OPEN)
	{
		sErrorMsg="Queue is not open";
		return false;
	}
	
	
	// can get number of messages only for a read or peek access mode queue
	if (iModeReadWrite != READ && iModeReadWrite != PEEK ) {
		sErrorMsg="Queue is not in read or peek mode";
		return false;
	}


	// set properties	
	DWORD dwTimeout = 0;	// timeout immediately if no msg is there
	DWORD dwCount = 0;		// count variable used locally


	// set message structure
	msgProps.aPropID = aMsgPropertyIden;
	msgProps.aPropVar = aPropertyValues;
	msgProps.aStatus = aStatus;
	msgProps.cProp = dwCount;


	// receive messages using API - open cursor and peek all the messages till the end
	HANDLE cursorHandle;
	hr = MQCreateCursor (queueHandle, &cursorHandle);
	if (FAILED (hr)) return nMessages;

	hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_PEEK_CURRENT, &msgProps, 
			NULL, NULL, cursorHandle, NULL);
	while (SUCCEEDED (hr)) { // hr is 0xc00e001c when cursor has reached the end
		nMessages++;
		hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_PEEK_NEXT, &msgProps, 
			NULL, NULL, cursorHandle, NULL);
	}
	this->setLastError(hr);
	MQCloseCursor (cursorHandle);


	return nMessages;

}


/**
* Method for writing a message to the queue.
* Returns false if the message could not be written, true otherwise.
*/
BOOLEAN CMessageQueue::writeMessage (unsigned char *ucLabel, unsigned int uiLabelLength, unsigned char *ucBody, unsigned int uiBodyLength, int iPriority,UINT timeToReachQueue, int delivery) {
	HRESULT hr;
	BOOLEAN blnSuccess = true;

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	MQMSGPROPS		msgProps;	// message properties


	if (iQueueState != OPEN || iModeReadWrite != WRITE) {
		sErrorMsg="Queue is not open or not in write mode";
		return false;
	}

	// set properties
	DWORD dwTimeout = -1;	// inifinite wait
	DWORD dwCount = 0;		// count variable used locally

	wchar_t wcLabel[MAX_LABEL_LENGTH];
	
	// convert label from unsigned char to wide char
	mbstowcs (wcLabel, (char *)ucLabel, MAX_LABEL_LENGTH);

	// set properties to fetch from queue
	aMsgPropertyIden [dwCount] = PROPID_M_BODY;	// message body
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caui.cElems = uiBodyLength;
	aPropertyValues [dwCount].caui.pElems = (USHORT*)ucBody;
	dwCount++;
	
	
	aMsgPropertyIden[dwCount] = PROPID_M_LABEL;	// message label
	aPropertyValues [dwCount].vt = VT_LPWSTR;
	aPropertyValues [dwCount].pwszVal = wcLabel;
	dwCount++;


	aMsgPropertyIden[dwCount] = PROPID_M_LABEL_LEN;	// message label length
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = MAX_LABEL_LENGTH;
	dwCount++;


	aMsgPropertyIden [dwCount] = PROPID_M_BODY_SIZE;	// message body size in bytes
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = uiBodyLength;
	dwCount++;


	aMsgPropertyIden [dwCount] = PROPID_M_PRIORITY;	// message priority
	aPropertyValues [dwCount].vt = VT_UI1;
	aPropertyValues [dwCount].bVal = iPriority;
	dwCount++;

	aMsgPropertyIden [dwCount] = PROPID_M_TIME_TO_REACH_QUEUE;
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = timeToReachQueue;
	dwCount++;

	aMsgPropertyIden [dwCount] = PROPID_M_JOURNAL;
	aPropertyValues [dwCount].vt = VT_UI1;
	aPropertyValues [dwCount].bVal = MQMSG_DEADLETTER;
	dwCount++;
	
	aMsgPropertyIden [dwCount] = PROPID_M_DELIVERY;
	aPropertyValues [dwCount].vt = VT_UI1;
	aPropertyValues [dwCount].bVal = (UCHAR) delivery;
	dwCount++;

	unsigned char ucMessageID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_MSGID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucMessageID;
	dwCount++;

	unsigned char ucCorrelationID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_CORRELATIONID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucCorrelationID;
	dwCount++;


	// set message structure
	msgProps.aPropID = aMsgPropertyIden;
	msgProps.aPropVar = aPropertyValues;
	msgProps.aStatus = aStatus;
	msgProps.cProp = dwCount;


	// send messages using API
	hr = MQSendMessage (queueHandle, &msgProps, MQ_NO_TRANSACTION);
	this->setLastError(hr);
	if (FAILED (hr)) {
		blnSuccess = false;
	}

	//cleanup code
	return blnSuccess;
}



/**
* Method for writing a message to the queue.
* Returns false if the message could not be written, true otherwise.
*/
BOOLEAN CMessageQueue::writeMessage (wchar_t *wcLabel, unsigned int uiLabelLength, wchar_t *wcBody, unsigned int uiBodyLength, int iPriority,UINT timeToReachQueue, int delivery) 
{
	HRESULT hr;
	BOOLEAN blnSuccess = true;

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	MQMSGPROPS		msgProps;	// message properties


	if (iQueueState != OPEN || iModeReadWrite != WRITE) {
		sErrorMsg="Queue is not open or not in write mode";
		return false;
	}

	// set properties
	DWORD dwTimeout = -1;	// inifinite wait
	DWORD dwCount = 0;		// count variable used locally

	// set properties to fetch from queue
	aMsgPropertyIden [dwCount] = PROPID_M_BODY;	// message body
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caui.cElems = uiBodyLength*2;
	aPropertyValues [dwCount].caui.pElems = (USHORT*)wcBody;
	dwCount++;
	
	
	aMsgPropertyIden[dwCount] = PROPID_M_LABEL;	// message label
	aPropertyValues [dwCount].vt = VT_LPWSTR;
	aPropertyValues [dwCount].pwszVal = wcLabel;
	dwCount++;


	aMsgPropertyIden[dwCount] = PROPID_M_LABEL_LEN;	// message label length
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = MAX_LABEL_LENGTH;
	dwCount++;


	aMsgPropertyIden [dwCount] = PROPID_M_BODY_SIZE;	// message body size in bytes
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = uiBodyLength*2;
	dwCount++;

	aMsgPropertyIden [dwCount] = PROPID_M_PRIORITY;	// message priority
	aPropertyValues [dwCount].vt = VT_UI1;
	aPropertyValues [dwCount].bVal = iPriority;
	dwCount++;

	aMsgPropertyIden [dwCount] = PROPID_M_TIME_TO_REACH_QUEUE;
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = timeToReachQueue;
	dwCount++;

	aMsgPropertyIden [dwCount] = PROPID_M_JOURNAL;
	aPropertyValues [dwCount].vt = VT_UI1;
	aPropertyValues [dwCount].bVal = MQMSG_DEADLETTER;
	dwCount++;
	
	aMsgPropertyIden [dwCount] = PROPID_M_DELIVERY;
	aPropertyValues [dwCount].vt = VT_UI1;
	aPropertyValues [dwCount].bVal = (UCHAR) delivery;
	dwCount++;

	unsigned char ucMessageID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_MSGID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucMessageID;
	dwCount++;

	unsigned char ucCorrelationID[100];
	aMsgPropertyIden [dwCount] = PROPID_M_CORRELATIONID;
	aPropertyValues [dwCount].vt = VT_VECTOR | VT_UI1;
	aPropertyValues [dwCount].caub.cElems = 20;
	aPropertyValues [dwCount].caub.pElems = ucCorrelationID;
	dwCount++;


	// set message structure
	msgProps.aPropID = aMsgPropertyIden;
	msgProps.aPropVar = aPropertyValues;
	msgProps.aStatus = aStatus;
	msgProps.cProp = dwCount;


	// send messages using API
	hr = MQSendMessage (queueHandle, &msgProps, MQ_NO_TRANSACTION);
	this->setLastError(hr);
	if (FAILED (hr)) {
		blnSuccess = false;
	}

	return blnSuccess;
}

bool CMessageQueue::removeMessageWithLookupId(ULONGLONG lookupid) {
	
	HRESULT hr;

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	MQMSGPROPS		msgProps;	// message properties


	if (iQueueState != OPEN)
	{
		sErrorMsg="Queue is not open";
		return false;
	}
	
	// can remove messages only for a read access mode queue
	if (iModeReadWrite != READ) {
		sErrorMsg="Queue is not in read mode";
		return false;
	}


	// set properties	
	DWORD dwCount = 0;		// count variable used locally


	// set message structure
	msgProps.aPropID = aMsgPropertyIden;
	msgProps.aPropVar = aPropertyValues;
	msgProps.aStatus = aStatus;
	msgProps.cProp = dwCount;


	// receive messages using API
	hr = MQReceiveMessageByLookupId(queueHandle, lookupid, MQ_LOOKUP_RECEIVE_CURRENT, &msgProps, 
			NULL, NULL, NULL);
	if(FAILED(hr))
	{
		setLastError(hr);
		return false;
	}
	return true;
}

/**
* Removes the given number of messages - Returns number of messages removed
*/
int CMessageQueue::removeMessage (int iCount) {
	int nMessages = 0;	
	HRESULT hr;

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	MQMSGPROPS		msgProps;	// message properties


	if (iQueueState != OPEN)
	{
		sErrorMsg="Queue is not open";
		return 0;
	}
	
	// can remove messages only for a read access mode queue
	if (iModeReadWrite != READ) {
		sErrorMsg="Queue is not in read mode";
		return 0;
	}


	// set properties	
	DWORD dwTimeout = 0;	// timeout immediately if no msg is there
	DWORD dwCount = 0;		// count variable used locally


	// set message structure
	msgProps.aPropID = aMsgPropertyIden;
	msgProps.aPropVar = aPropertyValues;
	msgProps.aStatus = aStatus;
	msgProps.cProp = dwCount;


	// receive messages using API
	while (nMessages < iCount) { // hr is 0xc00e001c when cursor has reached the end
		hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_RECEIVE, &msgProps, 
			NULL, NULL, NULL, NULL);
		if (FAILED (hr)) break;
		nMessages++;
	}


	return nMessages;
}


/**
* Purges all messages in the queue.
*/
BOOLEAN CMessageQueue::flushQueue () {
	BOOLEAN isSuccess = true;
	if (iQueueState != OPEN)
	{
		sErrorMsg="Queue is not open";
		return false;
	}
	// can remove messages only for a read access mode queue
	if (iModeReadWrite != READ) {
		sErrorMsg="Queue is not in read mode";
		return false;
	}
	HRESULT hr = MQPurgeQueue(queueHandle);
	this->setLastError(hr);
	if (FAILED(hr))
		isSuccess = false;
	else
		isSuccess = true;
	return isSuccess;
}



BOOLEAN CMessageQueue::isOpen () {
	if (iQueueState == OPEN) return true;
	else return false;
}



char *CMessageQueue::getName ()
{
	return cQueueName;
}


BOOLEAN CMessageQueue::isEmpty () {
	HRESULT hr;
	BOOLEAN bEmpty = true;

	wchar_t wcLabel [MAX_LABEL_LENGTH];

	HRESULT			aStatus [MAX_PROPERTIES];
	MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	MQMSGPROPS		msgProps;	// message properties

	

	if (iQueueState != OPEN || iModeReadWrite != READ) {
		sErrorMsg="Queue is not open or not in read mode";
		return false;
	}


	// set properties
	
	DWORD dwTimeout = 0;	// inifinite wait
	DWORD dwCount = 0;		// count variable used locally

	// set properties to fetch from queue
	aMsgPropertyIden[dwCount] = PROPID_M_LABEL;	// message label
	aPropertyValues [dwCount].vt = VT_LPWSTR;
	aPropertyValues [dwCount].pwszVal = wcLabel;
	dwCount++;


	aMsgPropertyIden[dwCount] = PROPID_M_LABEL_LEN;	// message label length
	aPropertyValues [dwCount].vt = VT_UI4;
	aPropertyValues [dwCount].ulVal = MAX_LABEL_LENGTH;
	dwCount++;


	// set message structure
	msgProps.aPropID = aMsgPropertyIden;
	msgProps.aPropVar = aPropertyValues;
	msgProps.aStatus = aStatus;
	msgProps.cProp = dwCount;


	// receive messages using API
	hr = MQReceiveMessage (queueHandle, dwTimeout, MQ_ACTION_PEEK_CURRENT, &msgProps, 
			NULL, NULL, NULL, NULL);

	this->setLastError(hr);
	if (hr == MQ_ERROR_IO_TIMEOUT) {
		bEmpty = true;
	}
	else
		bEmpty = false;


	return bEmpty;
}



/**
* Removes a queue from the system
*/
BOOLEAN CMessageQueue::deleteQueue (const char *cQueueName) {
	HRESULT hr;
	BOOLEAN blnSuccess = true;
	char *cPathName = getPrivateQueueName (cQueueName);

	// get formatted name using the API
	DWORD dwFormatNameLength = MAX_FORMATTED_NAME_LENGTH;
	wchar_t wcFormatName[MAX_FORMATTED_NAME_LENGTH];
	wchar_t wcPathName[MAX_FORMATTED_NAME_LENGTH];

	swprintf (wcPathName, L"%S", cPathName);
	hr = MQPathNameToFormatName (wcPathName, wcFormatName, &dwFormatNameLength);

	hr = MQDeleteQueue (wcFormatName);
	this->setLastError(hr);
	if (FAILED (hr)) 
		blnSuccess = false;

	// clean up code
	delete[] cPathName;
	return blnSuccess;
}
