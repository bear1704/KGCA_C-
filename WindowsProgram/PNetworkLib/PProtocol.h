#pragma once
#define PACKET_HEADER_SIZE 6
#define PACKET_MAX_DATA_SIZE 2048
#include <cassert>

#define ZAKUM_ID	20000
#define SERVER_ID   44444;

extern bool g_custom_tick;

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
	WORD id;  //클라는 내아이디, 서버는 보낼아이디, 서버가 브로드캐스트시 SERVER_ID

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
#define PACKET_BROADCAST_USERX_ATTACK_SUCCESS	701		//유저X가 몹을 때려서 데미지를 주었음을 브로드캐스트
#define PACKET_CS_USER_ATTACK					702		//클라의 캐릭터가 공격을 수행하였음을 알림(스킬, 방향 정보 삽입)
#define	PACKET_CS_MONSTER_HIT					703		//클라가 서버에게 몬스터가 피격당해 데미지를 입었음을 알림.
#define	PACKET_SC_ATTACK_ACK					704		//
#define	PACKET_BROADCAST_USERX_JUMP				705		//유저X의 점프를 유저들에게 알림
#define	PACKET_CS_REPORT_MYPOSITION				706		//위치보정용 위치전송
#define PACKET_CS_REPORT_MOVE_STATUS_MYPOSITION 707		//클라가 서버에게 이동중이라 알림. 유저 pos + 이동속도 + 이동방향(데드레커닝 추론용)
#define PACKET_BROADCAST_BE_ATTACKED			708		//서버가 클라에게 공격받았다 알림  데미지 + 방향
#define PACKET_BROADCAST_SPAWN_CHARACTER		709		//
#define PAKCET_BROADCAST_USERX_EXIT				710		//USERX가 나갔다고 브로드캐스트
#define PACKET_BROADCAST_USERX_HIT				730		//USERX 데미지 입었음을 알림
#define PACKET_CS_IM_HIT						731		//자기가 데미지를 입었음을 서버에게 보고
#define PACKET_SC_SPAWN_BOSS					780		//자쿰 소환 명령
#define PACKET_SC_BOSS_REAMIN_HP				781		//자쿰 남은 HP 서버->클라로 전송. 자신이 MONSTER_HIT을 보냈을때만 반송됨(HP 어긋나는거 방지)
#define PACKET_BROADCAST_METEOR_ACTIVE			901		//메테오 스킬 사용 지시


typedef struct{
	char username[30];
	int user_id;
}User;

typedef struct EXIT_MSG_{
	WORD id;
}EXIT_MSG;

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


typedef struct PKT_MSG_MONSTER_HIT_
{
	WORD monster_id;
	WORD player_cid;
	WORD player_user_id;
	int damage;
}PKT_MSG_MONSTER_HIT;

typedef struct INFO_CID_
{
	WORD cid;
}INFO_CID;

#pragma pack(pop)
