#include "PInstructionProcessor.h"
#include "resource.h"

HWND g_edit_name;
HWND g_hDlg;

std::mutex PInstructionProcessor::process_mutex_;
std::mutex PInstructionProcessor::spawn_mutex_;

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
			{return !PInstructionManager::GetInstance().IsQueueEmpty() || g_window_terminated; }); //큐가 비지 않았다면 실행


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
					//PPlayerCharacter* obj = (PPlayerCharacter*)current_scene_->FindObjectById(id);
					//아직 캐릭터에 ID를 부여하지 않았음!!!
					//obj->get_status().DecreaseHP(100);
					break;
				}
				case PACKET_SC_ID_PROVIDE:
				{
					//MessageBox(g_hWnd, L"provide", L"PROVIDE", MB_OK);
					
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
					break;
				}
		}

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
		
		current_scene_->AddGameObjects(component);
	}
	return;
}

void PInstructionProcessor::SpawnOtherPlayer(pPoint& pos, WORD id)
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
		component->set_id(id);
		component->Init();

		current_scene_->AddGameObjects(component);
	}
	return;
}
