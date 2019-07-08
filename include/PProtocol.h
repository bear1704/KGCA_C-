#pragma once
#define PACKET_HEADER_SIZE 4
#define PACKET_MAX_DATA_SIZE 2048

#pragma pack( push, 1)
	typedef struct
	{
		WORD len;   // 데이터 길이+헤더길이   WORD : unisgned short
		WORD type;  // 패킷 타입
	}PACKET_HEADER;
	typedef struct {
		PACKET_HEADER ph;
		char          msg[PACKET_MAX_DATA_SIZE];
	}UPACKET;

	#define PACKET_CHAR_MSG				 1000 // DATA
	#define PACKET_CHAR_NAME_SC_REQ		 1001 // DATA
	#define PACKET_CHAR_NAME_CS_ACK		 1002 // DATA
	#define PACKET_JOIN_SIGNIN_SC		 1003 // x
	#define PACKET_JOIN_USER_SC			 1004 // DATA
	#define PACKET_CS_DROP_REQ			 1005 // x
	#define PACKET_SC_DROP_ACK			 1006 // x
	#define PACKET_SC_BROAD_DROPUSER	 1007 // DATA


	#define USER_BASE_SIZE 24
	#define USER_NAME_SIZE 20
	typedef struct {
		int   index;
		char  user_name[USER_NAME_SIZE];
	}USER_NAME_ACK, USER_BASE;
	
	typedef struct	{
		USER_BASE user_base;
		char  msg[30];
	}USER_NAME_REQ;

	typedef struct	{
		char  user_name[USER_NAME_SIZE];
		char  msg[PACKET_MAX_DATA_SIZE-USER_NAME_SIZE];// 메세지 실제 크기
	}USER_CHAT_MSG;

#pragma pack(pop)
