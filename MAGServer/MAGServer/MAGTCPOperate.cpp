#include "stdafx.h"
#include "MAGTCPOperate.h"


MAGTCPOperate* MAGTCPOperate::mSingleInstance = NULL;

MAGTCPOperate::MAGTCPOperate(void)
{

}
MAGTCPOperate& MAGTCPOperate::get_Instance()
{
	if(mSingleInstance == NULL)
		mSingleInstance = new MAGTCPOperate();

	return *mSingleInstance;
}
MAGTCPOperate::~MAGTCPOperate(void)
{
}
DWORD MAGTCPOperate::init_connection(LPVOID lparam, int idConnection, char* loginID)
{
	/*MAGTCPOperate* ptrObj =  static_cast<MAGTCPOperate *>(lparam);
	try
	{
		boost::asio::io_service io_service;
		tcp::resolver r(io_service);
	
		ptrObj->mConnectionObj[idConnection] = new MAGTcpConn(io_service,idConnection,loginID);

		ptrObj->mConnectionObj[idConnection]->start(r.resolve(tcp::resolver::query("ip", "port")));

		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}*/
	return 0;
}
void MAGTCPOperate::create_connection()
{
	char * loginArray[] = {"BRN-01", "BRN-02", "BRE-01", "BRE-02"};
	try
	{
		boost::thread_group conn_threads;
		for (int i = 0; i != NumberofConnections; i++)
				conn_threads.add_thread(new boost::thread(init_connection, this, i, loginArray[i]));

		conn_threads.join_all();

	}
	catch (std::exception& e)
	{
	std::cerr << "Exception: " << e.what() << "\n";
	}
}
