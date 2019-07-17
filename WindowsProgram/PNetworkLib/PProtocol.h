#pragma once
#define PACKET_HEADER_SIZE 4
#define PACKET_MAX_DATA_SIZE 2048
#include <cassert>

#pragma pack( push, 1)
typedef struct
{
	WORD len;   // ������ ����+�������   WORD : unisgned short
	WORD type;  // ��Ŷ Ÿ��
}PACKET_HEADER;
typedef struct {
	PACKET_HEADER ph;
	char          msg[PACKET_MAX_DATA_SIZE];

	


}PACKET;

#define PACKET_SC_SAY_HI				600		//���� �� Hello
#define	PACKET_CHAR_MSG					601		//�޽��� ����(ä��)
#define PACKET_CS_LOGIN_SEND_USERNAME	602		//�α��� �� �����̸��� �Է¹޾� ����
#define PACKET_SC_LOGIN_ACCEPT			603		//�α��� ����
#define PACKET_BROADCAST_USERX_MOVEAXIS_AtoB	604		//�����鿡�� ����X�� �̵����¸� ����϶�� ����.user pos���� + ���� + �ӵ�
#define	PACKET_BROADCAST_ATTACK_SUCCESS			605		//������ Ŭ�󿡰� �ش� ������ ���������� �˸�
#define	PACKET_CS_ATTACK_REQUEST				606		//Ŭ�� �������� ���� ��û. ����
#define	PACKET_SC_ATTACK_ACK					607		//
#define	PACKET_BROADCAST_USERX_JUMP				608		//����X�� ������ �����鿡�� �˸�
#define	PACKET_CS_REPORT_MYPOSITION				609		//��ġ������ ��ġ����
#define PACKET_CS_REPORT_MOVE_STATUS_MYPOSITION 610		//Ŭ�� �������� �̵����̶� �˸�. ���� pos + �̵��ӵ� + �̵�����(���巹Ŀ�� �߷п�)
#define PACKET_BROADCAST_BE_ATTACKED			611		//������ Ŭ�󿡰� ���ݹ޾Ҵ� �˸�  ������ + ����
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
