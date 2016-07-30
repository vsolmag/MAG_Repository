#pragma once

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "../CommonFiles/Logger.h"
#include "../CommonFiles/TimedLogger.h"
#include "MAGMsgFmt.h"




using boost::asio::deadline_timer;
using boost::asio::ip::tcp;

using namespace MAGQuoteMTSrv;

class MAGTcpConn : public boost::enable_shared_from_this<MAGTcpConn>
{
	bool stopped_;
	int conn_id;
	int state;	// 0 - Not, 1 - Connected
	int logged_in;
	
	tcp::socket socket_;
	
	char LoginID[12];
	char buffer_read[512];
	
	boost::asio::streambuf input_buffer_;
	
	LogonRequestMsg logon_request_msg;
	StockInfoReqMsg stckreq;
	StockInfoRespMsg1 stckresp;
	GatewayRejectMsg gwrej;
	HeartBeatResp hbtresp;
	SubscribeReqMsg subMsg;
	SubscribeRespMsg1 subResp;
	RefreshReqMsg refreshReqMsg;

	UINT16 symbolID;
	MAGMsgFmt msg_fmt1;
	
	deadline_timer deadline_;
	deadline_timer heartbeat_timer_;
	
	


	void start_connect(tcp::resolver::iterator endpoint_iter);
	void handle_connect(const boost::system::error_code& ec, tcp::resolver::iterator endpoint_iter);
	void start_read();
	void handle_read(const boost::system::error_code& ec, size_t bytes_transferred );
	void start_write(unsigned char*,int len);
	void handle_write(const boost::system::error_code& ec);
	void check_deadline();
	void log_buffer(unsigned char* buffer, int size, int dir);

public:
	typedef boost::shared_ptr<MAGTcpConn> pointer;
	MAGTcpConn(boost::asio::io_service& io_service, int id);
	void start(tcp::resolver::iterator endpoint_iter);
	void stop();
	static CLogger *LogDebug;

};

