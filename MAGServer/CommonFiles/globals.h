// Globals.h
//
//////////////////////////////////////////////////////////////////////

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define DB_FAILURE_THRESHOLD	60



// message and string defines
#define MAX_STRING_LENGTH		256
#define MAX_GUID_LENGTH			40


// SHM defines
#define MAX_PROCESSES			20
#define MAX_CONFIG_PARAMS		100
#define MAX_COMMS_NETWORKS		100


// Message Defines
#define MAX_KEY_LENGTH			512
#define MAX_DEFINITIONS			256
#define	MAX_VARIATION_FIELDS	5

// Message Transformation Defines
#define MAX_METHOD_NAME_LENGTH		50
#define MAX_TRANSFORMATION_METHODS	100

// Queue defines
#define MAX_PROPERTIES				20
#define MAX_LABEL_LENGTH			256
#define MAX_FORMATTED_NAME_LENGTH	256
#define MAX_QUEUE_NAME_LENGTH		256

// Socket defines
#define MAX_ADAPTER_ADDRESS_LEN		256
#define MAX_IP_LENGTH				16
#define MAX_PORT_LENGTH				6

// State Table 
#define MAX_RETURN_VALUE			10

// Service defines
#define SERVICE_CONTROL_USER		128
#define SERVICE_INITIALIZE			128

// Logger
#define TEXT_HEADER	"...***...HEADER...***..."
#define TEXT_FOOTER	"...***...FOOTER...***..."


const unsigned int		NumberofConnections = 4;

// state clients types
enum StateClientType
{
	sctUnknownClient = 0,
	sctRdvTCPIPClient = 1,
	sctRdvTimerClient = 2,
	sctRdvMonClient = 3,
	sctRdvGMDClient = 4,
	sctRdvTPClient = 5
};
#endif