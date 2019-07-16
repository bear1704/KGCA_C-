#pragma once
#define PACKET_HEADER_SIZE 4
#define PACKET_MAX_DATA_SIZE 2048
#include <cassert>

#pragma pack( push, 1)
typedef struct
{
	WORD len;   // 데이터 길이+헤더길이   WORD : unisgned short
	WORD type;  // 패킷 타입
}PACKET_HEADER;
typedef struct {
	PACKET_HEADER ph;
	char          msg[PACKET_MAX_DATA_SIZE];
}PACKET;

#define PACKET_SC_SAY_HI				600
#define	PACKET_CHAR_MSG					601
#define PACKET_CS_LOGIN_SEND_USERNAME	602
#define PACKET_SC_LOGIN_ACCEPT			603
#define PACKET_BROADCAST_USERX_MOVEAXIS_AtoB	604
#define	PACKET_BROADCAST_ATTACK_SUCCESS			605
#define	PACKET_CS_ATTACK_REQUEST				606
#define	PACKET_SC_ATTACK_ACK					607
#define	PACKET_BROADCAST_USERX_JUMP				608
#define	PACKET_CS_REPORT_MYPOSITION				609
#define PACKET_BROADCAST_BE_ATTACKED			610


typedef struct{
	char username[30];
	int user_id;
}User;

typedef struct {
	User user;
	PACKET packet;
}USER_PACKET;

#pragma pack(pop)
