// MAGServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "MAGTcpConn.h"
#include "MAGMsgFmt.h"

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

void create_new_connection(char* host, char* port, int id)
{
	try
	{
		printf ("Hassan thread handler %d \n",id);
		boost::asio::io_service io_service;
		tcp::resolver r(io_service);
		MAGTcpConn c(io_service,id);
		c.start(r.resolve(tcp::resolver::query(host, port)));
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}



int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: client <host> <port>\n";
      return 1;
    }
	boost::thread_group conn_threads;
	   for (int i = 0; i != 1 /*conn_thread_count(4)*/; i++)
		   conn_threads.add_thread(new boost::thread(create_new_connection, argv[1], argv[2], 100+i));

	//create_new_connection(argv[1], argv[2], 5);	// Seprate connection for Unsolicited message

	conn_threads.join_all();

  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}

