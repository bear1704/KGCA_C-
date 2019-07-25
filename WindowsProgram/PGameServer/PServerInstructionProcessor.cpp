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
		std::unique_lock<std::mutex> ul(process_mutex1_); //mutex ���� �߻�����. ��?
		PInstructionManager::GetInstance().process_event_.wait(ul, []()
			{return !PInstructionManager::GetInstance().IsQueueEmpty(); }); //ť�� ���� �ʾҴٸ� ����


		if (g_window_terminated == true)
			break;

		//�Ʒ��� ��������
		PACKET packet = PInstructionManager::GetInstance().PopBackInstruction();
		

		switch (packet.ph.type)
		{
				case PACKET_CS_LOGIN_SEND_USERNAME:
				{
					WORD id = packet.ph.id;
					PUser* user = PUserManager::GetInstance().FindUserById(id);
					std::string str(packet.msg);
					user->set_name(str);

					printf("\n[�÷��̾� id %hd �� �̸� %s ���۹���]", id, user->get_name().c_str());
					
					std::random_device r;
					std::mt19937 engine(r());
					std::uniform_int_distribution<int> distribution(9016, 10000);
					auto generator = std::bind(distribution, engine); //������ ����ȭ 
					WORD random = generator();

					PKT_MSG_SPAWN pkt_msg;
					pkt_msg.id = random;
					pkt_msg.posx = 500.0f;
					pkt_msg.posy = 300.0f;

					char msg[sizeof(PKT_MSG_SPAWN)];
					memcpy(msg, &pkt_msg, sizeof(PKT_MSG_SPAWN));


					PPacketManager::GetInstance().PushPacket(user, PACKET_SC_SPAWN_CHARACTER, 
						msg, sizeof(PKT_MSG_SPAWN),
						PushType::SEND, true); //�÷��̾� ĳ���Ϳ��� ���̵� �����ϰ� ĳ���� �����϶�� ����
					printf("\n [ĳ���� ���� ����, Pos : %f,%f , CID : %hd, SOCKET : %d]", 
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

					printf("\n[�������� ID�ο� : %hd, SOCKET : %d]", user->get_id(), user->get_socket());
					break;

				}
				case PACKET_CS_SPAWN_COMPLETE: //�÷��̾� �����Ǹ� �� �ּҸ� ��ε�ĳ��Ʈ
				{
					PACKET pack;
					ZeroMemory(&pack, sizeof(PACKET));
					memcpy(&pack, &packet, sizeof(packet));
					pack.ph.type = PACKET_BROADCAST_USERX_SPAWN;
					Broadcast(pack);
					printf("\n ID : %hd �� �÷��̾� �������� ��ε�ĳ��Ʈ��, ", packet.ph.id);
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
