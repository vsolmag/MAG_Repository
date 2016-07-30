#pragma once

#include "MAGTcpConn.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>


class MAGTCPOperate
{
public:
	static	MAGTCPOperate& get_Instance();
	virtual ~MAGTCPOperate(void);

	static	DWORD	init_connection(LPVOID lparam, int idConnection, char* loginID);
			void	create_connection(); 

private:
	MAGTCPOperate(void);
	boost::thread_group thgroup;
	MAGTcpConn* mConnectionObj[4];
	static MAGTCPOperate* mSingleInstance;
	
};

