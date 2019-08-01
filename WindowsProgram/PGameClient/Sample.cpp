#include "Sample.h"
#include "PEventSelect.h"
#include "PNetworkTimer.h"

bool g_window_terminated;

Sample::Sample()
{
	timer = 0.0f;
	sound_flag = false;
	g_window_terminated = false;
	other_character_info_renew_counter_ = 0;
}

Sample::~Sample()
{


}



bool Sample::Init()
{

	InitDataLoad();
	
	PInstructionProcessor* p = &PInstructionProcessor::GetInstance();
	instruction_process_thread_ = std::thread([&p]() {p->ProcessInstruction(); });
	client_task_thread_ = std::thread([&p]() {p->ProcessClientTask(); });

	PInstructionProcessor::GetInstance().BindScene(g_current_scene_);


	if (g_current_scene_)
		g_current_scene_->Init();

	// 1)초기화


	if (!m_Network.Init())
	{
		return false;
	}
	// 2)접속
	if (!m_Network.Connect("192.168.0.124", 10000, hWnd))
	{
		return false;
	}
	// 3)모델 선택
	m_Network.set_current_model(make_shared<PEventSelect>(m_Network.get_socket(), OperateMode::CLIENT));

	PNetworkTimer::GetInstance().Init();

	return true;
}
bool Sample::PreFrame()
{
	m_Network.Frame();
	//assert(false);

	if (g_custom_tick && PInstructionProcessor::GetInstance().get_loading_end())
	{
		if (PNetworkDataStorage::GetInstance().is_b_need_report())
		{
			g_custom_tick = false;
			PNetworkDataStorage::GetInstance().set_b_need_report(false);
			PInstructionProcessor::GetInstance().ReportPositionMsg();
		}
		other_character_info_renew_counter_++;


		/*if (other_character_info_renew_counter_ > 15)
		{
			std::vector<PUser*>& userlist = PUserManager::GetInstance().user_list_;
			for (auto iter = userlist.begin(); iter != userlist.end(); iter++)
			{
				PUser* user = *iter;

				if (user->get_connected() == false)
				{
					g_current_scene_->DeleteGameObjectsByCid(user->get_character_id());
					PUserManager::GetInstance().DeleteUser(user);
				}

			}

			other_character_info_renew_counter_ = 0;


		}*/ //플레이어 퇴장할때 캐릭터 지우는 코드. 넘실거리는 버그로 일단 봉인조치

	}

	

	return true;
}
bool Sample::Frame() {
	


	if (g_current_scene_)
		g_current_scene_->Frame();


	timer += g_SecondPerFrame;
	if (timer > 0.1f && !sound_flag)
	{
		PSoundMgr::GetInstance().Load(L"data/sound/bgm.mp3");
		PSoundMgr::GetInstance().GetPtr(0)->SetMode(2);
		PSound* bgm = PSoundMgr::GetInstance().GetPtr(0);
		bgm->Play();
		sound_flag = true;
	}

	if (PInstructionProcessor::GetInstance().boss_spawn_)
	{
		PBossMonster* pbm = (PBossMonster*)g_current_scene_->FindObjectByCid(ZAKUM_ID);
		PPlayerCharacter* mychar = (PPlayerCharacter*)g_current_scene_->FindObjectByCid(PUserManager::GetInstance().oneself_user_.get_character_id());

		if (PCollision::GetInstance().RectInRect(mychar->get_collision_rect_(), pbm->get_collision_rect_()))
		{
			mychar->set_hit_(true);
			PACKET* pack = new PACKET;
			ZeroMemory(pack, sizeof(PACKET));
			pack->ph.id = PUserManager::GetInstance().oneself_user_.get_id();
			pack->ph.type = PACKET_CS_IM_HIT;
			pack->ph.len = sizeof(WORD) + PACKET_HEADER_SIZE;

			WORD cid = mychar->get_id();
			memcpy(pack->msg, &cid, sizeof(WORD));

			PPacketManager::GetInstance().PushPacket(PushType::SEND, *pack); //내가 맞았음을 서버에 보고

			

			delete pack;
		}
	}

	
	PInstructionManager::GetInstance().NotifyProcessEvent();
	PPacketManager::GetInstance().NotifyProcessEvent();
	return true;
}

bool Sample::Render()
{


	if (g_current_scene_)
		g_current_scene_->Render();

	return true;

}

bool Sample::Release() 
{
	g_window_terminated = true;
	PInstructionManager::GetInstance().NotifyProcessEvent();

	if (instruction_process_thread_.joinable())
		instruction_process_thread_.join();

	if (client_task_thread_.joinable())
		client_task_thread_.join();

	m_Network.Release(); 
	if (g_current_scene_)
		g_current_scene_->Release(); 



	

	return true; 
}



void Sample::draw_test_rect(FLOAT_RECT rect)
{

	SetROP2(g_handle_off_screenDC, R2_NOTXORPEN);
	FLOAT_RECT arect = P2DCamera::GetInstance().WorldToGamescreenRECT(rect);
	int prevMode2 = Rectangle(g_handle_off_screenDC, arect.left, arect.top,
		arect.left + arect.right, arect.top + arect.bottom);
	SetROP2(handle_off_screenDC, prevMode2);
}

bool Sample::InitDataLoad()
{

	

	PObjectInfoManager::GetInstance().LoadDataFromScript(L"data/UI/UI_data.txt", ObjectLoadType::UI);
	PObjectInfoManager::GetInstance().LoadDataFromScript(L"data/character/character_data.txt", ObjectLoadType::CHARACTER);
	PObjectInfoManager::GetInstance().LoadDataFromScript(L"data/map/map_data.txt", ObjectLoadType::MAP);
	PSpriteManager::GetInstance().LoadSpriteDataFromScript(L"data/UI/sprite/dmgfont/sprite.txt", ObjectLoadType::ETC_SPRITE);
	//실험용 초기화 -> 지연로드와 미리 로드의 속도차이 확인, 확장성있는 지연로드를 위하여

	PUIDataManager::GetInstance().LoadDataFromScript(L"data/UI/UI_composition_list.txt");
	PObjectDataManager::GetInstance().LoadDataFromScript(L"data/character/character_composition_list.txt");
	PScene* scene1 = new PScene();
	PUIComponent* uicomp_settingbar = PUIDataManager::GetInstance().get_ui_composition_list_from_map(L"MYSETTINGBTN");
	std::vector<PRectObject*> game_objects_ = PObjectDataManager::GetInstance().get_object_list_from_map(L"MUSHROOMLAND");

	PUIComponent* uicomp_bossbar = PUIDataManager::GetInstance().get_ui_composition_list_from_map(L"BOSS_HPBAR");
	scene1->InsertObject(uicomp_settingbar);
	scene1->InsertObject(uicomp_bossbar);
	scene1->InsertObject(game_objects_);
	scene1->set_scene_name_(L"MUSHROOMLAND");

	g_current_scene_ = scene1;
	


	//PSoundMgr::GetInstance().Play(PSoundMgr::GetInstance().Load(L"data/sound/extree.mp3"));
	//PSoundMgr::GetInstance().Play(PSoundMgr::GetInstance().Load(L"data/sound/extree_die.mp3"));

	//DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), HWND_DESKTOP, DlgProc);

	//std::thread aaa(PInstructionProcessor::GetInstance().ProcessInstruction);


	

	return true;
}

PCORE_RUN(L"MapleStory", 0, 0, 1024, 768);
