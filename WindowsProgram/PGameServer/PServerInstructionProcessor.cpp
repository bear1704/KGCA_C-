#include "PServerInstructionProcessor.h"

std::mutex PServerInstructionProcessor::process_mutex1_;
PServerInstructionProcessor::PServerInstructionProcessor()
{
	
}


PServerInstructionProcessor::~PServerInstructionProcessor()
{
}



void PServerInstructionProcessor::ProcessInstruction()
{

	while (g_window_terminated == false)
	{
		std::unique_lock<std::mutex> ul(process_mutex1_); //mutex 버그 발생지점. 왜?
		PInstructionManager::GetInstance().process_event_.wait(ul, []()
			{return !PInstructionManager::GetInstance().IsQueueEmpty(); }); //큐가 비지 않았다면 실행


		if (g_window_terminated == true)
			break;

		//아래에 구현내용
		PACKET packet = PInstructionManager::GetInstance().PopBackInstruction();
		

		switch (packet.ph.type)
		{
				case PACKET_CS_LOGIN_SEND_USERNAME:
				{
					WORD id = packet.ph.id;
					PUser* user = PUserManager::GetInstance().FindUserById(id);
					std::string str(packet.msg);
					user->set_name(str);

					printf("\n[플레이어 id %hd 의 이름 %s 전송받음]", id, user->get_name().c_str());
					
					std::random_device r;
					std::mt19937 engine(r());
					std::uniform_int_distribution<int> distribution(9016, 10000);
					auto generator = std::bind(distribution, engine); //데미지 난수화 
					WORD random = generator();

					PKT_MSG_SPAWN pkt_msg;
					pkt_msg.id = random;
					pkt_msg.posx = 500.0f;
					pkt_msg.posy = 300.0f;

					char msg[sizeof(PKT_MSG_SPAWN)];
					memcpy(msg, &pkt_msg, sizeof(PKT_MSG_SPAWN));


					PPacketManager::GetInstance().PushPacket(user, PACKET_SC_SPAWN_CHARACTER, 
						msg, sizeof(PKT_MSG_SPAWN),
						PushType::SEND, true); //플레이어 캐릭터에게 아이디 전송하고 캐릭터 스폰하라고 지시
					printf("\n [캐릭터 스폰 지시, Pos : %f,%f , CID : %hd, SOCKET : %d]", 
						pkt_msg.posx, pkt_msg.posy, random, (int)(user->get_socket()));

					user->set_character_id(random);

					break;
				}
				case PACKET_ANYDIR_SAY_HI:
				{
					SOCKET sock;
					memcpy(&sock, packet.msg, sizeof(SOCKET));
					
					PUser* user = PUserManager::GetInstance().FindUserBySocket(sock);
				
					PPacketManager::GetInstance().PushPacket(user, PACKET_SC_ID_PROVIDE, (char*)user->get_id(), 
						sizeof(WORD), PushType::SEND, false);

					printf("\n[유저에게 ID부여 : %hd, SOCKET : %d]", user->get_id(), user->get_socket());
					break;

				}
				case PACKET_CS_SPAWN_COMPLETE: //플레이어 스폰되면 그 주소를 브로드캐스트
				{
					PACKET pack;
					ZeroMemory(&pack, sizeof(PACKET));
					memcpy(&pack, &packet, sizeof(packet));
					pack.ph.type = PACKET_BROADCAST_USERX_SPAWN;
					Broadcast(pack);
					printf("\n ID : %hd 인 플레이어 스폰됨을 브로드캐스트함, ", packet.ph.id);
					break;
				}
		}

	}

}

bool PServerInstructionProcessor::Init()
{
	return false;
}

bool PServerInstructionProcessor::Frame()
{
	return false;
}

bool PServerInstructionProcessor::Render()
{
	return false;
}

bool PServerInstructionProcessor::Release()
{
	return false;
}

bool PServerInstructionProcessor::Broadcast(PACKET& packet)
{
	std::vector<PUser*> userlist = PUserManager::GetInstance().user_list_;

	for (auto iter : userlist)
	{
		PPacketManager::GetInstance().PushPacket(iter, packet.ph.type, packet.msg, sizeof(packet.msg), PushType::SEND, true);
		
	}

	return false;
}
