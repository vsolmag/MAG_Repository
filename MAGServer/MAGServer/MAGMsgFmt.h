#include <windows.h> 

#pragma once
namespace MAGQuoteMTSrv
{
#pragma pack(push, 1)
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
#pragma pack(pop) 
#pragma pack(push, 1)
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
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _sessiontest
{
	MsgHeader Hdr;
	UINT16	  filler;
	_sessiontest(){}
}SessionTestMsg;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _heartbeatresp
{
	MsgHeader Hdr;
	UINT16	  filler;
	_heartbeatresp(){}
}HeartBeatResp;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _sessionseq
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  NextSeqMsgNum;
	_sessionseq(){}
}SessionSeqUpMsg;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _throttlemsg
{
	MsgHeader Hdr;
	UINT8	  throttleAction;
	UINT8	  throttleType;
	UINT32	  refSAPIMsgID;
	_throttlemsg(){}
}ThrottleMsg;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _symboltestreq
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  SAPIMsgID;
	_symboltestreq(){}
}SymbolTestReqMsg;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _symboltestresp
{
	MsgHeader Hdr;
	UINT8	  SubscribeStatus;
	UINT8	  filler;
	UINT32	  refSAPIMsgID;
	_symboltestresp(){}
}SymbolTestRespMsg;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _tradservicedown
{
	MsgHeader Hdr;
	UINT8	  ServiceDownCode;
	char	  filler;
	_tradservicedown(){}
}TradingServiceDownMsg;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct _gatewaydownmsg
{
	MsgHeader Hdr;
	UINT8	  ServiceDownCode;
	char	  filler;
	_gatewaydownmsg(){}
}GatewayServiceDownMsg;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _subscribereqmsg
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  SAPIMsgID;
	_subscribereqmsg(){}
}SubscribeReqMsg;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _unsubscribereqmsg
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  SAPIMsgID;
	_unsubscribereqmsg(){}
}UnSubscribeReqMsg;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _unsubscriberespmsg
{
	MsgHeader Hdr;
	UINT8	  SAPIAdmRespCode;
	UINT8	  SubscribeStatus;
	UINT32	  refSAPIMsgID;
	_unsubscriberespmsg(){}
}UnSubscribeRespMsg;
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct _subscriberespmsg1
{
	MsgHeader Hdr;
	UINT8	  SAPIAdmRespCode;
	UINT8	  SubscribeStatus;
	UINT32	  refSAPIMsgID;
	StockInfoRecVar1	StockInfoRecord;
	_subscriberespmsg1(){}
}SubscribeRespMsg1;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _subscriberespmsg2
{
	MsgHeader Hdr;
	UINT8	  SAPIAdmRespCode;
	UINT8	  SubscribeStatus;
	UINT32	  refSAPIMsgID;
	StockInfoRecVar2	  StockInfoRecord;
	_subscriberespmsg2(){}
}SubscribeRespMsg2;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _subscriberespmsg3
{
	MsgHeader Hdr;
	UINT8	  SAPIAdmRespCode;
	UINT8	  SubscribeStatus;
	UINT32	  refSAPIMsgID;
	StockInfoRecVar3	  StockInfoRecord;
	_subscriberespmsg3(){}
}SubscribeRespMsg3;
#pragma pack(pop)

#pragma pack(push, 1)
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
#pragma pack(pop) 

#pragma pack(push, 1)
typedef struct _stockinforespmsg1
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  RefSAPIMsgID;
	StockInfoRecVar1 StockInfoRecord;

	_stockinforespmsg1(){}
}StockInfoRespMsg1;
#pragma pack(pop) 

#pragma pack(push, 1)
typedef struct _stockinforespmsg2
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  RefSAPIMsgID;
	StockInfoRecVar2 StockInfoRecord;

	_stockinforespmsg2(){}
}StockInfoRespMsg2;
#pragma pack(pop) 

#pragma pack(push, 1)
typedef struct _stockinforespmsg3
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32	  RefSAPIMsgID;
	StockInfoRecVar3 StockInfoRecord;

	_stockinforespmsg3(){}
}StockInfoRespMsg3;
#pragma pack(pop) 

#pragma pack(push, 1)
typedef struct _stockinfoupdatemsg1
{
	MsgHeader Hdr;
	UINT16	  filler1;
	UINT16	  filler2;
	UINT16	  filler3;
	StockInfoRecVar1 StockInfoRecord;
	_stockinfoupdatemsg1(){}
}StockInfoUpdMsg1;
#pragma pack(pop) 

#pragma pack(push, 1)
typedef struct _stockinfoupdatemsg2
{
	MsgHeader Hdr;
	UINT16	  filler1;
	UINT16	  filler2;
	UINT16	  filler3;
	StockInfoRecVar2 StockInfoRecord;
	_stockinfoupdatemsg2(){}
}StockInfoUpdMsg2;
#pragma pack(pop) 

#pragma pack(push, 1)
typedef struct _stockinfoupdatemsg3
{
	MsgHeader Hdr;
	UINT16	  filler1;
	UINT16	  filler2;
	UINT16	  filler3;
	StockInfoRecVar3 StockInfoRecord;
	_stockinfoupdatemsg3(){}
}StockInfoUpdMsg3;
#pragma pack(pop) 

#pragma pack(push, 1)
typedef struct _stockinfodeletemsg
{
	MsgHeader Hdr;
	UINT16	  filler;
	char      StockSymbol[11];
	UINT8	  filler2;
	_stockinfodeletemsg(){}
}StockInfoDelMsg;
#pragma pack(pop) 

#pragma pack(push, 1)
typedef struct _stockinfostatmsg
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32    RefSAPIMsgID;
	UINT32	  TotalMsgCount;
	_stockinfostatmsg(){}
}StockInfoStatMsg;
#pragma pack(pop) 


#pragma pack(push, 1)
typedef struct _refreshreqmsg
{
	MsgHeader Hdr;
	UINT16	  filler;
	UINT32    SAPIMsgID;
	_refreshreqmsg(){}
}RefreshReqMsg;
#pragma pack(pop) 

#pragma pack(push, 1)
typedef struct _bookstatefullupdmsg
{
	MsgHeader Hdr;
	UINT16	  FullUpdSeqNum;
	UINT16	  ProtocolVersion;
	UINT16	  ProtocolRevision;
	char	  StockSymbol[12];
	UINT16	  PacketNum;
	UINT16	  PacketTotal;
	UINT32    RefSAPIMsgID;
	_bookstatefullupdmsg(){}
}BookStateFullUpdMsg;
#pragma pack(pop)


/**************** Repeating Groups *******************************/
#pragma pack(push, 1)
typedef struct _stockstateflag
{
	UINT32 StockStateFlags;
	_stockstateflag(){}
}StockStateFlag;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _sapifncstatusgrp
{
	UINT8	SQuoteStatus;
	UINT8	TFOpenOnATradeStatus;
	UINT8	TFUnwindMktStatus;
	UINT8	TFCloseOnATradeStatus;
	_sapifncstatusgrp(){}
}SapiFuncStatusGrp;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _closingtmgrp
{
	UINT32	StockClosingTime;
	UINT32	StockClosingTimeMS;
	_closingtmgrp(){}
}ClosingTimeGrp;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _dmmposgrp
{
	UINT32	DMMPosition;
	_dmmposgrp(){}
}DMMPositionGrp;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _swinfogrp
{
	char SWVersion[28];
	_swinfogrp(){}
}SoftwareInfoGrp;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _lastsalesgroup
{
	UINT32	lastPrice;
	char	LastTick;
	char	Filler[3];
	_lastsalesgroup(){}
}LastSalesGroup;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _priceptagglimgrp
{
	UINT32	Price;
	UINT32	OpenBookAggregateQty;
	UINT32	OpenBookAggregateCount;
	_priceptagglimgrp(){}
}PricePointAGGLimGrp;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _squotepriceptgrp
{
	UINT32	Price;
	UINT32	CurrOpenQty;
	UINT32	ReservPublishQty;
	UINT32	ReplacedQty;
	UINT32	SQuoteBookStateFlags;
	_squotepriceptgrp(){}
}SQuotePricePtGrp;
#pragma pack(pop)



#pragma pack(push, 1)
typedef struct _awayquotegroup
{
	char    Exchange;
	char    QuoteCondition;
	UINT16  AwayQuoteFlags;
	UINT32  SourceTime;
	UINT32  SourceTimeMs;
	UINT32  NonNYBestBidPrice;
	UINT32  NonNYBestBidSize;
	UINT32  NonNYBestAskPrice;
	UINT32  NonNYBestAskSize;
	_awayquotegroup(){}
}AwayQuoteGroup;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _mdinfogroupquote
{
	char    MarketDataAvailable;
	char    QuoteCondition;
	char    Filler[2];
	UINT32  BidPrice;
	UINT32  BidSize;
	UINT32  AskPrice;
	UINT32  AskSize;
	_mdinfogroupquote(){}
}MDInfoGroupQuote;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _mdinfogrouptrade
{
	char    MarketDataAvailable;
	char    LastTick;
	char    Filler[2];
	UINT32  TradePrice;
	UINT32  TradeVol;
	_mdinfogrouptrade(){}
}MDInfoGroupTrade;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _lrpgrp
{
	UINT32  LowLRP;
	UINT32  HighLRP;
	_lrpgrp(){}
}LRPGroup;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _algocnfgrp
{
	UINT32  RefSAPIMsgId;
	UINT8	RefSAPIMsg;
	UINT8	Filler;
	UINT16	NothingDoneReasonCode;
	UINT16	ConfirmationFlags;
	UINT8	TFOpenOnATradeResponseCode;
	UINT8	TFUnwindMktResponseCode;
	UINT32	OrderQuantityShares;
	UINT32	InsertedQty;
	UINT32	ReservPublishQty;
	UINT32	ReplacedQty;
	UINT32	ShippedQuantityShares;
	UINT32	NothingDoneQty;
	UINT32	PRINQuantityShares;
	UINT32	InsertedPx;
	UINT32	ExecutionPx;
	UINT32	DBKLinkNum;
	UINT8	TFCloseOnATradeResponseCode;
	char	Filler2[3];
	_algocnfgrp(){}
}AlgoConfirmationGrp;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _algodisposrejgrp
{
	UINT32	RefSAPIMsgId;
	UINT8	RefSAPIMsg;
	UINT8	Filler;
	UINT16	DispositionFlags;
	UINT16	SAPIAlgoRejectCode;
	UINT16	Filler2;
	UINT32	PRINQuantityShares;
	UINT32	ReservPublishQty;
	UINT32	LimitPx;
	_algodisposrejgrp(){}
}AlgoDisPosRejGrp;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _openontrdpriceptgrp
{
	UINT8	MktImbalanceType;
	UINT8	NotPairedQtySide;
	char	Filler[2];
	UINT32	ImbalanceVol;
	UINT32	LimitPx;
	UINT32	PairedQty;
	UINT32	NotPairedQty;
	_openontrdpriceptgrp(){}
}OpenOnTradePricePointGrp;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct _closeontrdpriceptgrp
{
	UINT8	MktImbalanceType;
	UINT8	NotPairedQtySide;
	char	Filler[2];
	UINT32	ImbalanceVol;
	UINT32	LimitPx;
	UINT32	PairedQty;
	UINT32	NotPairedQty;
	UINT32	BuyMaxDMMAllocation;
	UINT32	SellMaxDMMAllocation;
	_closeontrdpriceptgrp(){}
}CloseOnTradePricePointGrp;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct _ssrgrp
{
	UINT32  SSRFilingPrice;
	_ssrgrp(){}
}SSRGroup;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct _pricebandgrp
{
	UINT32  LowerPriceBand;
	UINT32  UpperPriceBand;
	_pricebandgrp(){}
}PriceBandGrp;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct _aggsquoteprcptgrp
{
	UINT32  Price;
	UINT32  CurrOpenQty;
	UINT32	ReservPublishQty;
	UINT32	SQuoteCount;
	_aggsquoteprcptgrp(){}
}AGGSQuotePricePtGrp;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct _aggccsquoteprcptgrp
{
	UINT32  Price;
	UINT32  CurrOpenQty;
	UINT32	ReservPublishQty;
	UINT32	SQuoteCount;
	_aggccsquoteprcptgrp(){}
}AGGCCSQuotePricePtGrp;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct _manualtmpparamsgrp
{
	UINT32  PRIN1OpenCloseParam;
	UINT32  PRIN1SmartGkeyParam;
	UINT32	PRIN1sQuoteParam;
	UINT32	PRIN2OpenCloseParam;
	UINT32  PRIN2SmartGkeyParam;
	UINT32  PRIN2sQuoteParam;
	UINT32	CROWD1OpenCloseParam;
	UINT32	CROWD1SmartGkeyParam;
	UINT32  CROWD2OpenCloseParam;
	UINT32	CROWD2SmartGkeyParam;
	_manualtmpparamsgrp(){}
}ManualTempParamGrp;
#pragma pack(pop)


typedef enum
{
	STOCKSTATEFLAGSGROUP = 37000,
	SAPIFUNCTIONSSTATUSGROUP = 37001,
	CLOSINGTIMEGROUP = 37002,
	DMMPOSITIONGROUP = 37003,
	SOFTWAREINFOGROUP = 37004,
	LASTSALEGROUP = 37005,
	BUYPRICEPOINTAGGLIMITGROUP = 36007,
	SELLPRICEPOINTAGGLIMITGROUP = 36008,
	SQUOTEBUYPRICEPOINTSGROUP = 36013,
	SQUOTESELLPRICEPOINTSGROUP = 36014,
	AWAYQUOTESGROUP = 36015,
	MDINFOGROUP = 36022,
	LRPGROUP = 37006,
	ALGOCONFIRMATIONGROUP = 36026,
	ALGODISPOSITIONREJECTGROUP = 36025,
	OPENONTRADEPRICEPOINTSGROUP = 36033,
	CLOSEONTRADEPRICEPOINTSGROUP = 36097,
	SSRGROUP = 37007,
	PRICEBANDGRP = 37008,
	AGGSQUOTEBUYPRICEPOINTSGRP = 36093,
	AGGSQUOTESELLPRICEPOINTSGRP = 36094,
	AGGCCSQUOTEBUYPRICEPOINTSGRP = 36095,
	AGGCCSQUOTESELLPRICEPOINTSGRP = 36096,
	MANUALTEMPLATEPARAMETERSGROUP = 37009,

} RepeatingGrps;

/**********************************************************************************/

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
	STOCK_INFO_STATUS_MESSAGE = 0x0431,
	REFRESH_REQUEST_MESSAGE =   0x0241,
	BOOKSTATE_FULL_UPDATE_MESSAGE_SOLICITED = 0x0371,
	BOOKSTATE_FULL_UPDATE_MESSAGE_UNSOLICITED = 0x0381,
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
	void Format_subscribe_req_message(unsigned char* body,UINT16 symbolID);
	void Format_symbol_test_req_message(unsigned char* body);
	void Format_unsubscribe_req_message(unsigned char* body);
	void Format_stockinfo_req_message(unsigned char* body);
	void Format_refresh_req_message(unsigned char* body,UINT16);

	void parse_response(unsigned char* body);
	MsgType get_msg_type(unsigned char* body);


private:
	MsgHeader msgHeaderInfo;
	unsigned char MsgBody[512];

	MsgHeader make_header(MsgType type);
	void make_logon_request_body(unsigned char *);
	void make_session_test_body(unsigned char *);
	void make_heartbeat_resp_body(unsigned char *);
	void make_session_sequp_body(unsigned char *);
	void make_subscribe_req_body(unsigned char *,UINT16);
	void make_symbol_test_req_body(unsigned char *);
	void make_unsubscribe_req_body(unsigned char *);
	void make_stockinfo_req_body(unsigned char *);
	void make_refresh_req_body(unsigned char *,UINT16);
	

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
	void get_bookstate_fullupd_msg(unsigned char* body);


};

}