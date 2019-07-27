#pragma once
#define PACKET_HEADER_SIZE 6
#define PACKET_MAX_DATA_SIZE 2048
#include <cassert>

template<typename T>
using PacketMessage = T*;

#pragma pack( push, 1)

enum class Direction
{
	LEFT,
	RIGHT,
};

typedef struct ph
{
	WORD len;   // 데이터 길이+헤더길이   WORD : unisgned short
	WORD type;  // 패킷 타입 (프로토콜)
	WORD id;

}PACKET_HEADER;
typedef struct pkt{
	PACKET_HEADER ph;
	char          msg[PACKET_MAX_DATA_SIZE];
}PACKET;

#define PACKET_ANYDIR_SAY_HI				600		//접속 시 Hello
#define	PACKET_CHAR_MSG					601		//메시지 전송(채팅)
#define PACKET_CS_LOGIN_SEND_USERNAME	602		//로그인 시 유저이름을 입력받아 전송
#define PACKET_SC_LOGIN_ACCEPT			603		//로그인 승인
#define PACKET_SC_ID_PROVIDE			604		//최초 접속 시 ID값 부여
#define PACKET_SC_SPAWN_CHARACTER				632		//서버가 클라에게 메인플레이어 생성 지시, ID부여, 포지션 부여 
#define PACKET_CS_SPAWN_COMPLETE				633
#define PACKET_BROADCAST_USERX_SPAWN			634		//서버가 클라들에게 USERX가 스폰했음을 알림
#define PACKET_BROADCAST_USERX_MOVEAXIS_AtoB	700		//유저들에게 유저X의 이동상태를 재생하라고 보냄.user pos정보 + 방향 + 속도
#define	PACKET_BROADCAST_ATTACK_SUCCESS			701		//서버가 클라에게 해당 공격이 성공했음을 알림
#define	PACKET_CS_ATTACK_REQUEST				703		//클라가 서버에게 공격 요청. 공격
#define	PACKET_SC_ATTACK_ACK					704		//
#define	PACKET_BROADCAST_USERX_JUMP				705		//유저X의 점프를 유저들에게 알림
#define	PACKET_CS_REPORT_MYPOSITION				706		//위치보정용 위치전송
#define PACKET_CS_REPORT_MOVE_STATUS_MYPOSITION 707		//클라가 서버에게 이동중이라 알림. 유저 pos + 이동속도 + 이동방향(데드레커닝 추론용)
#define PACKET_BROADCAST_BE_ATTACKED			708		//서버가 클라에게 공격받았다 알림  데미지 + 방향
#define PACKET_BROADCAST_SPAWN_CHARACTER		709		//
#define PACKET_SC_TEST_HPDECREASE				710



typedef struct{
	char username[30];
	int user_id;
}User;

typedef struct {
	User user;
	PACKET packet;
}USER_PACKET;

typedef struct {
	char text[256];
}TextMessage;

typedef struct PKT_MSG_SPAWN_ {
	WORD id;
	float posx;
	float posy;
}PKT_MSG_SPAWN;

typedef struct PKT_MSG_REGULAR_POS_REPORT_
{
	WORD cid;
	float posx; float posy;
	FSM_State current_state;
	Direction dir;

}PKT_MSG_REGULAR_POS_REPORT;


#pragma pack(pop)
