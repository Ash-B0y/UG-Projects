/****************************************************************************
* Copyright (C) 2011 SciShine CO LTD. All rights reserved.
*
*     you can use or modify this file for any purpose, but you must not modify
* this Copyright Statement.
****************************************************************************/

/*
* SSUApi.h
* description:
*       this is the Orignal API definetion for SciShine's UHF RFID Reader. all command
*   are synchronized.
* history:
* 20110921 running  created, for 32 bits platform.
*/
#ifndef SSUAPI_H
#define SSUAPI_H

#if defined( WIN32 )
#   if defined( _SSU_SRC_ )
#      define  SSU_EXPORT        __declspec(dllexport)
#   else //
#      define  SSU_EXPORT        __declspec(dllimport)
#   endif
#else
#   define  SSU_EXPORT
#endif

#define SSU_VERSION_API       0x03000000
#define SSU_VERSION_PROTO     0x0300

/*
* SSU Error Number
*/
#define SSUE_SUCCESS            0     /*成功*/
#define SSUE_ERROR             -1     /*执行出错*/
#define SSUE_MEM               -2     /*内存错误*/
#define SSUE_COMM_DATA         -10     /*通信数据异常*/
#define SSUE_COMM_TIMEOUT      -11     /*通信超时*/
#define SSUE_COMM_ERR          -12     /*通信错误*/

// <= -50
#define SSUE_TAG_MEM_OVR       -80    // 标签越界
#define SSUE_TAG_MEM_LCK       -81    // 标签锁定
#define SSUE_TAG_PWR           -82    // 标签能量

#define SSUE_FAIL              -127   // 设备上操作不成功

/*
* 参数名
*/
#define CONFIG_NAME_invtRspTm         1        //盘存响应最大时限, ms
#define CONFIG_NAME_invtBufTm         2        //盘存结果刷新时间, s
#define CONFIG_NAME_invtSess          3        //盘存占用的会话通道
#define CONFIG_NAME_invtQMax          4        //盘存最大Q值
#define CONFIG_NAME_invtQMin          5        //盘存最小Q值
#define CONFIG_NAME_invtQMinTries     6        //盘存最小Q值上重复调整次数
#define CONFIG_NAME_invtIdleMin       7        //盘存最小空闲时间，ms
#define CONFIG_NAME_invtIdleFract     8        //盘存空闲时间占工作时间的分数

#define CONFIG_NAME_rfAntMask        21        //射频通道启用掩码，1位代表一个通道，最低位bit0代表索引为0的通道，以此类推
#define CONFIG_NAME_rfGain           22        //射频输出功率增益0-31dbm
#define CONFIG_NAME_rfCenter         23        //射频中心频点(KHz)
#define CONFIG_NAME_rfDeviation      24        //射频跳频范围(+- rfDeviation KHz)
#define CONFIG_NAME_rfStep           25        //射频跳频步长(KHz)
	
#define CONFIG_NAME_beepEnable      253        //标签操作成功时蜂鸣器发声控制，==0不发，缺省值0
///////////

/*
* 标签存储分区定义
*/
#define  TAG_BANK_RESERVED          0
#define  TAG_BANK_EPC               1
#define  TAG_BANK_TID               2
#define  TAG_BANK_USER              3

// net type
#define  SSU_NET_NONE    0x00   //无组网
#define  SSU_NET_TCPIP   0x01   //TCPIP网络
#define  SSU_NET_RS485   0x02   //RS485网络
#define  SSU_NET_CAN     0x03   //CAN网络

// net address type
#define  SSU_ADDR_RS232      ((SSU_NET_NONE  << 8) | 0x00)     // "COMx:nocrc"
#define  SSU_ADDR_RS485      ((SSU_NET_RS485  << 8) | 0x00)     // "COMx:Node"
#define  SSU_ADDR_CAN        ((SSU_NET_CAN  << 8) | 0x00)     // "COMx:Node"
#define  SSU_ADDR_TCP        ((SSU_NET_TCPIP << 8) | 0x01)     // "xxx.xxx.xxx.xxx:port"
#define  SSU_ADDR_UDP        ((SSU_NET_TCPIP << 8) | 0x02)     // "xxx.xxx.xxx.xxx:port"

/////////////////////
// const values
#define  SSU_TAGID_MAXSIZE   18
#define  SSU_TCP_UDP_PORT    2012
/*
* definetions for communication io of reader
*/


#ifdef __cplusplus
extern "C"
{
#endif

struct _st_ssu_context;
typedef struct _st_ssu_context SSUCtx;

typedef struct _st_dev_info
{
	unsigned int   version;      // main(31~24) + sub(23~16) + build(15~0)
	unsigned int   devSN;        // yy(31~24) + mm(23~20) + sn(19~0)
	char           devModel[16]; //ascii string ended by '\0'
}SSUDevInfo;

typedef struct _st_net_addr
{
	int  netType;  // enumerated by SSU_NET_xxx
	union
	{
		struct
		{
			unsigned char netip[4];
			unsigned char gateway[4];
			unsigned char netmask[4];
		} tcpip;

		unsigned char rs485;
	};
}SSUNetAddr;

extern SSU_EXPORT const unsigned char SSU_PWD_EMPTY[4];



/* SSUSetup/SSUShutup
 description:
		setup the api lib, initiate the communication arguments.
*/
SSU_EXPORT void  SSUSetup();
SSU_EXPORT void  SSUShutup();

/*
* SSUEbvBuild
* description:
*     build a integer into ebv byte string.
* argument:
     val - input integer
     buff - output the encoding byte string
     size - sizeof buff
* return:
	 >0 - encoding bytes
     <0 - error
*/
SSU_EXPORT int  SSUEbvBuild(unsigned int val, unsigned char* buff, int size);

/*
* SSUEbvBuild
* description:
*     build a integer into ebv byte string.
* argument:
     val - output integer
     buff - input the encoding byte string
     size - sizeof buff
* return:
	 >0 - decoding bytes
     <0 - error
*/
SSU_EXPORT int  SSUEbvParse(unsigned int* val, const unsigned char* buff, int size);


/* SSUNetAddrProc
 description:
		call back function to receive netaddr.
 argument:
     devSn - input the device sn, formated to yy(bit31~24)mm(bit23~20)xxxxxx(bit19~0)
     netAddr - input the net address of device noted by devSn.
 return:
	>0 - count of node
    =0 - no node.
    <0 - error defined by SSUE_....
*/
typedef void (*SSUNetAddrProc)(unsigned int devSn, SSUNetAddr* netAddr);

/* SSUNodeExplore
 description:
		query net address of all nodes on net. this function may block several seconds.
 argument:
     broadcastAddr - the address of net broadcasting.
     netType - input the net type, SSU_NET_xxx.
	 timeout - input the communication timeout, by ms.
     callback - input the callback function to process the netaddr received.
 return:
	>0 - count of node
    =0 - no node.
    <0 - error defined by SSUE_....
*/
SSU_EXPORT int  SSUNodeExplore(const char* broadcastAddr, int netType, int timeout, SSUNetAddrProc callback);

/* SSUNodeSet
 description:
     set address to the node identified by devSn.
 argument:
     broadcastAddr - the address of net broadcasting.
     connpwd - input the connecting password of target device.
     devSn - input the device sn, formated to yy(bit31~24)mm(bit23~20)xxxxxx(bit19~0)
     netAddr - input the net address of device noted by devSn.
	 timeout - input the communication timeout, by ms.
 return:
    =0 - successful.
    <0 - error defined by SSUE_....
*/
SSU_EXPORT int  SSUNodeSet(const char* broadcastAddr, const unsigned char connpwd[4], unsigned int devSn, const SSUNetAddr* netAddr, int timeout);


/* SSUConnect
 description:
     open and connect a context related to Reader Communication.
 argument:
     addr - input the reader's net addr.
     type - input the type of addr, rs232/rs485/tcpip/can. the address of rs232 is formated to "COMx:nocrc",
	        nocrc is valued to 0(with crc) or 1(without crc); rs485 is formated to "COMx:node", node is the
			the distinct No of the device on RS485 network, ranged (0, 255], and 255 is broadcasting address;
			can is same as 485; tcpip is formated to "ip:port".
	 timeout - input the communication timeout used from connecting to disconnecting.
	 pwd - password
	 customNo - custom number, customer id.
	 devInfo - output the infomation of device connected, include model, device sn, firmware version
*/
SSU_EXPORT SSUCtx* SSUConnect(const char* addr, int addrType, int timeout, const unsigned char pwd[4], unsigned int customNo, SSUDevInfo* devInfo);

/* SSUConfigGet
 description:
       get an argument of reader. 
 argument:
     ctx - input the communication context.
	 name - input the argument name
	 buff - output argument value
 	 size - input the bytes of buff
return:
     >=0 - the bytes of output argument buffer.
     <0 - error. 
*/
SSU_EXPORT int  SSUConfigGet(SSUCtx* ctx, unsigned short name, unsigned char* buff, int size);

/* SSUConfigBegin
 description:
       start a config progress. 
 argument:
     ctx - input the communication context.
 return:
     =0 - success.
     <0 - error. 
*/
SSU_EXPORT int  SSUConfigBegin(SSUCtx* ctx);

/* SSUConfigSet
 description:
       set an argument of reader. 
 argument:
     ctx - input the communication context.
	 name - input argument name
	 buff - input argument value
	 size - input the bytes of value
 return:
     =0 - success.
     <0 - error. 
*/
SSU_EXPORT int  SSUConfigSet(SSUCtx* ctx, unsigned short name, const unsigned char* buff, int size);

/* SSUConfigEnd
 description:
       end a config progress, the reader will store the modified arguments. 
 argument:
     ctx - input the communication context.
	 save - 0 is no save set, 1 is save.
 return:
	 >0 - success, but config not save
     =0 - success, and config saved.
     <0 - error. 
*/
SSU_EXPORT int  SSUConfigEnd(SSUCtx* ctx, unsigned char save);


/* SSUTagInvtAuto
 description:
       command the reader do inventory automatically. 
 argument:
     ctx - input the communication context.
	 enableReport - if enable the reader to report tagid automatically; it must alway be 0.
 return:
      0 - success.
     <0 - error. 
*/
SSU_EXPORT int  SSUTagInvtAuto(SSUCtx* ctx, unsigned char enableReport);

/* SSUTagInvtStop
 description:
       command the reader stop automatical inventorying. 
 argument:
     ctx - input the communication context.
 return:
      0 - success.
     <0 - error. 
*/
SSU_EXPORT int  SSUTagInvtStop(SSUCtx* ctx);

/* SSUTagQuery
 description:
       query a current tagid detected by reader. 
 argument:
     ctx - input the communication context.
	 tag - output tag buffer. the buffer is temperary, use atonce and should not save
	 --------------------------------------------------------------------------------
	 antNo - if not NULL, output the antNo(0~7) where the tag was detected. (-1) is empty.
 return:
     >0 - the bytes of output tag buffer.
      0 - no tag.
     <0 - error. 
*/
SSU_EXPORT int  SSUTagQuery(SSUCtx* ctx, unsigned char** tag, char* antNo);

/* SSUTagRead
 description:
       read data from a certain tag
 argument:
     ctx - input the communication context
	 pwd - access password
	 tag - input (or output when tagByts is 0) target tag epc(packedEpc). user should
	       ensure size of tag buffer more than SSU_TAGID_MAXSIZE. not null.
	 tagByts - input (or output) the bytes(0 ~ 63) of tagid. not null. 0 means operating 
	       any tag and output the operated tag's epc bytes.
	 bank - input the target sector number of tag, 0<=bank<=3.
	 offset - input the offset words that the reading start at, >=0. one word has two bytes.
	 words - input the words that the reading want, >0. one word has two bytes.
	 data - output the data, which should be sized to words * 2 bytes.
	 -------------------------------------------------------------------------------
	 antNo - input the antina where the tag would be operated. valid value is in range of 0 to 7, 
	         if <0 or outof the reader's range, all did by the reader.
 return:
     >0 - success, return 'words'
     <0 - error
*/
SSU_EXPORT int  SSUTagRead(SSUCtx* ctx, const unsigned char pwd[4], unsigned char* tag, int* tagByts, int bank, int offset, int words, unsigned char* data, char antNo);

/* SSUTagWrite
 description:
       write data to a certain tag
 argument:
     ctx - input the communication context
	 pwd - access password
	 tag - input (or output when tagByts is 0) target tag epc(packedEpc). user should
	       ensure size of tag buffer more than SSU_TAGID_MAXSIZE. not null.
	 tagByts - input (or output) the bytes(0 ~ 63) of tagid. not null. 0 means operating 
	       any tag and output the operated tag's epc bytes.
	 bank - input the target sector number of tag, 0<=bank<=3
	 offset - input the offset words that the reading start at, >=0. one word has two bytes.
	 words - input the words that the reading want, >0. one word has two bytes.
	 data - input the data, which should be sized to words * 2 bytes.
	 -------------------------------------------------------------------------------
	 antNo - input the antina where the tag would be operated. valid value is in range of 0 to 7, 
	         if <0 or outof the reader's range, all did by the reader.
 return:
     >0 - success, return 'words'
     <0 - error
*/
SSU_EXPORT int  SSUTagWrite(SSUCtx* ctx, const unsigned char pwd[4], unsigned char* tag, int* tagByts, int bank, int offset, int words, const unsigned char* data, char antNo);

/* SSUTagLock
 description:
       lock a certain tag
 argument:
     ctx - input the communication context
	 pwd - access password
	 tag - input target tag epc(packedEpc). not null
	 tagByts - input the bytes(1 ~ 63) of tag
	 lckData - input the lock data
	 -------------------------------------------------------------------------------
	 antNo - input the antina where the tag would be operated. valid value is in range of 0 to 7, 
	         if <0 or outof the reader's range, all did by the reader.
 return:
      0 - success
     <0 - error
*/
SSU_EXPORT int  SSUTagLock(SSUCtx* ctx, const unsigned char pwd[4], const unsigned char* tag, int tagByts, unsigned char lckData[3], char antNo);

/* SSUTagKill
 description:
       kill a certain tag
 argument:
     ctx - input the communication context
	 apwd - access password
	 kpwd - kill password
	 tag - input target tag epc(packedEpc). not null
	 tagByts - input the bytes(1 ~ 63) of tag
	 -------------------------------------------------------------------------------
	 antNo - input the antina where the tag would be operated. valid value is in range of 0 to 7, 
	         if <0 or outof the reader's range, all did by the reader.
 return:
      0 - success
     <0 - error
*/
SSU_EXPORT int  SSUTagKill(SSUCtx* ctx, const unsigned char apwd[4], const unsigned char kpwd[4], const unsigned char* tag, int tagByts, char antNo);

/* SSUConnPwdSet
 description:
     set the device's connecting password.
 argument:
     ctx - input the communication context.
     oldPwd - input the old connecting password.
     newPwd - input the new connecting password.
 return:
    =0 - successful.
    <0 - error defined by SSUE_....
*/
SSU_EXPORT int  SSUConnPwdSet(SSUCtx* ctx, const unsigned char oldPwd[4], const unsigned char newPwd[4]);

/* SSUNetAddrGet
 description:
		query net address of all nodes on net. this function may block several seconds.
 argument:
     ctx - input the context.
     netAddr - output the net address of the device connected.
 return:
    =0 - success.
    <0 - error defined by SSUE_....
*/
SSU_EXPORT int  SSUNetAddrGet(SSUCtx* ctx, SSUNetAddr* netAddr);

/* SSUNetAddrSet
 description:
     set the device's net address.
 argument:
     ctx - input the context.
     connpwd - input the connecting password of target device.
     netAddr - input the net address of device connected (identified by devSn).
 return:
    =0 - success.
    <0 - error defined by SSUE_....
*/
SSU_EXPORT int  SSUNetAddrSet(SSUCtx* ctx, const unsigned char connpwd[4], const SSUNetAddr* addr);

/*
* SSUDisconnect
* description:
*     disconnect communication and destroy the context.
* argument:
*     ctx - input the context.
*     force - input force disconnect flag, 1 force disconnect, 0 not force.
* return:
      0 - success
     <0 - error
*/
SSU_EXPORT int  SSUDisconnect(SSUCtx* ctx, unsigned int force);


/************************************************************************
          extanded functions which use special password formating
*************************************************************************/

/* SSUTagReadEx
 description:
       read TID or user data from a certain tag
 argument:
     ctx - input the communication context
	 tag - input (or output when tagByts is 0) target tag epc(packedEpc). user should
	       ensure size of tag buffer more than SSU_TAGID_MAXSIZE. not null.
	 tagByts - input (or output) the bytes(0 ~ 63) of tagid. not null. 0 means operating 
	       any tag and output the operated tag's epc bytes.
	 offset - input the offset words that the reading start at, >=0. one word has two bytes.
	 words - input the words that the reading want, >0. one word has two bytes.
	 data - output the data, which should be sized to words * 2 bytes.
 return:
     >0 - success, return 'words'
     <0 - error
*/
SSU_EXPORT int  SSUTagReadTID(SSUCtx* ctx, unsigned char* tag, int* tagByts, int offset, int words, unsigned char* data);
SSU_EXPORT int  SSUTagReadUSR(SSUCtx* ctx, unsigned char* tag, int* tagByts, int offset, int words, unsigned char* data);

/* SSUTagWriteUSR
 description:
       write EPC, Access Password, Kill Password, or User Data of a certain tag.
 argument:
     ctx - input the communication context
	 tagPwd - access password string of target tag
	 tag - input (or output when tagByts is 0) target tag epc(packedEpc). user should
	       ensure size of tag buffer more than SSU_TAGID_MAXSIZE. not null.
	 tagByts - input (or output) the bytes(0 ~ 63) of tagid. not null. 0 means operating 
	       any tag and output the operated tag's epc bytes.
	 offset - input the offset words that the reading start at, >=0. one word has two bytes.
	 words - input the words that the reading want, >0. one word has two bytes.
	 data - input the data, which should be sized to words * 2 bytes.
 return:
     >=0 - success, when >0 it return 'words'
     <0 - error
*/
SSU_EXPORT int  SSUTagWriteUSR(SSUCtx* ctx, const char* tagPwd, unsigned char* tag, int* tagByts, int offset, int words, const unsigned char* data);

/* SSUTagResetEPC
 description:
       reset the epc of a certain tag.
 argument:
     ctx - input the communication context
	 tagPwd - access password string of target tag
	 tag - input the target tag epc(packedEpc). not null.
	 tagByts - input the bytes of tagid, >0.
	 epc - input the new EPC(PC + EPC) byte string, not null.
	 epcByts - input the lengh of new EPC, even, >0.
 return:
     =0 - success
     <0 - error
*/
SSU_EXPORT int  SSUTagResetEPC(SSUCtx* ctx, const char* tagPwd, const unsigned char* tag, int tagByts, const unsigned char* epc, int epcByts);

/* SSUTagResetPWD
 description:
       reset the access password or kill password of a certain tag.
 argument:
     ctx - input the communication context
	 tagPwd - access password string of target tag
	 tag - input the target tag epc(packedEpc). not null.
	 tagByts - input the bytes of tagid, >0.
	 accPwd - input the new access password string, null means ignore.
	 killPwd - input the new kill password string, null means ignore.
 return:
     =0 - success
     <0 - error
*/
SSU_EXPORT int  SSUTagResetPWD(SSUCtx* ctx, const char* tagPwd, const unsigned char* tag, int tagByts, const char* accPwd, const char* killPwd);

/* SSUTagSolitifyEPC/SSUTagSolitifyUSR
 description:
       solitify EPC or USR permanently
 argument:
     ctx - input the communication context
	 tagPwd - access password of target tag
	 tag - input target tag epc(packedEpc). not null
	 tagByts - input the bytes(1 ~ 63) of tag
	 bank - input the target bank
	 opt - input the lock opt, 0 is unlock, 1 is lock, 2 is permanent lock
 return:
      0 - success
     <0 - error
*/
SSU_EXPORT int  SSUTagSolitifyEPC(SSUCtx* ctx, const char* tagPwd, const unsigned char* tag, int tagByts);
SSU_EXPORT int  SSUTagSolitifyUSR(SSUCtx* ctx, const char* tagPwd, const unsigned char* tag, int tagByts);

/* SSUTagKillEx
 description:
       kill a certain tag
 argument:
     ctx - input the communication context
	 tagAccPwd - input the access password string of target tag, not null
	 tagKillPwd - input the kill password string of target tag, not null
	 tag - input target tag epc(packedEpc). not null
	 tagByts - input the bytes of tag
 return:
      0 - success
     <0 - error
*/
SSU_EXPORT int  SSUTagKillEx(SSUCtx* ctx, const char* tagAccPwd, const char* tagKillPwd, const unsigned char* tag, int tagByts);

/*
* SSUConvPwd
* description:
*     convert a extended password(char string) to origenal password(4 bytes).
* argument:
     passwdStr - input password string, NULL or "" means {0,0,0,0}.
     passwdBuf - output password buffer sized 4
*/
SSU_EXPORT void  SSUConvPwd(const char* passwdStr, unsigned char passwdBuf[4]);


#ifdef __cplusplus
}
#endif


#endif
