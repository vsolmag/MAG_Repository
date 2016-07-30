#include "stdafx.h"
#include "MAGTcpConn.h"
#include "MAGMsgFmt.h"


namespace MAGQuoteMTSrv
{

MAGMsgFmt::MAGMsgFmt(void)
{
	//MAGTcpConn::LogDebug->Log(0,0,"MagMsgFmt","Initializing");
}

void MAGMsgFmt::Format_logon_request_message(unsigned char* body)
{
	MAGTcpConn::LogDebug->Log(0,0,"MagMsgFmt","Formating Logon Request");
	make_logon_request_body(body);
}

void MAGMsgFmt::Format_session_test_message(unsigned char* body)
{
	make_session_test_body(body);
}

void MAGMsgFmt::Format_heartbeat_resp_message(unsigned char* body)
{
	make_heartbeat_resp_body(body);
}

void MAGMsgFmt::Format_session_sequp_message(unsigned char* body)
{
	make_session_sequp_body(body);
}

void MAGMsgFmt::Format_subscribe_req_message(unsigned char* body,UINT16 symbolID)
{
	make_subscribe_req_body(body,symbolID);
}

void MAGMsgFmt::Format_symbol_test_req_message(unsigned char* body)
{
	make_symbol_test_req_body(body);
}

void MAGMsgFmt::Format_unsubscribe_req_message(unsigned char* body)
{
	make_unsubscribe_req_body(body);
}

void MAGMsgFmt::Format_stockinfo_req_message(unsigned char* body)
{
	make_stockinfo_req_body(body);
}

void MAGMsgFmt::Format_refresh_req_message(unsigned char* body,UINT16 symbolID)
{
	make_refresh_req_body(body,symbolID);
}


MsgHeader MAGMsgFmt::make_header(MsgType MsgType)
{
	MsgHeader MsgHdr;
	memset(&MsgHdr,0,sizeof(MsgHdr));

	switch (MsgType)
	{
		case LOGON_REQUEST_MESSAGE:
		{	
			MsgHdr.MsgType = LOGON_REQUEST_MESSAGE;
			MsgHdr.MsgLen = 102;
		}
			break;
		case SESSION_TEST_REQUEST:
		{
			MsgHdr.MsgType = SESSION_TEST_REQUEST;
			MsgHdr.MsgLen = 20;
		}
			break;
		case HEART_BEAT_RESPONSE:
		{
			MsgHdr.MsgType = HEART_BEAT_RESPONSE;
			MsgHdr.MsgLen = 20;
		}
			break;
		case SESSION_SEQ_UP_MESSAGE:
		{
			MsgHdr.MsgType = SESSION_SEQ_UP_MESSAGE;
			MsgHdr.MsgLen = 24;
		}
			break;
		case SUBSCRIBE_REQ_MESSAGE:
		{
			MsgHdr.MsgType = SUBSCRIBE_REQ_MESSAGE;
			MsgHdr.MsgLen = 24;
		}
			break;
		case SYMBOL_TEST_REQ_MESSAGE:
		{
			MsgHdr.MsgType = SYMBOL_TEST_REQ_MESSAGE;
			MsgHdr.MsgLen = 24;
		}
			break;
		case UNSUBSCRIBE_REQ_MESSAGE:
		{
			MsgHdr.MsgType = UNSUBSCRIBE_REQ_MESSAGE;
			MsgHdr.MsgLen = 24;
		}
			break;
		case STOCK_INFO_REQ_MESSAGE:
		{
			MsgHdr.MsgType = STOCK_INFO_REQ_MESSAGE;
			MsgHdr.MsgLen = 40;
		}
			break;
		case REFRESH_REQUEST_MESSAGE:
		{
			MsgHdr.MsgType = REFRESH_REQUEST_MESSAGE;
			MsgHdr.MsgLen = 24;
		}
			break;
		default:
			MsgHdr.MsgType = 0;
	}
	
	return MsgHdr;

}

void MAGMsgFmt::make_logon_request_body(unsigned char* body)
{
	LogonRequestMsg LogonMsg;
	memset(&LogonMsg,0,sizeof(LogonMsg));
	LogonMsg.Hdr = 	make_header(LOGON_REQUEST_MESSAGE);
    LogonMsg.Hdr.MsgSeqNo = 1;
	LogonMsg.LastMsgSeqNo = 0;
	memset(LogonMsg.SenderCompID,0,12);
	lstrcpyA(LogonMsg.SenderCompID,"BRE-01");
	memset(&LogonMsg.MessageVersionProfile,0,64);
	LogonMsg.CancelOnDisconnect = 0;
	LogonMsg.UnSolicatedAckSub = 0;
	memcpy(body,&LogonMsg,sizeof(LogonMsg));

	//MAGTcpConn::LogDebug->Log(0,0,"Logon Request","MsgSeqNo: %d || LoginID: %s ",LogonMsg.Hdr.MsgSeqNo,LogonMsg.SenderCompID);
	MAGTcpConn::LogDebug->Log(0,0,"Logon Request","MsgSeqNo: %d",LogonMsg.Hdr.MsgSeqNo);
	MAGTcpConn::LogDebug->Log(0,0,"Logon Request","LoginID: %s ",LogonMsg.SenderCompID);

}

void MAGMsgFmt::make_session_test_body(unsigned char* body)
{
	SessionTestMsg SessionMsg;
	memset(&SessionMsg,0,sizeof(SessionMsg));
	
	SessionMsg.Hdr = 	make_header(SESSION_TEST_REQUEST);
	SessionMsg.Hdr.MsgSeqNo = 1;
    
	memcpy(body,&SessionMsg,sizeof(SessionMsg));

}

void MAGMsgFmt::make_heartbeat_resp_body(unsigned char* body)
{
	HeartBeatResp HeartBeatMsg;
	memset(&HeartBeatMsg,0,sizeof(HeartBeatMsg));
	
	HeartBeatMsg.Hdr = 	make_header(HEART_BEAT_RESPONSE);
	HeartBeatMsg.Hdr.MsgSeqNo = 1;
    
	memcpy(body,&HeartBeatMsg,sizeof(HeartBeatMsg));

}

void MAGMsgFmt::make_session_sequp_body(unsigned char* body)
{
	SessionSeqUpMsg SessionSeqMsg;
	memset(&SessionSeqMsg,0,sizeof(SessionSeqMsg));
	
	SessionSeqMsg.Hdr = 	make_header(SESSION_SEQ_UP_MESSAGE);
	SessionSeqMsg.Hdr.MsgSeqNo = 1;
	SessionSeqMsg.NextSeqMsgNum = 2;
	memcpy(body,&SessionSeqMsg,sizeof(SessionSeqMsg));
}

void MAGMsgFmt::make_subscribe_req_body(unsigned char* body,UINT16 symbolID)
{
	SubscribeReqMsg SubReqMsg;
	memset(&SubReqMsg,0,sizeof(SubReqMsg));
	
	SubReqMsg.Hdr = 	make_header(SUBSCRIBE_REQ_MESSAGE);
	SubReqMsg.Hdr.MsgSeqNo = 3;
	SubReqMsg.Hdr.SymbolID = symbolID;
	SubReqMsg.SAPIMsgID = 2;
	memcpy(body,&SubReqMsg,sizeof(SubReqMsg));
	
	//MAGTcpConn::LogDebug->Log (0, 0, "Subscribe request", "SymbolID: %d || SAPIMsgID: %d",symbolID,SubReqMsg.SAPIMsgID);
	MAGTcpConn::LogDebug->Log (0, 0, "Subscribe request", "SymbolID: %d",symbolID);
	MAGTcpConn::LogDebug->Log (0, 0, "Subscribe request", "SAPIMsgID: %d",SubReqMsg.SAPIMsgID);
}

void MAGMsgFmt::make_symbol_test_req_body(unsigned char* body)
{
	SymbolTestReqMsg SymbolTstRqMsg;
	memset(&SymbolTstRqMsg,0,sizeof(SymbolTstRqMsg));
	
	SymbolTstRqMsg.Hdr = 	make_header(SYMBOL_TEST_REQ_MESSAGE);
	SymbolTstRqMsg.Hdr.MsgSeqNo = 1;
	SymbolTstRqMsg.SAPIMsgID = 1;
	memcpy(body,&SymbolTstRqMsg,sizeof(SymbolTstRqMsg));

}

void MAGMsgFmt::make_unsubscribe_req_body(unsigned char* body)
{
	UnSubscribeReqMsg UnSubReqMsg;
	memset(&UnSubReqMsg,0,sizeof(UnSubReqMsg));
	
	UnSubReqMsg.Hdr = 	make_header(UNSUBSCRIBE_REQ_MESSAGE);
	UnSubReqMsg.Hdr.MsgSeqNo = 1;
	UnSubReqMsg.SAPIMsgID = 1;
	memcpy(body,&UnSubReqMsg,sizeof(UnSubReqMsg));

}

void MAGMsgFmt::make_stockinfo_req_body(unsigned char* body)
{
	StockInfoReqMsg StckInfReqMsg;
	memset(&StckInfReqMsg,0,sizeof(StckInfReqMsg));
	
	StckInfReqMsg.Hdr = make_header(STOCK_INFO_REQ_MESSAGE);
	StckInfReqMsg.Hdr.MsgSeqNo = 2;
	StckInfReqMsg.SAPIMsgID = 2;
	StckInfReqMsg.DBKDevice = 42;
	StckInfReqMsg.PostID = 11;
	lstrcpyA(StckInfReqMsg.StockSymbol,"AMAT");
	StckInfReqMsg.TeeID = 'D';

	memcpy(body,&StckInfReqMsg,sizeof(StckInfReqMsg));

	//MAGTcpConn::LogDebug->Log (0, 0, "StockInfo Request", "SAPIMsgID: %d || POST ID: %d || TEE ID: %c || DBK DEVICE ID: %d || Stock Symbol: %s",StckInfReqMsg.SAPIMsgID,
		//								StckInfReqMsg.PostID,StckInfReqMsg.TeeID,StckInfReqMsg.DBKDevice,StckInfReqMsg.StockSymbol);
	MAGTcpConn::LogDebug->Log (0, 0, "StockInfo Request", "SAPIMsgID: %d",StckInfReqMsg.SAPIMsgID);
	MAGTcpConn::LogDebug->Log (0, 0, "StockInfo Request", "POST ID: %d",StckInfReqMsg.PostID);
	MAGTcpConn::LogDebug->Log (0, 0, "StockInfo Request", "TEE ID: %c",StckInfReqMsg.TeeID);
	MAGTcpConn::LogDebug->Log (0, 0, "StockInfo Request", "DBK DEVICE ID: %d",StckInfReqMsg.DBKDevice);
	MAGTcpConn::LogDebug->Log (0, 0, "StockInfo Request", "Stock Symbol: %s",StckInfReqMsg.StockSymbol);
}

void MAGMsgFmt::make_refresh_req_body(unsigned char* body,UINT16 symbolID)
{
	RefreshReqMsg rfrshReqMsg;
	memset(&rfrshReqMsg,0,sizeof(rfrshReqMsg));
	
	rfrshReqMsg.Hdr = make_header(REFRESH_REQUEST_MESSAGE);
	rfrshReqMsg.Hdr.MsgSeqNo = 4;
	rfrshReqMsg.Hdr.SymbolID = symbolID;
	rfrshReqMsg.SAPIMsgID = 3;
	memcpy(body,&rfrshReqMsg,sizeof(rfrshReqMsg));
	//MAGTcpConn::LogDebug->Log (0, 0, "Refresh Request", "Symbol ID %d || SAPIMsgID %d",symbolID,rfrshReqMsg.SAPIMsgID);
	MAGTcpConn::LogDebug->Log (0, 0, "Refresh Request", "Symbol ID: %d",symbolID);
	MAGTcpConn::LogDebug->Log (0, 0, "Refresh Request", "SAPIMsgID: %d",rfrshReqMsg.SAPIMsgID);

}

void MAGMsgFmt::parse_response(unsigned char* body)
{
	parse_response_body(body);
}

void MAGMsgFmt::parse_response_body(unsigned char* body)
{
	MsgHeader MsgHdr;
	memset(&MsgHdr,0,sizeof(MsgHdr));
	memcpy(&MsgHdr,body,18);
	UINT16 msgType = MsgHdr.MsgType;
	UINT16 msgLen =  MsgHdr.MsgLen;
	
	switch(msgType)
	{
	      case LOGON_ACCEPT_MESSAGE1:
		  case LOGON_ACCEPT_MESSAGE2:
			  get_logon_accept_response(body);
			break;
		  case LOGON_REJECT_MESSAGE:
			  get_logon_reject_message(body);
			  break;
		  case SESSION_TEST_REQUEST:
			  get_session_test_message(body);
			  break;
		  case HEART_BEAT_RESPONSE:
			  get_heart_beat_response(body);
			  break;
		  case SESSION_SEQ_UP_MESSAGE:
			  get_session_up_message(body);
			  break;
		  case  TRADING_SERVICE_DOWN_MESSAGE:
			  get_trading_service_down_message(body);
			  break;
		  case GATEWAY_SERVICE_DOWN_MESSAGE:
			  get_gateway_service_down_message(body);
			  break;
		  case THROTTLE_MSG:
			  get_throttle_message(body);
			  break;
		  case TRADING_ENGINE_REJECT_MESSAGE:
			  get_trading_reject_message(body);
			  break;
		  case SUBSCRIBE_RESP_MESSAGE1:
			  get_subscribe_resp_var1(body);
			  break;
		 case SUBSCRIBE_RESP_MESSAGE2:
			  get_subscribe_resp_var2(body);
			  break;
		case SUBSCRIBE_RESP_MESSAGE3:
			  get_subscribe_resp_var3(body);
			  break;
		case SYMBOL_TEST_RESP_MESSAGE:
			get_symbol_test_resp(body);
			break;
		case UNSUBSCRIBE_RESP_MESSAGE:
			get_unsubscribe_resp_message(body);
			break;
		case STOCK_INFO_STATUS_MESSAGE:
			get_stockinfo_status_message(body);
			break;
		case GATEWAY_REJECT_MESSAGE:
			get_gateway_reject_message(body);
			break;
		case STOCK_INFO_RESP_MESSAGE1:
			get_stockinfo_resp_var1(body);
			break;
		case STOCK_INFO_RESP_MESSAGE2:
			get_stockinfo_resp_var2(body);
			break;
		case STOCK_INFO_RESP_MESSAGE3:
			get_stockinfo_resp_var3(body);
			break;
		case STOCK_INFO_DELETE_MESSAGE:
			get_stockinfo_delete_message(body);
			break;
		case STOCK_INFO_UPDATE_MESSAGE1:
			get_stockinfo_upd_msgvar1(body);
			break;
		case STOCK_INFO_UPDATE_MESSAGE2:
			get_stockinfo_upd_msgvar2(body);
			break;
		case STOCK_INFO_UPDATE_MESSAGE3:
			get_stockinfo_upd_msgvar3(body);
			break;
		case BOOKSTATE_FULL_UPDATE_MESSAGE_SOLICITED:
		case BOOKSTATE_FULL_UPDATE_MESSAGE_UNSOLICITED:
			get_bookstate_fullupd_msg(body);
		default:
			break;
	}

}

MsgType MAGMsgFmt::get_msg_type(unsigned char* body)
{
	MsgHeader MsgHdr;
	memset(&MsgHdr,0,sizeof(MsgHdr));
	memcpy(&MsgHdr,body,18);
	return (MsgType)MsgHdr.MsgType;
}
void MAGMsgFmt::get_logon_accept_response(unsigned char* body)
{
	LogonRequestMsg AccpMsg;
	printf ("Accept Repsonse \n");
	memcpy(&AccpMsg,body,sizeof(AccpMsg));

}

void MAGMsgFmt::get_logon_reject_message(unsigned char* body)
{
	LogonRejectMsg RejMsg;
	printf ("Reject Repsonse \n");
	memcpy(&RejMsg,body,sizeof(RejMsg));

}

void MAGMsgFmt::get_session_test_message(unsigned char* body)
{
	SessionTestMsg SesTestMsg;
	memcpy(&SesTestMsg,body,sizeof(SesTestMsg));

}


void MAGMsgFmt::get_heart_beat_response(unsigned char* body)
{
	HeartBeatResp HeartBeatRespMsg;
	memcpy(&HeartBeatRespMsg,body,sizeof(HeartBeatRespMsg));

}

void MAGMsgFmt::get_session_up_message(unsigned char* body)
{
	SessionSeqUpMsg SesSeqUpMsg;
	memcpy(&SesSeqUpMsg,body,sizeof(SesSeqUpMsg));

}

void MAGMsgFmt::get_trading_service_down_message(unsigned char* body)
{
	TradingServiceDownMsg TradServDownMsg;
	memcpy(&TradServDownMsg,body,sizeof(TradServDownMsg));

}

void MAGMsgFmt::get_gateway_service_down_message(unsigned char* body)
{
	GatewayServiceDownMsg GatewayServDownMsg;
	memcpy(&GatewayServDownMsg,body,sizeof(GatewayServDownMsg));

}

void MAGMsgFmt::get_throttle_message(unsigned char* body)
{
	ThrottleMsg ThrotlMsg;
	memcpy(&ThrotlMsg,body,sizeof(ThrotlMsg));

}

void MAGMsgFmt::get_trading_reject_message(unsigned char* body)
{
	TradingEngRejectMsg TradEngRejMsg;
	memcpy(&TradEngRejMsg,body,sizeof(TradEngRejMsg));

}

void MAGMsgFmt::get_subscribe_resp_var1(unsigned char* body)
{
	SubscribeRespMsg1 SubsRspMsg;
	memcpy(&SubsRspMsg,body,sizeof(SubsRspMsg));

}

void MAGMsgFmt::get_subscribe_resp_var2(unsigned char* body)
{
	SubscribeRespMsg2 SubsRspMsg;
	memcpy(&SubsRspMsg,body,sizeof(SubsRspMsg));

}

void MAGMsgFmt::get_subscribe_resp_var3(unsigned char* body)
{
	SubscribeRespMsg3 SubsRspMsg;
	memcpy(&SubsRspMsg,body,sizeof(SubsRspMsg));

}

void MAGMsgFmt::get_symbol_test_resp(unsigned char* body)
{
	SymbolTestRespMsg SymTestRespMsg;
	memcpy(&SymTestRespMsg,body,sizeof(SymTestRespMsg));

}

void MAGMsgFmt::get_unsubscribe_resp_message(unsigned char* body)
{
	UnSubscribeRespMsg UnSubRespMsg;
	memcpy(&UnSubRespMsg,body,sizeof(UnSubRespMsg));

}

void MAGMsgFmt::get_stockinfo_status_message(unsigned char* body)
{
	StockInfoStatMsg StckInfStatMsg;
	memcpy(&StckInfStatMsg,body,sizeof(StckInfStatMsg));

}

void MAGMsgFmt::get_gateway_reject_message(unsigned char* body)
{
	GatewayRejectMsg GatewayRejMsg;
	memcpy(&GatewayRejMsg,body,sizeof(GatewayRejMsg));

}

void MAGMsgFmt::get_stockinfo_resp_var1(unsigned char* body)
{
	StockInfoRespMsg1 StckInfRespMsg;
	memcpy(&StckInfRespMsg,body,sizeof(StckInfRespMsg));

}

void MAGMsgFmt::get_stockinfo_resp_var2(unsigned char* body)
{
	StockInfoRespMsg2 StckInfRespMsg;
	memcpy(&StckInfRespMsg,body,sizeof(StckInfRespMsg));

}

void MAGMsgFmt::get_stockinfo_resp_var3(unsigned char* body)
{
	StockInfoRespMsg3 StckInfRespMsg;
	memcpy(&StckInfRespMsg,body,sizeof(StckInfRespMsg));

}

void MAGMsgFmt::get_stockinfo_delete_message(unsigned char* body)
{
	StockInfoDelMsg StckInfDelMsg;
	memcpy(&StckInfDelMsg,body,sizeof(StckInfDelMsg));

}

void MAGMsgFmt::get_stockinfo_upd_msgvar1(unsigned char* body)
{
	StockInfoUpdMsg1 StckInfUpdMsg;
	memcpy(&StckInfUpdMsg,body,sizeof(StckInfUpdMsg));

}

void MAGMsgFmt::get_stockinfo_upd_msgvar2(unsigned char* body)
{
	StockInfoUpdMsg2 StckInfUpdMsg;
	memcpy(&StckInfUpdMsg,body,sizeof(StckInfUpdMsg));

}

void MAGMsgFmt::get_stockinfo_upd_msgvar3(unsigned char* body)
{
	StockInfoUpdMsg3 StckInfUpdMsg;
	memcpy(&StckInfUpdMsg,body,sizeof(StckInfUpdMsg));

}

void MAGMsgFmt::get_bookstate_fullupd_msg(unsigned char* body)
{
	BookStateFullUpdMsg BkStUpdMsg;
	memcpy(&BkStUpdMsg,body,sizeof(BkStUpdMsg));
	UINT16 grpId = 0;
	UINT16 offset = 0;
	UINT16 location = sizeof(BkStUpdMsg);
	UINT16 Firstoffset = 0;
	AwayQuoteGroup awayQuoteGrp;
	MDInfoGroupQuote mdInfQuote;
	MDInfoGroupTrade mdInfTrade;
	
	MAGTcpConn::LogDebug->Log (0, 0, "BookState fullUpd Resp", "Parsing for Repeating Groups");
	
	memcpy( &Firstoffset,body+location+2,2);
	while(true)
	{
		MAGTcpConn::LogDebug->Log (0, 0, "Repeating group", "-----------------------------------------------------------");
		memcpy( &grpId,body+location,2);
		memcpy( &offset,body+location+2,2);
		location += 4;

		if(grpId == 0 || location == Firstoffset)
			break;

		if(grpId == STOCKSTATEFLAGSGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "STOCKSTATEFLAGSGROUP", "STOCKSTATEFLAGSGROUP offset in response: %d",offset);
			printf("IN STOCKSTATEFLAGSGROUP with offset %d\n",offset);
			StockStateFlag stkStateFlg;
			memset(&stkStateFlg,0,sizeof(stkStateFlg));
			memcpy(&stkStateFlg,body+offset,sizeof(stkStateFlg));
			MAGTcpConn::LogDebug->Log (0, 0, "STOCKSTATEFLAGSGROUP", "Flags: %d",stkStateFlg.StockStateFlags);
			printf("Flags: %d\n",stkStateFlg.StockStateFlags);
		}
		else if(grpId == SAPIFUNCTIONSSTATUSGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "SAPIFUNCTIONSSTATUSGROUP", "SAPIFUNCTIONSSTATUSGROUP offset in response: %d",offset);
			printf("IN SAPIFUNCTIONSSTATUSGROUP with offset %d\n",offset);
			SapiFuncStatusGrp SapiFncStGrp;
			memset(&SapiFncStGrp,0,sizeof(SapiFncStGrp));
			memcpy(&SapiFncStGrp,body+offset,sizeof(SapiFncStGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "SAPIFUNCTIONSSTATUSGROUP", "SQuoteStatus: %d",SapiFncStGrp.SQuoteStatus);
			MAGTcpConn::LogDebug->Log (0, 0, "SAPIFUNCTIONSSTATUSGROUP", "TFOpenOnATradeStatus: %d",SapiFncStGrp.TFOpenOnATradeStatus);
			MAGTcpConn::LogDebug->Log (0, 0, "SAPIFUNCTIONSSTATUSGROUP", "TFCloseOnATradeStatus: %d",SapiFncStGrp.TFCloseOnATradeStatus);
			MAGTcpConn::LogDebug->Log (0, 0, "SAPIFUNCTIONSSTATUSGROUP", "TFUnwindMktStatus: %d",SapiFncStGrp.TFUnwindMktStatus);


			printf("SQuoteStatus: %d || TFOpenOnATradeStatus: %d || TFCloseOnATradeStatus: %d || TFUnwindMktStatus: %d\n",SapiFncStGrp.SQuoteStatus,SapiFncStGrp.TFOpenOnATradeStatus,SapiFncStGrp.TFCloseOnATradeStatus,SapiFncStGrp.TFUnwindMktStatus);
		}

		else if(grpId == CLOSINGTIMEGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSINGTIMEGROUP", "CLOSINGTIMEGROUP offset in response: %d",offset);
			printf("IN CLOSINGTIMEGROUP with offset %d\n",offset);
			ClosingTimeGrp clsngTimeGrp;
			memset(&clsngTimeGrp,0,sizeof(clsngTimeGrp));
			memcpy(&clsngTimeGrp,body+offset,sizeof(clsngTimeGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSINGTIMEGROUP", "StockClosingTime: %d",clsngTimeGrp.StockClosingTime);
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSINGTIMEGROUP", "StockClosingTimeMS: %d",clsngTimeGrp.StockClosingTimeMS);
			
			printf("StockClosingTime: %d || StockClosingTimeMS: %d\n",clsngTimeGrp.StockClosingTime,clsngTimeGrp.StockClosingTimeMS);
		}

		else if(grpId == DMMPOSITIONGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "DMMPOSITIONGROUP", "DMMPOSITIONGROUP offset in response: %d",offset);
			printf("IN DMMPOSITIONGROUP with offset %d\n",offset);
			DMMPositionGrp DMMPosGrp;
			memset(&DMMPosGrp,0,sizeof(DMMPosGrp));
			memcpy(&DMMPosGrp,body+offset,sizeof(DMMPosGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "DMMPOSITIONGROUP", "DMMPosition: %d",DMMPosGrp.DMMPosition);
			
			printf("DMMPosition: %d\n",DMMPosGrp.DMMPosition);
		}

		else if(grpId == SOFTWAREINFOGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "SOFTWAREINFOGROUP", "SOFTWAREINFOGROUP offset in response: %d",offset);
			printf("IN SOFTWAREINFOGROUP with offset %d\n",offset);
			SoftwareInfoGrp SWInfoGrp;
			memset(&SWInfoGrp,0,sizeof(SWInfoGrp));
			memcpy(&SWInfoGrp,body+offset,sizeof(SWInfoGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "SOFTWAREINFOGROUP", "Software Version: %s",SWInfoGrp.SWVersion);
			
			printf("Software Version: %s\n",SWInfoGrp.SWVersion);
		}

		else if(grpId == LASTSALEGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "LASTSALEGROUP", "LASTSALEGROUP offset in response: %d",offset);
			printf("IN LASTSALEGROUP with offset %d\n",offset);
			LastSalesGroup LastSaleGrp;
			memset(&LastSaleGrp,0,sizeof(LastSaleGrp));
			memcpy(&LastSaleGrp,body+offset,sizeof(LastSaleGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "LASTSALEGROUP", "LastPrice: %d",LastSaleGrp.lastPrice);
			MAGTcpConn::LogDebug->Log (0, 0, "LASTSALEGROUP", "LastTick: %c",LastSaleGrp.LastTick);

			printf("LastPrice: %d || LastTick: %c\n",LastSaleGrp.lastPrice,LastSaleGrp.LastTick);
		}

		else if(grpId == BUYPRICEPOINTAGGLIMITGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "BUYPRICEPOINTAGGLIMITGROUP", "BUYPRICEPOINTAGGLIMITGROUP offset in response: %d",offset);
			printf("BUYPRICEPOINTAGGLIMITGROUP with offset %d\n",offset);
			PricePointAGGLimGrp PrcPtAGGLmtGrp;
			memset(&PrcPtAGGLmtGrp,0,sizeof(PrcPtAGGLmtGrp));
			memcpy(&PrcPtAGGLmtGrp,body+offset,sizeof(PrcPtAGGLmtGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "BUYPRICEPOINTAGGLIMITGROUP", "Price: %d",PrcPtAGGLmtGrp.Price);
			MAGTcpConn::LogDebug->Log (0, 0, "BUYPRICEPOINTAGGLIMITGROUP", "OpenBookAggregateQty: %d",PrcPtAGGLmtGrp.OpenBookAggregateQty);
			MAGTcpConn::LogDebug->Log (0, 0, "BUYPRICEPOINTAGGLIMITGROUP", "OpenBookAggregateCount: %d",PrcPtAGGLmtGrp.OpenBookAggregateCount);
			
			printf("Price: %d || OpenBookAggregateQty: %d || OpenBookAggregateCount: %d\n",PrcPtAGGLmtGrp.Price,PrcPtAGGLmtGrp.OpenBookAggregateQty,PrcPtAGGLmtGrp.OpenBookAggregateCount);
		}

		else if(grpId == SELLPRICEPOINTAGGLIMITGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "SELLPRICEPOINTAGGLIMITGROUP", "SELLPRICEPOINTAGGLIMITGROUP offset in response: %d",offset);
			printf("SELLPRICEPOINTAGGLIMITGROUP with offset %d\n",offset);
			PricePointAGGLimGrp PrcPtAGGLmtGrp;
			memset(&PrcPtAGGLmtGrp,0,sizeof(PrcPtAGGLmtGrp));
			memcpy(&PrcPtAGGLmtGrp,body+offset,sizeof(PrcPtAGGLmtGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "SELLPRICEPOINTAGGLIMITGROUP", "Price: %d",PrcPtAGGLmtGrp.Price);
			MAGTcpConn::LogDebug->Log (0, 0, "SELLPRICEPOINTAGGLIMITGROUP", "OpenBookAggregateQty: %d",PrcPtAGGLmtGrp.OpenBookAggregateQty);
			MAGTcpConn::LogDebug->Log (0, 0, "SELLPRICEPOINTAGGLIMITGROUP", "OpenBookAggregateCount: %d",PrcPtAGGLmtGrp.OpenBookAggregateCount);
			
			printf("Price: %d || OpenBookAggregateQty: %d || OpenBookAggregateCount: %d\n",PrcPtAGGLmtGrp.Price,PrcPtAGGLmtGrp.OpenBookAggregateQty,PrcPtAGGLmtGrp.OpenBookAggregateCount);
		}

		else if(grpId == SQUOTEBUYPRICEPOINTSGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTEBUYPRICEPOINTSGROUP", "SQUOTEBUYPRICEPOINTSGROUP offset in response: %d",offset);
			printf("SQUOTEBUYPRICEPOINTSGROUP with offset %d\n",offset);
			SQuotePricePtGrp SQuotePrcPtGrp;
			memset(&SQuotePrcPtGrp,0,sizeof(SQuotePrcPtGrp));
			memcpy(&SQuotePrcPtGrp,body+offset,sizeof(SQuotePrcPtGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTEBUYPRICEPOINTSGROUP", "Price: %d",SQuotePrcPtGrp.Price);
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTEBUYPRICEPOINTSGROUP", "CurrOpenQty: %d",SQuotePrcPtGrp.CurrOpenQty);
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTEBUYPRICEPOINTSGROUP", "ReplacedQty: %d",SQuotePrcPtGrp.ReplacedQty);
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTEBUYPRICEPOINTSGROUP", "ReservPublishQty: %d",SQuotePrcPtGrp.ReservPublishQty);
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTEBUYPRICEPOINTSGROUP", "SQuoteBookStateFlags: %d",SQuotePrcPtGrp.SQuoteBookStateFlags);


			printf("Price: %d || CurrOpenQty: %d || ReplacedQty: %d || ReservPublishQty: %d || SQuoteBookStateFlags: %d\n",SQuotePrcPtGrp.Price,SQuotePrcPtGrp.CurrOpenQty,SQuotePrcPtGrp.ReplacedQty,SQuotePrcPtGrp.ReservPublishQty,SQuotePrcPtGrp.SQuoteBookStateFlags);
		}

		else if(grpId == SQUOTESELLPRICEPOINTSGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTESELLPRICEPOINTSGROUP", "SQUOTESELLPRICEPOINTSGROUP offset in response: %d",offset);
			printf("SQUOTESELLPRICEPOINTSGROUP with offset %d\n",offset);
			SQuotePricePtGrp SQuotePrcPtGrp;
			memset(&SQuotePrcPtGrp,0,sizeof(SQuotePrcPtGrp));
			memcpy(&SQuotePrcPtGrp,body+offset,sizeof(SQuotePrcPtGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTESELLPRICEPOINTSGROUP", "Price: %d",SQuotePrcPtGrp.Price);
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTESELLPRICEPOINTSGROUP", "CurrOpenQty: %d",SQuotePrcPtGrp.CurrOpenQty);
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTESELLPRICEPOINTSGROUP", "ReplacedQty: %d",SQuotePrcPtGrp.ReplacedQty);
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTESELLPRICEPOINTSGROUP", "ReservPublishQty: %d",SQuotePrcPtGrp.ReservPublishQty);
			MAGTcpConn::LogDebug->Log (0, 0, "SQUOTESELLPRICEPOINTSGROUP", "SQuoteBookStateFlags: %d",SQuotePrcPtGrp.SQuoteBookStateFlags);


			printf("Price: %d || CurrOpenQty: %d || ReplacedQty: %d || ReservPublishQty: %d || SQuoteBookStateFlags: %d\n",SQuotePrcPtGrp.Price,SQuotePrcPtGrp.CurrOpenQty,SQuotePrcPtGrp.ReplacedQty,SQuotePrcPtGrp.ReservPublishQty,SQuotePrcPtGrp.SQuoteBookStateFlags);
		}

		else if(grpId == AWAYQUOTESGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "AWAYQUOTESGROUP", "AWAYQUOTESGROUP offset in response: %d",offset);
			printf("IN AWAYQUOTE with offset %d\n",offset);
			memset(&awayQuoteGrp,0,sizeof(awayQuoteGrp));
			memcpy(&awayQuoteGrp,body+offset,sizeof(awayQuoteGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "AWAYQUOTESGROUP", "Exchange: %c",awayQuoteGrp.Exchange);
			MAGTcpConn::LogDebug->Log (0, 0, "AWAYQUOTESGROUP", "QuoteCond: %c",awayQuoteGrp.QuoteCondition);
			MAGTcpConn::LogDebug->Log (0, 0, "AWAYQUOTESGROUP", "NonNYBestBidPrice: %d",awayQuoteGrp.NonNYBestBidPrice);
			MAGTcpConn::LogDebug->Log (0, 0, "AWAYQUOTESGROUP", "NonNYBestASKPrice: %d",awayQuoteGrp.NonNYBestAskPrice);
			printf("Exchange %c QuoteCond %c BestBidPrice %d\n",awayQuoteGrp.Exchange,awayQuoteGrp.QuoteCondition,awayQuoteGrp.NonNYBestBidPrice);
		}
		else if(grpId == MDINFOGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP", "MDINFOGROUP offset in response: %d",offset);
			printf("IN MDINFO with offset %d\n",offset);
			char MDdata;
			memcpy(&MDdata,body+offset,1);
			if(MDdata == 'Q')
			{
				MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP", "Quote type MarketData Available");
				memset(&mdInfQuote,0,sizeof(mdInfQuote));
			    memcpy(&mdInfQuote,body+offset,sizeof(mdInfQuote));
				//MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP Quote", "BidPrice: %d || AskPrice: %d || QuoteCondition: %c",mdInfQuote.BidPrice,mdInfQuote.AskPrice,mdInfQuote.QuoteCondition);
				MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP Quote", "BidPrice: %d",mdInfQuote.BidPrice);
				MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP Quote", "AskPrice: %d",mdInfQuote.AskPrice);
				MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP Quote", "QuoteCondition: %c",mdInfQuote.QuoteCondition);
				printf("Quote Cond %c BId PRice %d AskPrice %d\n",mdInfQuote.QuoteCondition,mdInfQuote.BidPrice,mdInfQuote.AskPrice);
			}
			else if(MDdata == 'T')
			{
				MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP", "Trade type MarketData Available");
				printf("IN MDINFO Trade with offset: %d\n",offset);
				memset(&mdInfTrade,0,sizeof(mdInfTrade));
			    memcpy(&mdInfTrade,body+offset,sizeof(mdInfTrade));
				//MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP Trade", "Last Tick: %c || Trade Price: %d  || TradeVol: %d",mdInfTrade.LastTick,mdInfTrade.TradePrice,mdInfTrade.TradeVol);
				MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP Trade", "Last Tick: %c",mdInfTrade.LastTick);
				MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP Trade", "Trade Price: %d",mdInfTrade.TradePrice);
				MAGTcpConn::LogDebug->Log (0, 0, "MDINFOGROUP Trade", "TradeVol: %d",mdInfTrade.TradeVol);
				printf("Last Tick %c Trade PRice %d TradeVol %d\n",mdInfTrade.LastTick,mdInfTrade.TradePrice,mdInfTrade.TradeVol);
			}
		}

		else if(grpId == LRPGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "LRPGROUP", "LRPGROUP offset in response: %d",offset);
			printf("LRPGROUP with offset %d\n",offset);
			LRPGroup LRPGrp;
			memset(&LRPGrp,0,sizeof(LRPGrp));
			memcpy(&LRPGrp,body+offset,sizeof(LRPGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "LRPGROUP", "HighLRP: %d",LRPGrp.HighLRP);
			MAGTcpConn::LogDebug->Log (0, 0, "LRPGROUP", "LowLRP: %d",LRPGrp.LowLRP);

			printf("HighLRP: %d || LowLRP: %d \n",LRPGrp.HighLRP,LRPGrp.LowLRP);
		}

		else if(grpId == ALGOCONFIRMATIONGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "ALGOCONFIRMATIONGROUP offset in response: %d",offset);
			printf("ALGOCONFIRMATIONGROUP with offset %d\n",offset);
			AlgoConfirmationGrp AlgoCnfmGrp;
			memset(&AlgoCnfmGrp,0,sizeof(AlgoCnfmGrp));
			memcpy(&AlgoCnfmGrp,body+offset,sizeof(AlgoCnfmGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "RefSAPIMsgId: %d",AlgoCnfmGrp.RefSAPIMsgId);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "RefSAPIMsg: %d",AlgoCnfmGrp.RefSAPIMsg);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "NothingDoneReasonCode: %d",AlgoCnfmGrp.NothingDoneReasonCode);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "ConfirmationFlags: %d",AlgoCnfmGrp.ConfirmationFlags);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "TFOpenOnATradeResponseCode: %d",AlgoCnfmGrp.TFOpenOnATradeResponseCode);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "TFUnwindMktResponseCode: %d",AlgoCnfmGrp.TFUnwindMktResponseCode);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "OrderQuantityShares: %d",AlgoCnfmGrp.OrderQuantityShares);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "InsertedQty: %d",AlgoCnfmGrp.InsertedQty);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "ReservPublishQty: %d",AlgoCnfmGrp.ReservPublishQty);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "ReplacedQty: %d",AlgoCnfmGrp.ReplacedQty);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "ShippedQuantityShares: %d",AlgoCnfmGrp.ShippedQuantityShares);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "NothingDoneQty: %d",AlgoCnfmGrp.NothingDoneQty);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "PRINQuantityShares: %d",AlgoCnfmGrp.PRINQuantityShares);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "InsertedPx: %d",AlgoCnfmGrp.InsertedPx);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "ExecutionPx: %d",AlgoCnfmGrp.ExecutionPx);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "DBKLinkNum: %d",AlgoCnfmGrp.DBKLinkNum);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGOCONFIRMATIONGROUP", "TFCloseOnATradeResponseCode: %d",AlgoCnfmGrp.TFCloseOnATradeResponseCode);


			printf("RefSAPIMsgId: %d || RefSAPIMsg: %d \n",AlgoCnfmGrp.RefSAPIMsgId,AlgoCnfmGrp.RefSAPIMsg);
		}

		else if(grpId == ALGODISPOSITIONREJECTGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "ALGODISPOSITIONREJECTGROUP", "ALGODISPOSITIONREJECTGROUP offset in response: %d",offset);
			printf("ALGODISPOSITIONREJECTGROUP with offset %d\n",offset);
			AlgoDisPosRejGrp AlgoDispsRejGp;
			memset(&AlgoDispsRejGp,0,sizeof(AlgoDispsRejGp));
			memcpy(&AlgoDispsRejGp,body+offset,sizeof(AlgoDispsRejGp));
			MAGTcpConn::LogDebug->Log (0, 0, "ALGODISPOSITIONREJECTGROUP", "RefSAPIMsgId: %d",AlgoDispsRejGp.RefSAPIMsgId);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGODISPOSITIONREJECTGROUP", "RefSAPIMsg: %d",AlgoDispsRejGp.RefSAPIMsg);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGODISPOSITIONREJECTGROUP", "DispositionFlags: %d",AlgoDispsRejGp.DispositionFlags);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGODISPOSITIONREJECTGROUP", "SAPIAlgoRejectCode: %d",AlgoDispsRejGp.SAPIAlgoRejectCode);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGODISPOSITIONREJECTGROUP", "PRINQuantityShares: %d",AlgoDispsRejGp.PRINQuantityShares);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGODISPOSITIONREJECTGROUP", "ReservPublishQty: %d",AlgoDispsRejGp.ReservPublishQty);
			MAGTcpConn::LogDebug->Log (0, 0, "ALGODISPOSITIONREJECTGROUP", "LimitPx: %d",AlgoDispsRejGp.LimitPx);


			printf("RefSAPIMsgId: %d || RefSAPIMsg: %d \n",AlgoDispsRejGp.RefSAPIMsgId,AlgoDispsRejGp.RefSAPIMsg);
		}

		else if(grpId == OPENONTRADEPRICEPOINTSGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "OPENONTRADEPRICEPOINTSGROUP", "OPENONTRADEPRICEPOINTSGROUP offset in response: %d",offset);
			printf("OPENONTRADEPRICEPOINTSGROUP with offset %d\n",offset);
			OpenOnTradePricePointGrp OpenOnTrdPrcPtGrp;
			memset(&OpenOnTrdPrcPtGrp,0,sizeof(OpenOnTrdPrcPtGrp));
			memcpy(&OpenOnTrdPrcPtGrp,body+offset,sizeof(OpenOnTrdPrcPtGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "OPENONTRADEPRICEPOINTSGROUP", "MktImbalanceType: %d",OpenOnTrdPrcPtGrp.MktImbalanceType);
			MAGTcpConn::LogDebug->Log (0, 0, "OPENONTRADEPRICEPOINTSGROUP", "NotPairedQtySide: %d",OpenOnTrdPrcPtGrp.NotPairedQtySide);
			MAGTcpConn::LogDebug->Log (0, 0, "OPENONTRADEPRICEPOINTSGROUP", "ImbalanceVol: %d",OpenOnTrdPrcPtGrp.ImbalanceVol);
			MAGTcpConn::LogDebug->Log (0, 0, "OPENONTRADEPRICEPOINTSGROUP", "LimitPx: %d",OpenOnTrdPrcPtGrp.LimitPx);
			MAGTcpConn::LogDebug->Log (0, 0, "OPENONTRADEPRICEPOINTSGROUP", "PairedQty: %d",OpenOnTrdPrcPtGrp.PairedQty);
			MAGTcpConn::LogDebug->Log (0, 0, "OPENONTRADEPRICEPOINTSGROUP", "NotPairedQty: %d",OpenOnTrdPrcPtGrp.NotPairedQty);
			

			printf("MktImbalanceType: %d || NotPairedQtySide: %d || ImbalanceVol: %d || LimitPx: %d ||  PairedQty: %d || NotPairedQty: %d \n",OpenOnTrdPrcPtGrp.MktImbalanceType,OpenOnTrdPrcPtGrp.NotPairedQtySide,OpenOnTrdPrcPtGrp.ImbalanceVol,OpenOnTrdPrcPtGrp.LimitPx,OpenOnTrdPrcPtGrp.PairedQty,OpenOnTrdPrcPtGrp.NotPairedQty);
		}

		else if(grpId == CLOSEONTRADEPRICEPOINTSGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSEONTRADEPRICEPOINTSGROUP", "CLOSEONTRADEPRICEPOINTSGROUP offset in response: %d",offset);
			printf("CLOSEONTRADEPRICEPOINTSGROUP with offset %d\n",offset);
			CloseOnTradePricePointGrp CloseOnTrdPrcPtGrp;
			memset(&CloseOnTrdPrcPtGrp,0,sizeof(CloseOnTrdPrcPtGrp));
			memcpy(&CloseOnTrdPrcPtGrp,body+offset,sizeof(CloseOnTrdPrcPtGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSEONTRADEPRICEPOINTSGROUP", "MktImbalanceType: %d",CloseOnTrdPrcPtGrp.MktImbalanceType);
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSEONTRADEPRICEPOINTSGROUP", "NotPairedQtySide: %d",CloseOnTrdPrcPtGrp.NotPairedQtySide);
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSEONTRADEPRICEPOINTSGROUP", "ImbalanceVol: %d",CloseOnTrdPrcPtGrp.ImbalanceVol);
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSEONTRADEPRICEPOINTSGROUP", "LimitPx: %d",CloseOnTrdPrcPtGrp.LimitPx);
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSEONTRADEPRICEPOINTSGROUP", "PairedQty: %d",CloseOnTrdPrcPtGrp.PairedQty);
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSEONTRADEPRICEPOINTSGROUP", "NotPairedQty: %d",CloseOnTrdPrcPtGrp.NotPairedQty);
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSEONTRADEPRICEPOINTSGROUP", "BuyMaxDMMAllocation: %d",CloseOnTrdPrcPtGrp.BuyMaxDMMAllocation);
			MAGTcpConn::LogDebug->Log (0, 0, "CLOSEONTRADEPRICEPOINTSGROUP", "SellMaxDMMAllocation: %d",CloseOnTrdPrcPtGrp.SellMaxDMMAllocation);

			printf("MktImbalanceType: %d || NotPairedQtySide: %d || ImbalanceVol: %d || LimitPx: %d ||  PairedQty: %d || NotPairedQty: %d \n",CloseOnTrdPrcPtGrp.MktImbalanceType,CloseOnTrdPrcPtGrp.NotPairedQtySide,CloseOnTrdPrcPtGrp.ImbalanceVol,CloseOnTrdPrcPtGrp.LimitPx,CloseOnTrdPrcPtGrp.PairedQty,CloseOnTrdPrcPtGrp.NotPairedQty);
		}

		else if(grpId == SSRGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "SSRGROUP", "SSRGROUP offset in response: %d",offset);
			printf("SSRGROUP with offset %d\n",offset);
			SSRGroup SSRGrp;
			memset(&SSRGrp,0,sizeof(SSRGrp));
			memcpy(&SSRGrp,body+offset,sizeof(SSRGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "SSRGROUP", "SSRFilingPrice: %d",SSRGrp.SSRFilingPrice);
			
			printf("SSRFilingPrice: %d\n",SSRGrp.SSRFilingPrice);
		}

		else if(grpId == PRICEBANDGRP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "PRICEBANDGRP", "PRICEBANDGRP offset in response: %d",offset);
			printf("PRICEBANDGRP with offset %d\n",offset);
			PriceBandGrp PriceBndGrp;
			memset(&PriceBndGrp,0,sizeof(PriceBndGrp));
			memcpy(&PriceBndGrp,body+offset,sizeof(PriceBndGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "PRICEBANDGRP", "UpperPriceBand: %d",PriceBndGrp.UpperPriceBand);
			MAGTcpConn::LogDebug->Log (0, 0, "PRICEBANDGRP", "LowerPriceBand: %d",PriceBndGrp.LowerPriceBand);

			printf("UpperPriceBand: %d || LowerPriceBand: %d\n",PriceBndGrp.UpperPriceBand,PriceBndGrp.LowerPriceBand);
		}

		else if(grpId == AGGSQUOTEBUYPRICEPOINTSGRP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "AGGSQUOTEBUYPRICEPOINTSGRP", "AGGSQUOTEBUYPRICEPOINTSGRP offset in response: %d",offset);
			printf("AGGSQUOTEBUYPRICEPOINTSGRP with offset %d\n",offset);
			AGGSQuotePricePtGrp AGGSQuotePrcPtGrp;
			memset(&AGGSQuotePrcPtGrp,0,sizeof(AGGSQuotePrcPtGrp));
			memcpy(&AGGSQuotePrcPtGrp,body+offset,sizeof(AGGSQuotePrcPtGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "AGGSQUOTEBUYPRICEPOINTSGRP", "Price: %d",AGGSQuotePrcPtGrp.Price);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGSQUOTEBUYPRICEPOINTSGRP", "CurrOpenQty: %d",AGGSQuotePrcPtGrp.CurrOpenQty);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGSQUOTEBUYPRICEPOINTSGRP", "ReservPublishQty: %d",AGGSQuotePrcPtGrp.ReservPublishQty);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGSQUOTEBUYPRICEPOINTSGRP", "SQuoteCount: %d",AGGSQuotePrcPtGrp.SQuoteCount);
			
			printf("Price: %d || CurrOpenQty: %d \n",AGGSQuotePrcPtGrp.Price,AGGSQuotePrcPtGrp.CurrOpenQty);
		}

		else if(grpId == AGGSQUOTESELLPRICEPOINTSGRP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "AGGSQUOTESELLPRICEPOINTSGRP", "AGGSQUOTESELLPRICEPOINTSGRP offset in response: %d",offset);
			printf("AGGSQUOTESELLPRICEPOINTSGRP with offset %d\n",offset);
			AGGSQuotePricePtGrp AGGSQuotePrcPtGrp;
			memset(&AGGSQuotePrcPtGrp,0,sizeof(AGGSQuotePrcPtGrp));
			memcpy(&AGGSQuotePrcPtGrp,body+offset,sizeof(AGGSQuotePrcPtGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "AGGSQUOTESELLPRICEPOINTSGRP", "Price: %d",AGGSQuotePrcPtGrp.Price);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGSQUOTESELLPRICEPOINTSGRP", "CurrOpenQty: %d",AGGSQuotePrcPtGrp.CurrOpenQty);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGSQUOTESELLPRICEPOINTSGRP", "ReservPublishQty: %d",AGGSQuotePrcPtGrp.ReservPublishQty);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGSQUOTESELLPRICEPOINTSGRP", "SQuoteCount: %d",AGGSQuotePrcPtGrp.SQuoteCount);
			
			printf("Price: %d || CurrOpenQty: %d \n",AGGSQuotePrcPtGrp.Price,AGGSQuotePrcPtGrp.CurrOpenQty);
		}

		else if(grpId == AGGCCSQUOTEBUYPRICEPOINTSGRP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "AGGCCSQUOTEBUYPRICEPOINTSGRP", "AGGCCSQUOTEBUYPRICEPOINTSGRP offset in response: %d",offset);
			printf("AGGCCSQUOTEBUYPRICEPOINTSGRP with offset %d\n",offset);
			AGGCCSQuotePricePtGrp AGGCCSQuotePrcPtGrp;
			memset(&AGGCCSQuotePrcPtGrp,0,sizeof(AGGCCSQuotePrcPtGrp));
			memcpy(&AGGCCSQuotePrcPtGrp,body+offset,sizeof(AGGCCSQuotePrcPtGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "AGGCCSQUOTEBUYPRICEPOINTSGRP", "Price: %d",AGGCCSQuotePrcPtGrp.Price);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGCCSQUOTEBUYPRICEPOINTSGRP", "CurrOpenQty: %d",AGGCCSQuotePrcPtGrp.CurrOpenQty);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGCCSQUOTEBUYPRICEPOINTSGRP", "ReservPublishQty: %d",AGGCCSQuotePrcPtGrp.ReservPublishQty);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGCCSQUOTEBUYPRICEPOINTSGRP", "SQuoteCount: %d",AGGCCSQuotePrcPtGrp.SQuoteCount);

			printf("Price: %d || CurrOpenQty: %d \n",AGGCCSQuotePrcPtGrp.Price,AGGCCSQuotePrcPtGrp.CurrOpenQty);
		}

		else if(grpId == AGGCCSQUOTESELLPRICEPOINTSGRP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "AGGCCSQUOTESELLPRICEPOINTSGRP", "AGGCCSQUOTESELLPRICEPOINTSGRP offset in response: %d",offset);
			printf("AGGCCSQUOTESELLPRICEPOINTSGRP with offset %d\n",offset);
			AGGCCSQuotePricePtGrp AGGCCSQuotePrcPtGrp;
			memset(&AGGCCSQuotePrcPtGrp,0,sizeof(AGGCCSQuotePrcPtGrp));
			memcpy(&AGGCCSQuotePrcPtGrp,body+offset,sizeof(AGGCCSQuotePrcPtGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "AGGCCSQUOTESELLPRICEPOINTSGRP", "Price: %d",AGGCCSQuotePrcPtGrp.Price);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGCCSQUOTESELLPRICEPOINTSGRP", "CurrOpenQty: %d",AGGCCSQuotePrcPtGrp.CurrOpenQty);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGCCSQUOTESELLPRICEPOINTSGRP", "ReservPublishQty: %d",AGGCCSQuotePrcPtGrp.ReservPublishQty);
			MAGTcpConn::LogDebug->Log (0, 0, "AGGCCSQUOTESELLPRICEPOINTSGRP", "SQuoteCount: %d",AGGCCSQuotePrcPtGrp.SQuoteCount);

			printf("Price: %d || CurrOpenQty: %d \n",AGGCCSQuotePrcPtGrp.Price,AGGCCSQuotePrcPtGrp.CurrOpenQty);
		}

		else if(grpId == MANUALTEMPLATEPARAMETERSGROUP)
		{
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "MANUALTEMPLATEPARAMETERSGROUP offset in response: %d",offset);
			printf("MANUALTEMPLATEPARAMETERSGROUP with offset %d\n",offset);
			ManualTempParamGrp ManualTmpParmGrp;
			memset(&ManualTmpParmGrp,0,sizeof(ManualTmpParmGrp));
			memcpy(&ManualTmpParmGrp,body+offset,sizeof(ManualTmpParmGrp));
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "PRIN1OpenCloseParam: %d",ManualTmpParmGrp.PRIN1OpenCloseParam);
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "PRIN1SmartGkeyParam: %d",ManualTmpParmGrp.PRIN1SmartGkeyParam);
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "PRIN1sQuoteParam: %d",ManualTmpParmGrp.PRIN1sQuoteParam);
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "PRIN2OpenCloseParam: %d",ManualTmpParmGrp.PRIN2OpenCloseParam);
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "PRIN2SmartGkeyParam: %d",ManualTmpParmGrp.PRIN2SmartGkeyParam);
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "PRIN2sQuoteParam: %d",ManualTmpParmGrp.PRIN2sQuoteParam);
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "CROWD1OpenCloseParam: %d",ManualTmpParmGrp.CROWD1OpenCloseParam);
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "CROWD1SmartGkeyParam: %d",ManualTmpParmGrp.CROWD1SmartGkeyParam);
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "CROWD2OpenCloseParam: %d",ManualTmpParmGrp.CROWD2OpenCloseParam);
			MAGTcpConn::LogDebug->Log (0, 0, "MANUALTEMPLATEPARAMETERSGROUP", "CROWD2SmartGkeyParam: %d",ManualTmpParmGrp.CROWD2SmartGkeyParam);
			
			printf("PRIN1OpenCloseParam: %d || PRIN2OpenCloseParam: %d \n",ManualTmpParmGrp.PRIN1OpenCloseParam,ManualTmpParmGrp.PRIN2OpenCloseParam);
		}
		
	}
}

MAGMsgFmt::~MAGMsgFmt(void)
{
}


}