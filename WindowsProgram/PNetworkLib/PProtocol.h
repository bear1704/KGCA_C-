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
	WORD len;   // ������ ����+�������   WORD : unisgned short
	WORD type;  // ��Ŷ Ÿ�� (��������)
	WORD id;

}PACKET_HEADER;
typedef struct pkt{
	PACKET_HEADER ph;
	char          msg[PACKET_MAX_DATA_SIZE];
}PACKET;

#define PACKET_ANYDIR_SAY_HI				600		//���� �� Hello
#define	PACKET_CHAR_MSG					601		//�޽��� ����(ä��)
#define PACKET_CS_LOGIN_SEND_USERNAME	602		//�α��� �� �����̸��� �Է¹޾� ����
#define PACKET_SC_LOGIN_ACCEPT			603		//�α��� ����
#define PACKET_SC_ID_PROVIDE			604		//���� ���� �� ID�� �ο�
#define PACKET_SC_SPAWN_CHARACTER				632		//������ Ŭ�󿡰� �����÷��̾� ���� ����, ID�ο�, ������ �ο� 
#define PACKET_CS_SPAWN_COMPLETE				633
#define PACKET_BROADCAST_USERX_SPAWN			634		//������ Ŭ��鿡�� USERX�� ���������� �˸�
#define PACKET_BROADCAST_USERX_MOVEAXIS_AtoB	700		//�����鿡�� ����X�� �̵����¸� ����϶�� ����.user pos���� + ���� + �ӵ�
#define	PACKET_BROADCAST_ATTACK_SUCCESS			701		//������ Ŭ�󿡰� �ش� ������ ���������� �˸�
#define	PACKET_CS_ATTACK_REQUEST				703		//Ŭ�� �������� ���� ��û. ����
#define	PACKET_SC_ATTACK_ACK					704		//
#define	PACKET_BROADCAST_USERX_JUMP				705		//����X�� ������ �����鿡�� �˸�
#define	PACKET_CS_REPORT_MYPOSITION				706		//��ġ������ ��ġ����
#define PACKET_CS_REPORT_MOVE_STATUS_MYPOSITION 707		//Ŭ�� �������� �̵����̶� �˸�. ���� pos + �̵��ӵ� + �̵�����(���巹Ŀ�� �߷п�)
#define PACKET_BROADCAST_BE_ATTACKED			708		//������ Ŭ�󿡰� ���ݹ޾Ҵ� �˸�  ������ + ����
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
