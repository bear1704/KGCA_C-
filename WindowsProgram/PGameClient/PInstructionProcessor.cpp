#include "PInstructionProcessor.h"
#include "resource.h"

HWND g_edit_name;
HWND g_hDlg;

std::mutex PInstructionProcessor::process_mutex_;
std::mutex PInstructionProcessor::spawn_mutex_;
std::mutex PInstructionProcessor::client_mutex_;

LRESULT CALLBACK DlgProc(HWND hDlg,
	UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
	{
		g_hDlg = hDlg;
		g_edit_name = GetDlgItem(hDlg, IDC_NAMEEDIT);
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			TCHAR Name[16] = { 0, };
			SendMessage(g_edit_name, WM_GETTEXT, 16, (LPARAM)Name);
			std::wstring name(Name);
			std::string mstr = unicode_to_multibyte_str(name);

			char name_[16] = { 0, };
			WideCharToMultiByte(CP_ACP, 0, Name, lstrlenW(Name), name_, lstrlenW(Name), NULL, NULL);

			PUser* myuser = &(PUserManager::GetInstance().oneself_user_);
			PPacketManager::GetInstance().PushPacket(myuser, PACKET_CS_LOGIN_SEND_USERNAME,
				(char*)name_, mstr.length(), PushType::SEND, true);


			PUserManager::GetInstance().oneself_user_.set_name(mstr); //중복처리없음, 사실상바로수용 
			EndDialog(hDlg, IDOK);

		}break;
		}
	}
	return 0;
	}
}


PInstructionProcessor::PInstructionProcessor()
{
	loading_end_ = false;
}


PInstructionProcessor::~PInstructionProcessor()
{
}


void PInstructionProcessor::BindScene(PScene * current_scene) 
{
	current_scene_ = current_scene;
}

void PInstructionProcessor::ProcessInstruction()
{
	while (g_window_terminated == false)
	{
		//MessageBox(g_hWnd, L"proces", L"proces", MB_OK);
		std::unique_lock<std::mutex> ul(process_mutex_);
		PInstructionManager::GetInstance().process_event_.wait(ul, []()
			{return !PInstructionManager::GetInstance().IsQueueEmpty() && !g_window_terminated; }); //큐가 비지 않았다면 실행


		if (g_window_terminated == true)
			break;

		//아래에 구현내용
		PACKET packet = PInstructionManager::GetInstance().PopBackInstruction();
		

		switch (packet.ph.type)
		{			
				case PACKET_SC_TEST_HPDECREASE:
				{
					int dec = *(PacketMessage<int>)packet.msg;
					WORD id = packet.ph.id;
					PPlayerCharacter* obj = (PPlayerCharacter*)current_scene_->FindObjectByCid(id);
					obj->get_status().DecreaseHP(100);
					break;
				}
				case PACKET_SC_ID_PROVIDE:
				{
					
					WORD id = *((WORD*)packet.msg);
					PUserManager::GetInstance().oneself_user_.set_id(id);
					DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, DlgProc);
					break;
				}
				case PACKET_SC_SPAWN_CHARACTER: //캐릭터 스폰시키고 캐릭터 고유 아이디 부여
				{
					PKT_MSG_SPAWN pos_msg;
					memcpy(&pos_msg, packet.msg, packet.ph.len - PACKET_HEADER_SIZE);

					pPoint pos = pPoint(pos_msg.posx, pos_msg.posy);
					SpawnPlayer(pos, pos_msg.id);
					

					char msg[sizeof(PKT_MSG_SPAWN)];
					memcpy(msg, &pos_msg, sizeof(PKT_MSG_SPAWN));
					PPacketManager::GetInstance().PushPacket(&PUserManager::GetInstance().oneself_user_, 
						PACKET_CS_SPAWN_COMPLETE,
						msg, sizeof(PKT_MSG_SPAWN), PushType::SEND, true);

					loading_end_ = true;

					break;

				}
				case PACKET_BROADCAST_USERX_SPAWN:
				{
					PKT_MSG_SPAWN broad_msg;
					memcpy(&broad_msg, packet.msg, sizeof(PKT_MSG_SPAWN));
					
					if (broad_msg.id == PUserManager::GetInstance().oneself_user_.get_character_id())
						break;  //스폰 브로드캐스트 객체가 자신의 캐릭터 iD이면, 스폰할 필요 없다.
										
					pPoint pos = pPoint(broad_msg.posx, broad_msg.posy);
					SpawnOtherPlayer(pos, broad_msg.id);
					PUserManager::GetInstance().AddUserSimpleType(packet.ph.id, broad_msg.id); //클라 유저리스트에 유저추가

					break;
				}
				case PACKET_BROADCAST_USERX_MOVEAXIS_AtoB:
				{
					PKT_MSG_REGULAR_POS_REPORT report_msg;
					ZeroMemory(&report_msg, sizeof(PKT_MSG_REGULAR_POS_REPORT));
					memcpy(&report_msg, packet.msg, sizeof(PKT_MSG_REGULAR_POS_REPORT));

					if (report_msg.cid == PUserManager::GetInstance().oneself_user_.get_character_id())
						break;

					PPlayerCharacter* userx_character = (PPlayerCharacter*)current_scene_->FindObjectByCid(report_msg.cid);

					if (userx_character == nullptr) //늦게 들어온 플레이어는 other_spawn 처리를 못했으므로 없을 것이다.
					{
						//그래서 이전까지 플레이어를 만들어준다.
						pPoint other_player_pos = pPoint(report_msg.posx, report_msg.posy);
						SpawnOtherPlayer(other_player_pos, report_msg.cid);
						userx_character = (PPlayerCharacter*)current_scene_->FindObjectByCid(report_msg.cid);
					}

					userx_character->set_position_(pPoint(report_msg.posx, report_msg.posy));

					userx_character->SetTransition(FsmStateToFsmEvent(report_msg.current_state));
					
					if (report_msg.dir == Direction::RIGHT)
						userx_character->set_right_dir(true);
					else
						userx_character->set_right_dir(false);

					break;
				}
				case PACKET_SC_SPAWN_BOSS:
				{
					PKT_MSG_SPAWN spawn_msg;
					ZeroMemory(&spawn_msg, sizeof(PKT_MSG_SPAWN));
					memcpy(&spawn_msg, packet.msg, sizeof(PKT_MSG_SPAWN));

					pPoint boss_pos = pPoint(spawn_msg.posx, spawn_msg.posy);
					
					SpawnBossMonster(boss_pos, spawn_msg.id);
					break;
				}
		}

	}

}

void PInstructionProcessor::ProcessClientTask()
{
	while (g_window_terminated == false)
	{
		
		std::unique_lock<std::mutex> ul(client_mutex_);
		PInstructionManager::GetInstance().process_event_.wait(ul, []()
			{return !PNetworkDataStorage::GetInstance().IsQueueEmpty() && !g_window_terminated; }); //큐가 비지 않았다면 실행

		HitData data = PNetworkDataStorage::GetInstance().PopData();
		


	}
}

bool PInstructionProcessor::Init()
{
	return false;
}

bool PInstructionProcessor::Frame()
{
	return false;
}

bool PInstructionProcessor::Render()
{
	return false;
}

bool PInstructionProcessor::Release()
{
	return false;
}

void PInstructionProcessor::SpawnPlayer(pPoint& pos, WORD id)
{
	std::lock_guard<std::mutex> lk(spawn_mutex_);
	{
		PPlayerCharacter* component;
		component = new PPlayerCharacter();
		component->Set(path, L"player", pPoint(pos.x, pos.y));
		PObjectDataManager::GetInstance().LoadAnimationDataFromScriptEx(animation_path); //캐릭터 스프라이트 선행 로드 후에 위치해야 함.
		component->set_gravity_(450.0f);
		component->set_type_(Type::PLAYER);
		component->StatusSet(status_path, component->get_object_name());
		component->set_animation_list_(PObjectDataManager::GetInstance().get_animation_list_from_map(L"player"));
		component->set_alpha_and_scale_(component->get_alpha_(), component->get_scale_());
		component->set_client_owner_character(true);
		current_scene_->set_target(component);
		component->set_id(id);
		PUserManager::GetInstance().oneself_user_.set_character_id(id);
		component->Init();
		my_character_ = component;

		current_scene_->AddGameObjects(component);
	}
	return;
}

void PInstructionProcessor::SpawnOtherPlayer(pPoint& pos, WORD cid)
{
	std::lock_guard<std::mutex> lk(spawn_mutex_);
	{
		PPlayerCharacter* component;
		component = new PPlayerCharacter();
		component->Set(path, L"other_player", pPoint(pos.x, pos.y));
		PObjectDataManager::GetInstance().LoadAnimationDataFromScriptEx(animation_path); //캐릭터 스프라이트 선행 로드 후에 위치해야 함.
		component->set_gravity_(450.0f);
		component->set_type_(Type::OTHER_PLAYER);
		component->StatusSet(status_path, component->get_object_name());
		component->set_animation_list_(PObjectDataManager::GetInstance().get_animation_list_from_map(L"other_player"));
		component->set_alpha_and_scale_(component->get_alpha_(), component->get_scale_());
		component->set_client_owner_character(false);
		current_scene_->set_target(component);
		component->set_id(cid);
		component->Init();

		current_scene_->AddGameObjects(component);
	}
	return;
}

void PInstructionProcessor::SpawnBossMonster(pPoint& pos, WORD id)
{

	std::lock_guard<std::mutex> lk(spawn_mutex_);
	{
		PBossMonster* component;
		component = new PBossMonster();
		component->Set(path, L"zakum", pPoint(pos.x, pos.y));
		PObjectDataManager::GetInstance().LoadAnimationDataFromScriptEx(animation_path); //캐릭터 스프라이트 선행 로드 후에 위치해야 함.
		//component->set_gravity_(450.0f);
		component->set_type_(Type::BOSS_MONSTER);
		component->StatusSet(status_path, component->get_object_name());
		component->set_animation_list_(PObjectDataManager::GetInstance().get_animation_list_from_map(L"zakum"));
		component->set_alpha_and_scale_(component->get_alpha_(), component->get_scale_());
		component->set_id(id);
		component->Init();

		current_scene_->AddGameObjects(component);
	}
	return;
}

void PInstructionProcessor::ReportPositionMsg()
{
	PACKET packet;
	packet.ph.id = PUserManager::GetInstance().oneself_user_.get_id();
	packet.ph.len = sizeof(PKT_MSG_REGULAR_POS_REPORT) + PACKET_HEADER_SIZE;
	packet.ph.type = PACKET_CS_REPORT_MYPOSITION;
	PKT_MSG_REGULAR_POS_REPORT posmsg;
	posmsg.cid = PUserManager::GetInstance().oneself_user_.get_character_id();
	PPlayerCharacter* pp = (PPlayerCharacter*)g_current_scene_->FindObjectByCid(posmsg.cid);
	posmsg.current_state = pp->current_player_state_;
	posmsg.posx = pp->get_position_().x;
	posmsg.posy = pp->get_position_().y;

	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD)
		posmsg.dir = Direction::LEFT;
	else if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
		posmsg.dir = Direction::RIGHT;

	memcpy(packet.msg, &posmsg, sizeof(PKT_MSG_REGULAR_POS_REPORT));

	PPacketManager::GetInstance().PushPacket(PushType::SEND, packet);
}

const bool& PInstructionProcessor::get_loading_end()
{
	return loading_end_;
}
