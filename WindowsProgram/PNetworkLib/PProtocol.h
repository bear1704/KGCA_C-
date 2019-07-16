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

#define PACKET_SC_SAY_HI 600


	typedef struct{
		char username[30];
		int user_id;
	}User;

	typedef struct {
		User user;
		PACKET packet;
	}USER_PACKET;

#pragma pack(pop)
