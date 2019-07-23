#include "PInstructionProcessor.h"
#include "resource.h"

HWND g_edit_name;
HWND g_hDlg;


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

	while (true)
	{
		//MessageBox(g_hWnd, L"proces", L"proces", MB_OK);
		std::unique_lock<std::mutex> ul(process_mutex_);
		PInstructionManager::GetInstance().process_event_.wait(ul, []()
			{return !PInstructionManager::GetInstance().IsQueueEmpty(); }); //큐가 비지 않았다면 실행

		//아래에 구현내용
		PACKET packet = PInstructionManager::GetInstance().PopBackInstruction();
		

		switch (packet.ph.type)
		{

			if(g_operate_mode == OperateMode::CLIENT) //클라
			{
				case PACKET_SC_TEST_HPDECREASE:
				{
					int dec = *(PacketMessage<int>)packet.msg;
					WORD id = packet.ph.id;
					PPlayerCharacter* obj = (PPlayerCharacter*)current_scene_->FindObjectById(id);
					obj->get_status().DecreaseHP(100);
					break;
				}
				case PACKET_SC_ID_PROVIDE:
				{
					WORD id = *((WORD*)packet.msg);
					//MessageBox(g_hWnd, std::to_wstring(id).c_str(), L"hi", MB_OK);
					PUserManager::GetInstance().oneself_user_.set_id(id);
					DialogBox(g_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, DlgProc);
				}
			}
			else if (g_operate_mode == OperateMode::SERVER)//서버
			{
				case PACKET_CS_LOGIN_SEND_USERNAME:
				{
					WORD id = packet.ph.id;
					PUser* user = PUserManager::GetInstance().FindUserById(id);
					std::string str(packet.msg);
					user->set_name(str);

					printf("\n 플레이어 id %hd 의 이름 %s 전송받음", id, user->get_name().c_str());

					int a = 4;
					PPacketManager::GetInstance().PushPacket(user, PACKET_SC_TEST_HPDECREASE, (char*)a, sizeof(int),
						PushType::SEND, false);

				}
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
