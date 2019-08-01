#include "PServerInstructionProcessor.h"

std::mutex PServerInstructionProcessor::process_mutex1_;
bool PServerInstructionProcessor::init_ok_ = false;

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
					auto generator = std::bind(distribution, engine); 
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

					PPlayerCharacter* user_character = new PPlayerCharacter();
					user_character->set_id(random);
					g_current_scene_->get_game_objects()->push_back(user_character);
					

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
					PACKET* pack = new PACKET;
					ZeroMemory(pack, sizeof(PACKET));
					memcpy(pack, &packet, sizeof(packet));
					pack->ph.type = PACKET_BROADCAST_USERX_SPAWN;
					Broadcast(*pack);
					printf("\n [브로드캐스트] ID : %hd 인 플레이어 스폰 ", packet.ph.id);

					PACKET* boss_pack = new PACKET;
					ZeroMemory(boss_pack, sizeof(PACKET));
					PKT_MSG_SPAWN spawn_msg;
					spawn_msg.id = ZAKUM_ID;
					PBossMonster* pbm = (PBossMonster*) g_current_scene_->FindObjectByCid(ZAKUM_ID);
					spawn_msg.posx = pbm->get_position_().x;
					spawn_msg.posy = pbm->get_position_().y; //hard_coded

					memcpy(boss_pack->msg, &spawn_msg, sizeof(PKT_MSG_SPAWN));
					boss_pack->ph.type = PACKET_SC_SPAWN_BOSS;
					boss_pack->ph.len = sizeof(PKT_MSG_SPAWN) + PACKET_HEADER_SIZE;
					boss_pack->ph.id = pack->ph.id;

					PPacketManager::GetInstance().PushPacket(PushType::SEND, *boss_pack);

					delete boss_pack;
					delete pack;
					init_ok_ = true;
					break;
				}
				case PACKET_CS_REPORT_MYPOSITION:
				{
					PACKET* pkt = new PACKET;
					ZeroMemory(pkt, sizeof(PACKET));
					pkt->ph.type = PACKET_BROADCAST_USERX_MOVEAXIS_AtoB;
					pkt->ph.len = sizeof(PKT_MSG_REGULAR_POS_REPORT) + PACKET_HEADER_SIZE;
					pkt->ph.id = 0;
					memcpy(pkt->msg, packet.msg, sizeof(PKT_MSG_REGULAR_POS_REPORT));
					Broadcast(*pkt);

					WORD id = packet.ph.id;
					PUser* user = PUserManager::GetInstance().FindUserById(id);
					if (user == nullptr)
						break;

					PKT_MSG_REGULAR_POS_REPORT* report_msg = new PKT_MSG_REGULAR_POS_REPORT;
					ZeroMemory(report_msg, sizeof(PKT_MSG_REGULAR_POS_REPORT));
					memcpy(report_msg, packet.msg, sizeof(PKT_MSG_REGULAR_POS_REPORT));
					std::string dir; std::string state;
					dir = (report_msg->dir == Direction::LEFT) ? "LEFT" : "RIGHT";
					state = FsmStateToString(report_msg->current_state);


					PPlayerCharacter* character = (PPlayerCharacter*)g_current_scene_->FindObjectByCid(user->get_character_id());
					character->set_position_(pPoint(report_msg->posx, report_msg->posy));
					FLOAT_RECT norm_box = { 0,0,53,77 };
					character->set_collision_box_norm(norm_box);
					character->set_collision_box_(norm_box);

					//printf("\n [브로드캐스트] ID : %hd 인 패킷의 좌표 X: %f, Y: %f DIR : %s  STATE : %s", 
					//	packet.ph.id, report_msg.posx, report_msg.posy, dir.c_str(), state.c_str());


					delete pkt;
					delete report_msg;
					break;
				}
				case PACKET_CS_MONSTER_HIT:
				{
					PKT_MSG_MONSTER_HIT* pmmh = new PKT_MSG_MONSTER_HIT;
					ZeroMemory(pmmh, sizeof(PKT_MSG_MONSTER_HIT));
					memcpy(pmmh, packet.msg, sizeof(PKT_MSG_MONSTER_HIT));
					PBossMonster* bm = (PBossMonster*)g_current_scene_->FindObjectByCid(pmmh->monster_id);
					bm->get_status().DecreaseHP(pmmh->damage);


					PACKET* pkt = new PACKET;
					pkt->ph.id = pmmh->player_user_id;
					pkt->ph.len = PACKET_HEADER_SIZE + sizeof(PKT_MSG_MONSTER_HIT);
					pkt->ph.type = PACKET_BROADCAST_USERX_ATTACK_SUCCESS;
					memcpy(pkt->msg, pmmh, sizeof(PKT_MSG_MONSTER_HIT));

					Broadcast(*pkt);

					PACKET hp_pack;
					ZeroMemory(&hp_pack, sizeof(PACKET));
					hp_pack.ph.id = pmmh->player_user_id;
					hp_pack.ph.type = PACKET_SC_BOSS_REAMIN_HP;
					hp_pack.ph.len = PACKET_HEADER_SIZE + sizeof(int);
					int remain_hp = bm->get_status().get_hp_();
					memcpy(hp_pack.msg, &remain_hp, sizeof(int));

					PPacketManager::GetInstance().PushPacket(PushType::SEND, hp_pack);

					delete pkt;
					delete pmmh;
					break;
				}
				case PACKET_CS_IM_HIT:
				{
					WORD cid;
					memcpy(&cid, packet.msg, sizeof(WORD));
					PACKET* hitpack = new PACKET;
					hitpack->ph.id = SERVER_ID;
					hitpack->ph.type = PACKET_BROADCAST_USERX_HIT;
					hitpack->ph.len = sizeof(WORD) + PACKET_HEADER_SIZE;
					memcpy(hitpack->msg, &cid, sizeof(WORD));
					Broadcast(*hitpack);

					delete hitpack;
				
					break;
				}
		}

	}

}

bool PServerInstructionProcessor::Init()
{
	init_ok_ = false;
	return true;
}

bool PServerInstructionProcessor::Frame()
{

	//if (init_ok_)
	//{
	//	PBossMonster* pbm = (PBossMonster*)g_current_scene_->FindObjectByCid(ZAKUM_ID);


	//	for (PUser* user : PUserManager::GetInstance().user_list_)
	//	{
	//		PPlayerCharacter* player = (PPlayerCharacter*)g_current_scene_->FindObjectByCid(user->get_character_id());


	//		if (PCollision::GetInstance().RectInRect(player->get_collision_rect_(), pbm->get_collision_rect_()))
	//		{  //플레이어와의 충돌 체크 
	//			player->set_hit_(true);
	//		}
	//	}
	//}
	return true;

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

	for (PUser* iter : userlist)
	{
			PPacketManager::GetInstance().PushPacket(iter, packet.ph.type, packet.msg, packet.ph.len - PACKET_HEADER_SIZE,
				PushType::SEND, true);
		
	}

	return false;
}
