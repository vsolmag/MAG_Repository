#include <windows.h> 

#pragma once
namespace MAGQuoteMTSrv
{

typedef struct _msgheader
{
	UINT16 MsgType;
	UINT16 MsgLen;
	UINT32 MsgSeqNo;
	UINT32 MsgSendTime;
	UINT32 MsgSendTimeUS;
	UINT16 SymbolID; 

	_msgheader(){}
} MsgHeader;

typedef struct _logonrequest
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32    LastMsgSeqNo;
	char      SenderCompID[12];
	UINT16    MessageVersionProfile[32];
	char	  CancelOnDisconnect;
	char      UnSolicatedAckSub;

	_logonrequest(){}
}LogonRequestMsg;

typedef struct _logonreject
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32    LastSeqSrvRcv;
	UINT32    LastSeqSrvSent;
	UINT16    RejectType;
	char	  RejectText[40];
	UINT16    filler2;

	_logonreject(){}
}LogonRejectMsg;

typedef struct _sessiontest
{
	MsgHeader Hdr;
	UINT16	  filler;
	_sessiontest(){}
}SessionTestMsg;

typedef struct _heartbeatresp
{
	MsgHeader Hdr;
	UINT16	  filler;
	_heartbeatresp(){}
}HeartBeatResp;

typedef struct _sessionseq
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  NextSeqMsgNum;
	_sessionseq(){}
}SessionSeqUpMsg;

typedef struct _throttlemsg
{
	MsgHeader Hdr;
	UINT8	  throttleAction;
	UINT8	  throttleType;
	UINT32	  refSAPIMsgID;
	_throttlemsg(){}
}ThrottleMsg;

typedef struct _symboltestreq
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  SAPIMsgID;
	_symboltestreq(){}
}SymbolTestReqMsg;

typedef struct _symboltestresp
{
	MsgHeader Hdr;
	UINT8	  SubscribeStatus;
	UINT8	  filler;
	UINT32	  refSAPIMsgID;
	_symboltestresp(){}
}SymbolTestRespMsg;

typedef struct _tradservicedown
{
	MsgHeader Hdr;
	UINT8	  ServiceDownCode;
	char	  filler;
	_tradservicedown(){}
}TradingServiceDownMsg;

typedef struct _gatewaydownmsg
{
	MsgHeader Hdr;
	UINT8	  ServiceDownCode;
	char	  filler;
	_gatewaydownmsg(){}
}GatewayServiceDownMsg;

typedef struct _subscribereqmsg
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  SAPIMsgID;
	_subscribereqmsg(){}
}SubscribeReqMsg;

typedef struct _unsubscribereqmsg
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  SAPIMsgID;
	_unsubscribereqmsg(){}
}UnSubscribeReqMsg;

typedef struct _subscriberespmsg1
{
	MsgHeader Hdr;
	UINT8	  SAPIAdmRespCode;
	UINT8	  SubscribeStatus;
	UINT32	  refSAPIMsgID;
	char	  StockInfoRecord[252];
	_subscriberespmsg1(){}
}SubscribeRespMsg1;

typedef struct _subscriberespmsg2
{
	MsgHeader Hdr;
	UINT8	  SAPIAdmRespCode;
	UINT8	  SubscribeStatus;
	UINT32	  refSAPIMsgID;
	char	  StockInfoRecord[272];
	_subscriberespmsg2(){}
}SubscribeRespMsg2;

typedef struct _subscriberespmsg3
{
	MsgHeader Hdr;
	UINT8	  SAPIAdmRespCode;
	UINT8	  SubscribeStatus;
	UINT32	  refSAPIMsgID;
	char	  StockInfoRecord[276];
	_subscriberespmsg3(){}
}SubscribeRespMsg3;

typedef struct _unsubscriberespmsg
{
	MsgHeader Hdr;
	UINT8	  SAPIAdmRespCode;
	UINT8	  SubscribeStatus;
	UINT32	  refSAPIMsgID;
	_unsubscriberespmsg(){}
}UnSubscribeRespMsg;

typedef struct _gatewayrejectmsg
{
	MsgHeader Hdr;
	UINT8	  refSAPIMsg;
	UINT8	  DMMRejectCode;
	UINT32	  refSAPIMsgID;
	UINT16    refRepeatingGrpInst;
	UINT16	  refErrorTag;
	_gatewayrejectmsg(){}
}GatewayRejectMsg;

typedef struct _tradingrejectmsg
{
	MsgHeader Hdr;
	UINT8	  refSAPIMsg;
	UINT8	  filler;
	UINT32	  refSAPIMsgID;
	UINT16    refRepeatingGrpInst;
	UINT16	  refErrorTag;
	_tradingrejectmsg(){}
}TradingEngRejectMsg;

typedef struct _stockinforecordvar1
{
	UINT64    CurrShareOutstanding;
	UINT32	  DirectPlusMaxQtyShares;
	UINT32	  DMMBillingNum;
	UINT32	  DMMClearingFirmID;
	UINT32	  SAPIThrottleRate;
	UINT32	  MOCTime;
	UINT32	  OpenOnTradeMaxQty;
	UINT32	  MaxOrderQty;
	UINT16    PostID;
	UINT16    DMMUnitID;
	UINT16    StockNo;
	UINT16    AltDBKDev;
	UINT16    AltPost;
	UINT16    DBKDev;
	UINT8     PriceDenominationCode;
	char	  RoundLotCode;
	char      UOTCode;
	char      SP_Group;
	char      ShortCorpName[32];
	char      PrevClosingPrice[18];
	char      AvgVolShares[12];
	char      StockSymbol[11];
	char      MPVDecimal[10];
	char      DepthGuidePriceGrp1[10];
	char      LRPValue[10];
	char      NYSEOpenTime[8];
	char      OpenOnTradePriceRange[8];
	char      DepthGuideTradeDate[7];
	char      DepthGuidePriceGrp1Depth10[6];
	char      DepthGuidePriceGrp1Depth25[6];
	char      DepthGuidePriceGrp1Depth3[6];
	char      DepthGuidePriceGrp1Depth5[6];
	char      NewStockSymbol[5];
	char      NewStockSuffix[5];
	char      DMMSymbol[4];
	char      DMMUnitMnemonic[4];
	char      RegionCode[3];
	char      ISOCountryCode[3];
	char      Panel[2];
	char      ProductType[2];
	char      BankRuptFlag;
	char      ZeroDisplayFlag;
	char      DelayHaltResumeCode;
	char      DJ_StockInd;
	char      HaltReasonCode;
	char      HighPxInd;
	char      InhibitOrdersInd;
	char      PossDupFlag;
	char      PrimaryMkt;
	char      PurgeStockInd;
	char      SAPIServiceEligibilityFlag;
	char      BookStateEligibilityFlag;
	char      PrinRptsEligibiltyFlag;
	char      SettlementInstValidation;
	char      SpecialHaltFlag;
	char      TeeID;
	char      HybridHighPriceFlag;
	char      SetSecuritySlowFlag;
	char      VolumeGroup;
	char	  DMMGWId;
	char      RouteToNewBookFlag;
	UINT8	  filler;
	_stockinforecordvar1(){}
}StockInfoRecVar1;

typedef struct _stockinforecordvar2
{
	UINT64    CurrShareOutstanding;
	UINT32	  DirectPlusMaxQtyShares;
	UINT32	  DMMBillingNum;
	UINT32	  DMMClearingFirmID;
	UINT32	  SAPIThrottleRate;
	UINT32	  MOCTime;
	UINT32	  OpenOnTradeMaxQty;
	UINT32	  MaxOrderQty;
	UINT16    PostID;
	UINT16    DMMUnitID;
	UINT16    StockNo;
	UINT16    AltDBKDev;
	UINT16    AltPost;
	UINT16    DBKDev;
	UINT8     PriceDenominationCode;
	char	  RoundLotCode;
	char      UOTCode;
	char      SP_Group;
	char      ShortCorpName[32];
	char      PrevClosingPrice[18];
	char      AvgVolShares[12];
	char      StockSymbol[11];
	char      MPVDecimal[10];
	char      DepthGuidePriceGrp1[10];
	char      LRPValue[10];
	char      NYSEOpenTime[8];
	char      OpenOnTradePriceRange[8];
	char      DepthGuideTradeDate[7];
	char      DepthGuidePriceGrp1Depth10[6];
	char      DepthGuidePriceGrp1Depth25[6];
	char      DepthGuidePriceGrp1Depth3[6];
	char      DepthGuidePriceGrp1Depth5[6];
	char      NewStockSymbol[5];
	char      NewStockSuffix[5];
	char      DMMSymbol[4];
	char      DMMUnitMnemonic[4];
	char      RegionCode[3];
	char      ISOCountryCode[3];
	char      Panel[2];
	char      ProductType[2];
	char      BankRuptFlag;
	char      ZeroDisplayFlag;
	char      DelayHaltResumeCode;
	char      DJ_StockInd;
	char      HaltReasonCode;
	char      HighPxInd;
	char      InhibitOrdersInd;
	char      PossDupFlag;
	char      PrimaryMkt;
	char      PurgeStockInd;
	char      SAPIServiceEligibilityFlag;
	char      BookStateEligibilityFlag;
	char      PrinRptsEligibiltyFlag;
	char      SettlementInstValidation;
	char      SpecialHaltFlag;
	char      TeeID;
	char      HybridHighPriceFlag;
	char      SetSecuritySlowFlag;
	char      VolumeGroup;
	char	  DMMGWId;
	char      RouteToNewBookFlag;
	char      PriceImprovementParameter[7];
	char      RekeyPrice[7];
	char      DisplayUnit[2];
	char      StockClass;
	char      TapeModeFlag;
	UINT8     filler[3];
	_stockinforecordvar2(){}
}StockInfoRecVar2;

typedef struct _stockinforecordvar3
{
	UINT64    CurrShareOutstanding;
	UINT32	  DirectPlusMaxQtyShares;
	UINT32	  DMMBillingNum;
	UINT32	  DMMClearingFirmID;
	UINT32	  SAPIThrottleRate;
	UINT32	  MOCTime;
	UINT32	  OpenOnTradeMaxQty;
	UINT32	  MaxOrderQty;
	UINT32    CloseOnTradeMaxQty;
	UINT16    PostID;
	UINT16    DMMUnitID;
	UINT16    StockNo;
	UINT16    AltDBKDev;
	UINT16    AltPost;
	UINT16    DBKDev;
	UINT8     PriceDominationCode;
	char	  RoundLotCode;
	char      UOTCode;
	char      SP_Group;
	char      ShortCorpName[32];
	char      PrevClosingPrice[18];
	char      AvgVolShares[12];
	char      StockSymbol[11];
	char      MPVDecimal[10];
	char      DepthGuidePriceGrp1[10];
	char      LRPValue[10];
	char      NYSEOpenTime[8];
	char      OpenOnTradePriceRange[8];
	char      DepthGuideTradeDate[7];
	char      DepthGuidePriceGrp1Depth10[6];
	char      DepthGuidePriceGrp1Depth25[6];
	char      DepthGuidePriceGrp1Depth3[6];
	char      DepthGuidePriceGrp1Depth5[6];
	char      NewStockSymbol[5];
	char      NewStockSuffix[5];
	char      DMMSymbol[4];
	char      DMMUnitMnemonic[4];
	char      RegionCode[3];
	char      ISOCountryCode[3];
	char      Panel[2];
	char      ProductType[2];
	char      BankRuptFlag;
	char      ZeroDisplayFlag;
	char      DelayHaltResumeCode;
	char      DJ_StockInd;
	char      HaltReasonCode;
	char      HighPxInd;
	char      InhibitOrdersInd;
	char      PossDupFlag;
	char      PrimaryMkt;
	char      PurgeStockInd;
	char      SAPIServiceEligibilityFlag;
	char      BookStateEligibilityFlag;
	char      PrinRptsEligibiltyFlag;
	char      SettlementInstValidation;
	char      SpecialHaltFlag;
	char      TeeID;
	char      HybridHighPriceFlag;
	char      SetSecuritySlowFlag;
	char      VolumeGroup;
	char	  DMMGWId;
	char      RouteToNewBookFlag;
	char      PriceImprovementParameter[7];
	char      RekeyPrice[7];
	char      DisplayUnit[2];
	char      StockClass;
	char      TapeModeFlag;
	UINT8     filler[3];
	_stockinforecordvar3(){}
}StockInfoRecVar3;


typedef struct _stockinforeqmsg
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  SAPIMsgID;
	UINT16    DBKDevice;
	UINT16	  PostID;
	char	  TeeID;
	char      StockSymbol[11];
	_stockinforeqmsg(){}
}StockInfoReqMsg;

typedef struct _stockinforespmsg1
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  RefSAPIMsgID;
	StockInfoRecVar1 StockInfoRecord;

	_stockinforespmsg1(){}
}StockInfoRespMsg1;

typedef struct _stockinforespmsg2
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  RefSAPIMsgID;
	StockInfoRecVar2 StockInfoRecord;

	_stockinforespmsg2(){}
}StockInfoRespMsg2;

typedef struct _stockinforespmsg3
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  RefSAPIMsgID;
	StockInfoRecVar3 StockInfoRecord;

	_stockinforespmsg3(){}
}StockInfoRespMsg3;

typedef struct _stockinfoupdatemsg1
{
	MsgHeader Hdr;
	UINT16	  filler1;
	UINT16	  filler2;
	UINT16	  filler3;
	StockInfoRecVar1 StockInfoRecord;
	_stockinfoupdatemsg1(){}
}StockInfoUpdMsg1;

typedef struct _stockinfoupdatemsg2
{
	MsgHeader Hdr;
	UINT16	  filler1;
	UINT16	  filler2;
	UINT16	  filler3;
	StockInfoRecVar2 StockInfoRecord;
	_stockinfoupdatemsg2(){}
}StockInfoUpdMsg2;

typedef struct _stockinfoupdatemsg3
{
	MsgHeader Hdr;
	UINT16	  filler1;
	UINT16	  filler2;
	UINT16	  filler3;
	StockInfoRecVar3 StockInfoRecord;
	_stockinfoupdatemsg3(){}
}StockInfoUpdMsg3;

typedef struct _stockinfodeletemsg
{
	MsgHeader Hdr;
	UINT16	  filler;
	char      StockSymbol[11];
	UINT8	  filler2;
	_stockinfodeletemsg(){}
}StockInfoDelMsg;


typedef struct _stockinfostatmsg
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32    RefSAPIMsgID;
	UINT32	  TotalMsgCount;
	_stockinfostatmsg(){}
}StockInfoStatMsg;


typedef enum
{
	LOGON_REQUEST_MESSAGE = 0x0021,
	LOGON_ACCEPT_MESSAGE1 = 0x0022,
	LOGON_ACCEPT_MESSAGE2 = 0x0023,
	LOGON_REJECT_MESSAGE = 0x0141,
	SESSION_TEST_REQUEST = 0x0011,
	HEART_BEAT_RESPONSE = 0x0001,
	SESSION_SEQ_UP_MESSAGE = 0x0151,
	THROTTLE_MSG = 0x0421,
	SYMBOL_TEST_REQ_MESSAGE = 0x0221,
	SYMBOL_TEST_RESP_MESSAGE = 0x0321,
	TRADING_SERVICE_DOWN_MESSAGE = 0x0401,
	GATEWAY_SERVICE_DOWN_MESSAGE = 0x0411,
	SUBSCRIBE_REQ_MESSAGE = 0x0201,
	UNSUBSCRIBE_REQ_MESSAGE = 0x0211,
	SUBSCRIBE_RESP_MESSAGE1 = 0x0301,
	SUBSCRIBE_RESP_MESSAGE2 = 0x0302,
	SUBSCRIBE_RESP_MESSAGE3 = 0x0303,
	UNSUBSCRIBE_RESP_MESSAGE = 0x0311,
	GATEWAY_REJECT_MESSAGE = 0x03D1,
	TRADING_ENGINE_REJECT_MESSAGE = 0x03C1,
	STOCK_INFO_REQ_MESSAGE = 0x0231,
	STOCK_INFO_RESP_MESSAGE1 = 0x0331,
	STOCK_INFO_RESP_MESSAGE2 = 0x0332,
	STOCK_INFO_RESP_MESSAGE3 = 0x0333,
	STOCK_INFO_UPDATE_MESSAGE1 = 0x0351,
	STOCK_INFO_UPDATE_MESSAGE2 = 0x0352,
	STOCK_INFO_UPDATE_MESSAGE3 = 0x0353,
	STOCK_INFO_DELETE_MESSAGE = 0x0341,
	STOCK_INFO_STATUS_MESSAGE = 0x0431
} MsgType;

class MAGMsgFmt
{
public:
	MAGMsgFmt(void);
	~MAGMsgFmt(void);
	
	void Format_logon_request_message(unsigned char *);
	void Format_session_test_message(unsigned char* body);
	void Format_heartbeat_resp_message(unsigned char* body);
	void Format_session_sequp_message(unsigned char* body);
	void Format_subscribe_req_message(unsigned char* body);
	void Format_symbol_test_req_message(unsigned char* body);
	void Format_unsubscribe_req_message(unsigned char* body);
	void Format_stockinfo_req_message(unsigned char* body);

	void parse_response(unsigned char* body);

private:
	MsgHeader msgHeaderInfo;
	unsigned char MsgBody[512];

	MsgHeader make_header(MsgType type);
	void make_logon_request_body(unsigned char *);
	void make_session_test_body(unsigned char *);
	void make_heartbeat_resp_body(unsigned char *);
	void make_session_sequp_body(unsigned char *);
	void make_subscribe_req_body(unsigned char *);
	void make_symbol_test_req_body(unsigned char *);
	void make_unsubscribe_req_body(unsigned char *);
	void make_stockinfo_req_body(unsigned char *);
	
	void parse_response_body(unsigned char* body);
	
	void get_logon_accept_response(unsigned char* body);
	void get_logon_reject_message(unsigned char* body);
	void get_session_test_message(unsigned char* body);
	void get_heart_beat_response(unsigned char* body);
	void get_session_up_message(unsigned char* body);

	void get_trading_service_down_message(unsigned char* body);
	void get_gateway_service_down_message(unsigned char* body);
	void get_throttle_message(unsigned char* body);
	void get_trading_reject_message(unsigned char* body);
	void get_subscribe_resp_var1(unsigned char* body);
	void get_subscribe_resp_var2(unsigned char* body);
	void get_subscribe_resp_var3(unsigned char* body);
	void get_symbol_test_resp(unsigned char* body);
	void get_unsubscribe_resp_message(unsigned char* body);
	void get_stockinfo_status_message(unsigned char* body);
	void get_gateway_reject_message(unsigned char* body);
	void get_stockinfo_resp_var1(unsigned char* body);
	void get_stockinfo_resp_var2(unsigned char* body);
	void get_stockinfo_resp_var3(unsigned char* body);
	void get_stockinfo_delete_message(unsigned char* body);
	void get_stockinfo_upd_msgvar1(unsigned char* body);
	void get_stockinfo_upd_msgvar2(unsigned char* body);
	void get_stockinfo_upd_msgvar3(unsigned char* body);

};

}