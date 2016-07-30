// MessageQueue.h: interface for the CMessageQueue class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _MESSAGEQUEUE_H_
#define _MESSAGEQUEUE_H_

// including header files
#include <memory.h>
#include <stdlib.h>
#include <wchar.h>
#include <windows.h>
#include <mq.h>
#include "globals.h"
#include <string>
using namespace std;
#define MQ_READ_BLOCKING		-1
#define MQ_NO_BLOCKING			0


/**
* Message Queue Wrapper Class.
* This class abstracts the details of using MSMQ API classes provided by Microsoft.
* Note: Queue names are case insensitive.
*/
class CMessageQueue  
{
private:
	char cQueueName [MAX_QUEUE_NAME_LENGTH];
	int iModeReadWrite;
	int iQueueState;
	QUEUEHANDLE queueHandle;

	//MQQUEUEPROPS	queueProps;	// queue properties
	//MQMSGPROPS		msgProps;	// message properties
	//QUEUEPROPID		aQueuePropertyIden [MAX_PROPERTIES];	// array of queue property identifiers
	//MSGPROPID		aMsgPropertyIden [MAX_PROPERTIES];		// array of message property identifiers
	//MQPROPVARIANT	aPropertyValues [MAX_PROPERTIES];		// array of property values
	//HRESULT			aStatus [MAX_PROPERTIES];				// array of status

	string sErrorMsg;
	static HMODULE hModule;
protected:
	/**
	* Used internally to form name of a private queue.
	*/
	char *getPrivateQueueName (const char *cQueueName);

	int getMessage (unsigned int & uiPriority,unsigned char *ucLabel, unsigned int &uiLabelLength, 
					   unsigned char *ucBody, unsigned int &uiBodyLength,
					   BOOLEAN blnPeek, int iTimeout, HANDLE hCursor, ULONGLONG &lookupid);
	int getMessage (wchar_t *wcLabel, unsigned int &uiLabelLength, 
					   wchar_t *wcBody, unsigned int &uiBodyLength,
					   BOOLEAN blnPeek, int iTimeout);
	void setLastError(HRESULT hr);

public:
	/**
	* Queue opening modes
	*/
	static const int READ;
	static const int PEEK;
	static const int WRITE;

	/**
	* Queue states
	*/
	static const int OPEN;
	static const int CLOSE;

	/**
	* Constructor.
	*/
	CMessageQueue();

	/**
	* Get last error
	*/
	const char* getLastError ();

	/**
	* Create queue
	*/
	BOOLEAN createQueue (char *cQueueName);

	/**
	* Takes a read/write mode and the name of the queue.
	* For read mode, if a queue doesn't exist a false value is returned.
	* For write mode, if a queue doesn't exist, a new one is created.
	*/
	BOOLEAN openQueue (int iModeReadWrite, const char *cQueueName);
	BOOLEAN openRemoteQueue(int iModeReadWrite, const char* cIP ,const char *cQueueName);
	/**
	* Method for reading a message from the queue.
	* Reading a message removes it from the queue.
	* Returns the number of chars read.
	*/
	int readMessageWithPriority (unsigned int & uiPriority, unsigned char *ucLabel, unsigned int &uiLabelLength, unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout = MQ_READ_BLOCKING); 
	int readMessage (unsigned char *ucLabel, unsigned int &uiLabelLength, unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout = MQ_READ_BLOCKING); 
	int readMessage (wchar_t *wcLabel, unsigned int &uiLabelLength, wchar_t *wcBody, unsigned int &uiBodyLength, int iTimeout = MQ_READ_BLOCKING); 

	/**
	* Read a specific message based on the label
	*/
	int readSpecificMessage (char *searchLabel,
		unsigned char *ucLabel, unsigned int &uiLabelLength,
		unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout = MQ_NO_BLOCKING);
	int peekSpecificMessage (char *searchLabel,
		unsigned char *ucLabel, unsigned int &uiLabelLength,
		unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout = MQ_NO_BLOCKING);
	/**
	* Method to peek a message from the queue.
	* Peeking a message does not remove it from the queue. It allocates memory itself. 
	* Returns the number of chars read.
	*/
	int peekMessageWithPriority (ULONGLONG &lookupid,unsigned int & uiPriority,unsigned char *ucLabel, unsigned int &uiLabelLength, unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout = MQ_READ_BLOCKING);
	int peekMessage (ULONGLONG &lookupid,unsigned char *ucLabel, unsigned int &uiLabelLength, unsigned char *ucBody, unsigned int &uiBodyLength, int iTimeout = MQ_READ_BLOCKING);
	int peekMessage (wchar_t *wcLabel, unsigned int &uiLabelLength, wchar_t *wcBody, unsigned int &uiBodyLength, int iTimeout = MQ_READ_BLOCKING);

	/**
	* Method to check if the queue is empty
	*/
	BOOLEAN	isEmpty();

	/**
	* Method to get the number of messages available in the queue.
	*/
	int getNumberOfMessages ();

	/**
	* Method for writing a message to the queue.
	* Returns false if the message could not be written, true otherwise.
	*/
	BOOLEAN writeMessage (wchar_t *wcLabel, unsigned int uiLabelLength, wchar_t *wcBody, unsigned int uiBodyLength, int iPriority=3,UINT timeToReachQueue = LONG_LIVED, int delivery=MQMSG_DELIVERY_EXPRESS);
	BOOLEAN writeMessage (unsigned char *ucLabel, unsigned int uiLabelLength, unsigned char *ucBody, unsigned int uiBodyLength, int iPriority=3,UINT timeToReachQueue = LONG_LIVED, int delivery=MQMSG_DELIVERY_EXPRESS);

	/**
	* Removes the given number of messages from the queue - default 1
	* Returns number of messages removed from the queue
	*/ 
	int removeMessage (int iCount = 1);
	bool removeMessageWithLookupId(ULONGLONG lookupid);
	/**
	* Purges all messages in the queue.
	*/
	BOOLEAN flushQueue ();

	/**
	* Removes a queue from the system
	*/
	BOOLEAN deleteQueue (const char *cQueueName);

	/**
	* Returns queue name
	*/
	char *getName();

	/**
	* Check if queue is open
	*/
	BOOLEAN isOpen ();


	/**
	* Closes an open queue
	*/
	BOOLEAN closeQueue (); 

	/**
	* Destructor
	*/
	virtual ~CMessageQueue();
};


#endif
