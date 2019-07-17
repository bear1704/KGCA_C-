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

#define PACKET_SC_SAY_HI				600		//접속 시 Hello
#define	PACKET_CHAR_MSG					601		//메시지 전송(채팅)
#define PACKET_CS_LOGIN_SEND_USERNAME	602		//로그인 시 유저이름을 입력받아 전송
#define PACKET_SC_LOGIN_ACCEPT			603		//로그인 승인
#define PACKET_BROADCAST_USERX_MOVEAXIS_AtoB	604		//유저들에게 유저X의 이동상태를 재생하라고 보냄.user pos정보 + 방향 + 속도
#define	PACKET_BROADCAST_ATTACK_SUCCESS			605		//서버가 클라에게 해당 공격이 성공했음을 알림
#define	PACKET_CS_ATTACK_REQUEST				606		//클라가 서버에게 공격 요청. 공격
#define	PACKET_SC_ATTACK_ACK					607		//
#define	PACKET_BROADCAST_USERX_JUMP				608		//유저X의 점프를 유저들에게 알림
#define	PACKET_CS_REPORT_MYPOSITION				609		//위치보정용 위치전송
#define PACKET_CS_REPORT_MOVE_STATUS_MYPOSITION 610		//클라가 서버에게 이동중이라 알림. 유저 pos + 이동속도 + 이동방향(데드레커닝 추론용)
#define PACKET_BROADCAST_BE_ATTACKED			611		//서버가 클라에게 공격받았다 알림  데미지 + 방향
#define PACKET_BROADCAST_SPAWN_CHARACTER		612		//


typedef struct{
	char username[30];
	int user_id;
}User;

typedef struct {
	User user;
	PACKET packet;
}USER_PACKET;

#pragma pack(pop)
