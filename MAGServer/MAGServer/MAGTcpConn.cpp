#include "stdafx.h"
#include "MAGTcpConn.h"

#include <iostream>
#include <boost/array.hpp>
#include <boost/thread/thread.hpp> 
#include "../CommonFiles/Logger.h"
#include "../CommonFiles/TimedLogger.h"

using namespace std;


void hexDump (char *desc, void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;
	
	// Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %i\n",len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0) 
                printf ("  %s\n", buff);
				
	        // Output the offset.
            printf ("  %04x ", i);
		}

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);
		
		// And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
		i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
	
	return ;
}


void MAGTcpConn::log_buffer(unsigned char* buffer, int size, int dir)
{
	char log_buffer[512] = "";
	unsigned char* pc=(unsigned char*)buffer;
	for (int i=0; i<size; i++)
		sprintf (log_buffer + strlen(log_buffer)," %02x", pc[i]);
	if (dir == 1)
		LogDebug->Log (0, 0, "Send Buffer", "%s",log_buffer);
	else
		LogDebug->Log (0, 0, "Recevie Buffer", "%s",log_buffer);
}

CLogger *MAGTcpConn::LogDebug;
MAGTcpConn::MAGTcpConn(boost::asio::io_service& io_service, int id)
    : stopped_(false),
      socket_(io_service),
      deadline_(io_service),
      heartbeat_timer_(io_service),
	  conn_id(id),
	  state(0),
	  logged_in(0)
{
		//MAGTcpConn::LogDebug = new CTimedLogger("D:\\hassan.txt",3,1000);
		MAGTcpConn::LogDebug = new CTimedLogger("C:\\Users\\developer2\\MAGQuoteTCPSrv.txt",3,1000);
		/*C:\\Users\\developer2\\MAGQuoteTCPSrv.txt*/
		LogDebug->Log (0, 0, "MagTcpConn", "MAGQuoteTCPSrv Started");

}

// Called by the user of the client class to initiate the connection process.
// The endpoint iterator will have been obtained using a tcp::resolver.
void MAGTcpConn::start(tcp::resolver::iterator endpoint_iter)
{
    // Start the connect actor.
    start_connect(endpoint_iter);

    // Start the deadline actor. You will note that we're not setting any
    // particular deadline here. Instead, the connect and input actors will
    // update the deadline prior to each asynchronous operation.
	deadline_.async_wait(boost::bind(&MAGTcpConn::check_deadline, this));
}

// This function terminates all the actors to shut down the connection. It
// may be called by the user of the client class, or by the class itself in
// response to graceful termination or an unrecoverable error.
void MAGTcpConn::stop()
{
    stopped_ = true;
    socket_.close();
	state = 0;
    deadline_.cancel();
    heartbeat_timer_.cancel();
}

void MAGTcpConn::start_connect(tcp::resolver::iterator endpoint_iter)
{
    if (endpoint_iter != tcp::resolver::iterator())
    {
		std::stringstream buffer;
		buffer << "Trying " << endpoint_iter->endpoint() << "...\n";
		std::string text(buffer.str()); 
		LogDebug->Log (0, 0, "start_connect", "%s",text.c_str());
	  
		// Set a deadline for the connect operation.
		deadline_.expires_from_now(boost::posix_time::seconds(60));

		// Start the asynchronous connect operation.
		socket_.async_connect(endpoint_iter->endpoint(),
		  boost::bind(&MAGTcpConn::handle_connect,
            this, _1, endpoint_iter));
	}
	else
	{
		// There are no more endpoints to try. Shut down the client.
		stop();
    }
}

void MAGTcpConn::handle_connect(const boost::system::error_code& ec,
      tcp::resolver::iterator endpoint_iter)
{
    if (stopped_)
      return;
	
	std::stringstream buffer;

    // The async_connect() function automatically opens the socket at the start
    // of the asynchronous operation. If the socket is closed at this time then
    // the timeout handler must have run first.
    if (!socket_.is_open())
    {
      std::cout << "Connect timed out\n";
	  LogDebug->Log (0, 0, "handle_connect", "Connect timed out");
      // Try the next available endpoint.
      start_connect(++endpoint_iter);
    }

    // Check if the connect operation failed before the deadline expired.
    else if (ec)
    {
      std::cout << "Connect error: " << ec.message() << "\n";
	  buffer << "Connect error: " << ec.message() << "\n";
	  std::string text(buffer.str()); 
	  LogDebug->Log (0, 0, "handle_connect", "%s",text.c_str());
	  
      // We need to close the socket used in the previous connection attempt
      // before starting a new one.
      socket_.close();

      // Try the next available endpoint.
      start_connect(++endpoint_iter);
    }

    // Otherwise we have successfully established a connection.
    else
    {
      std::cout << "Connected to " << endpoint_iter->endpoint() << "\n";
	  buffer << "Connected to " << endpoint_iter->endpoint() << "\n";
	  std::string text(buffer.str()); 
	  LogDebug->Log (0, 0, "handle_connect", "%s",text.c_str());

	  // State changed to connected
	  state = 1;

	  // Start the input actor.
	  start_read();

	 /*********************************/
	// if connection is not logged in,  Sent Logon request 
	if (!logged_in) {
		msg_fmt1.Format_logon_request_message((unsigned char*)&logon_request_msg);
	
		hexDump ("my_str", &logon_request_msg, sizeof (logon_request_msg));
	

	//	this->log_buffer((unsigned char*)&logon_request_msg, sizeof(logon_request_msg), 1);
		LogDebug->Log (0, 0, "LogonRequestPacket", "MsgType: %u | MsgLen: %u | MsgSeqNum: %u | MsgSendtime: %u | LoginID: %s | LastMsgSeqNum: %u ",
			logon_request_msg.Hdr.MsgType, logon_request_msg.Hdr.MsgLen, logon_request_msg.Hdr.MsgSeqNo, logon_request_msg.Hdr.MsgSendTime, logon_request_msg.SenderCompID, logon_request_msg.LastMsgSeqNo);
	}
	/*********************************/
      // Start the heartbeat actor.
	start_write((unsigned char*)&logon_request_msg,sizeof(logon_request_msg));
    }
}

void MAGTcpConn::start_read()
{
    // Set a deadline for the read operation.
    deadline_.expires_from_now(boost::posix_time::seconds(30));

	//Message size and buffer read from Socket
	//boost::asio::async_read(socket_, boost::asio::buffer(buffer_read,108),  boost::bind(&MAGTcpConn::handle_read, this, _1,
		//boost::asio::placeholders::bytes_transferred));

	    socket_.async_read_some(boost::asio::buffer(buffer_read, 512),
			boost::bind(&MAGTcpConn::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));

}

void MAGTcpConn::handle_read(const boost::system::error_code& ec, size_t bytes_received )
{
    if (stopped_) {
		cout << "Stopped here by library" << endl;
      return;
	}

    if (!ec)
    {

      std::string line = buffer_read;

	  // Empty messages are heartbeats and so ignored.
      if (!line.empty())
	  {
        std::cout << "Received: " << line << "\n";
		std::cout << "Received bytes" << bytes_received << endl;
		msg_fmt1.parse_response((unsigned char*)buffer_read);
		
		
		MAGQuoteMTSrv::MsgType msgType = msg_fmt1.get_msg_type((unsigned char*)buffer_read);
		if(msgType == LOGON_ACCEPT_MESSAGE1 || msgType == LOGON_ACCEPT_MESSAGE2)
		{
		
			hexDump("Recevied buffer Accept",buffer_read,bytes_received);
			LogDebug->Log (0, 0, "MagTcpConn", "Logon Accept Request Received");
			LogDebug->Log (0, 0, "MagTcpConn", "Sending StockInfo Request Message");
			//this->log_buffer((unsigned char*) buffer_read, bytes_received, 2);
			msg_fmt1.Format_stockinfo_req_message((unsigned char *)&stckreq);
			std::cout << "sending stock req" << endl;
			start_write((unsigned char *)&stckreq,sizeof(stckreq));
				
		}
		else if(msgType == SESSION_TEST_REQUEST || msgType == SESSION_SEQ_UP_MESSAGE)
		{
		
			hexDump("Recevied buffer Session test",buffer_read,bytes_received);
			LogDebug->Log (0, 0, "MagTcpConn", "Session Test Message Recieved");

			//this->log_buffer((unsigned char*) buffer_read, bytes_received, 2);
			msg_fmt1.Format_heartbeat_resp_message((unsigned char *)&hbtresp);
			LogDebug->Log (0, 0, "MagTcpConn", "Sending HeartBeat in Response");

			std::cout << "sending hbt resp req" << endl;
			start_write((unsigned char *)&hbtresp,sizeof(hbtresp));

		}
		
		else if(msgType == STOCK_INFO_RESP_MESSAGE1)
		{
			//hexDump("Recevied buffer Stock Resp",buffer_read,bytes_received);
			
			//this->log_buffer((unsigned char*) buffer_read, bytes_received, 2);
			memcpy(&stckresp,buffer_read,sizeof(stckresp));
			symbolID = stckresp.StockInfoRecord.StockNo;
			LogDebug->Log (0, 0, "MagTcpConn", "Stock Information Response Recieved with Symbol ID: %d",symbolID);
			printf("Stock info resp : Symbol ID is %d\n",symbolID);
			LogDebug->Log (0, 0, "MagTcpConn", "Sending Subscribe request for Symbol : %s and Symbol ID: %d",stckresp.StockInfoRecord.StockSymbol,symbolID);
			msg_fmt1.Format_subscribe_req_message((unsigned char*)&subMsg,symbolID);
			std::cout << "sending hbt subscribe request" << endl;
			start_write((unsigned char *)&subMsg,sizeof(subMsg));
		}

		else if(msgType == SUBSCRIBE_RESP_MESSAGE1)
		{
	//		hexDump("Recevied buffer subscribe response",buffer_read,bytes_received);
			printf("Subscribe response\n");
			//this->log_buffer((unsigned char*) buffer_read, bytes_received, 2);
			memcpy(&subResp,buffer_read,sizeof(subResp));
			symbolID = subResp.StockInfoRecord.StockNo;
			printf("subscribe %d\n",subResp.SubscribeStatus);
			//LogDebug->Log (0, 0, "MagTcpConn", "Recieve Subscribe Response for Symbol: %s, Symbol ID: %d and Subscribe Status: %d",subResp.StockInfoRecord.StockSymbol,symbolID,subResp.SubscribeStatus);
			LogDebug->Log (0, 0, "MagTcpConn", "Recieve Subscribe Response for Symbol: %s",subResp.StockInfoRecord.StockSymbol);
			LogDebug->Log (0, 0, "MagTcpConn", "Recieve Subscribe Response for Symbol ID: %d",symbolID);
			LogDebug->Log (0, 0, "MagTcpConn", "Recieve Subscribe Response for Subscribe Status: %d",subResp.SubscribeStatus);

			if(subResp.SubscribeStatus == 1)
			{
				LogDebug->Log (0, 0, "MagTcpConn", "Sending Refresh Request for Symbol ID: %d",symbolID);
				msg_fmt1.Format_refresh_req_message((unsigned char*)&refreshReqMsg,symbolID);
			std::cout << "sending Refresh request" << endl;
			start_write((unsigned char *)&refreshReqMsg,sizeof(refreshReqMsg));

			}
		}

		else if(msgType == GATEWAY_REJECT_MESSAGE)
		{
			//this->log_buffer((unsigned char*) buffer_read, bytes_received, 2);
			hexDump("Recevied buffer GW reject",buffer_read,bytes_received);
			memcpy(&gwrej,buffer_read,sizeof(gwrej));
			LogDebug->Log (0, 0, "MagTcpConn", "Gateway Reject Message Received");
			printf("gwrej error refSAPI Msg: %u | DMM REJECT CODE: %u | INVALID FIELD VALUE: %u",gwrej.refSAPIMsg,gwrej.DMMRejectCode,gwrej.refErrorTag);
			LogDebug->Log (0, 0,"GatewayReject Msg", "gwrej error refSAPI Msg: %u | DMM REJECT CODE: %u | INVALID FIELD VALUE: %u",gwrej.refSAPIMsg,gwrej.DMMRejectCode,gwrej.refErrorTag);
		}

		else if(msgType == BOOKSTATE_FULL_UPDATE_MESSAGE_SOLICITED || msgType == BOOKSTATE_FULL_UPDATE_MESSAGE_UNSOLICITED)
		{
	//		this->log_buffer((unsigned char*) buffer_read, bytes_received, 2);
		//	hexDump("Recevied buffer GW reject",buffer_read,bytes_received);
		//	memcpy(&gwrej,buffer_read,sizeof(gwrej));
			LogDebug->Log (0, 0, "MagTcpConn", "BookState Full Update Message Recieved for Symbol ID %d",symbolID);
			printf("getting bookstate full update\n");
			msg_fmt1.parse_response((unsigned char*)buffer_read);
			boost::this_thread::sleep_for( boost::chrono::seconds(10) );
			LogDebug->Log (0, 0, "MagTcpConn", "Sending Refresh Request for Symbol ID: %d",symbolID);
			msg_fmt1.Format_refresh_req_message((unsigned char*)&refreshReqMsg,symbolID);
			std::cout << "sending Refresh request" << endl;
			start_write((unsigned char *)&refreshReqMsg,sizeof(refreshReqMsg));
		//	LogDebug->Log (0, 0,"GatewayReject Msg", "gwrej error refSAPI Msg: %u | DMM REJECT CODE: %u | INVALID FIELD VALUE: %u",gwrej.refSAPIMsg,gwrej.DMMRejectCode,gwrej.refErrorTag);
		}
		else
		{
			hexDump("Recevied buffer",buffer_read,bytes_received);
		}
      }

    start_read();
    }
    else
    {
      std::cout << "Error on receive: " << ec.message() << "\n";

      //stop();
    }
}

void MAGTcpConn::start_write(unsigned char* body, int len)
{
    if (stopped_)
      return;
    
	std::cout << "Sending Buffer" << endl;
	hexDump ("my_str", body, len);
	// Start an asynchronous operation to send a message.
	boost::asio::async_write(socket_, boost::asio::buffer((unsigned char*)body,len),
		boost::bind(&MAGTcpConn::handle_write, this, _1));
  }


  void MAGTcpConn::handle_write(const boost::system::error_code& ec)
  {
    if (stopped_)
      return;

    if (!ec)
    {
      // Wait 10 seconds before sending the next heartbeat.
      //heartbeat_timer_.expires_from_now(boost::posix_time::seconds(10));
	  //heartbeat_timer_.async_wait(boost::bind(&MAGTcpConn::start_write, this));
    }
    else
    {
      std::cout << "Error on heartbeat: " << ec.message() << "\n";

      //stop();
    }
	//start_write(); for infinite sending
  }

  void MAGTcpConn::check_deadline()
  {
    if (stopped_)
      return;

    // Check whether the deadline has passed. We compare the deadline against
    // the current time since a new asynchronous operation may have moved the
    // deadline before this actor had a chance to run.
    if (deadline_.expires_at() <= deadline_timer::traits_type::now())
    {
      // The deadline has passed. The socket is closed so that any outstanding
      // asynchronous operations are cancelled.
//      socket_.close();

      // There is no longer an active deadline. The expiry is set to positive
      // infinity so that the actor takes no action until a new deadline is set.
      deadline_.expires_at(boost::posix_time::pos_infin);
    }

    // Put the actor back to sleep.
	deadline_.async_wait(boost::bind(&MAGTcpConn::check_deadline, this));
  }
  
