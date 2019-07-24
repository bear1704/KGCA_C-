#include "Sample.h"
#include "PEventSelect.h"

bool g_window_terminated;

Sample::Sample()
{
	timer = 0.0f;
	sound_flag = false;
	g_window_terminated = false;
}

Sample::~Sample()
{
	if(instruction_process_thread_.joinable())
		instruction_process_thread_.join();


}



bool Sample::Init()
{

	InitDataLoad();
	
	PInstructionProcessor* p = &PInstructionProcessor::GetInstance();
	instruction_process_thread_ = std::thread([&p]() {p->ProcessInstruction(); });

	PInstructionProcessor::GetInstance().BindScene(g_current_scene_);


	if (g_current_scene_)
		g_current_scene_->Init();

	// 1)초기화


	if (!m_Network.Init())
	{
		return false;
	}
	// 2)접속
	if (!m_Network.Connect("127.0.0.1", 10000, hWnd))
	{
		return false;
	}
	// 3)모델 선택
	m_Network.set_current_model(make_shared<PEventSelect>(m_Network.get_socket(), OperateMode::CLIENT));


	return true;
}
bool Sample::PreFrame()
{
	m_Network.Frame();
	//assert(false);
	return true;
}
bool Sample::Frame() {
	


	if (g_current_scene_)
		g_current_scene_->Frame();


	timer += g_SecondPerFrame;
	if (timer > 0.1f && !sound_flag)
	{
		PSoundMgr::GetInstance().Load(L"data/sound/map.mp3");
		PSoundMgr::GetInstance().GetPtr(0)->SetMode(2);
		PSound* bgm = PSoundMgr::GetInstance().GetPtr(0);
		bgm->Play();
		sound_flag = true;
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
	m_Network.Release(); 
	if (g_current_scene_)
		g_current_scene_->Release(); 

	g_window_terminated = true;
	PInstructionManager::GetInstance().NotifyProcessEvent();


	if(instruction_process_thread_.joinable())
		instruction_process_thread_.join();

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
	//실험용 초기화 -> 지연로드와 미리 로드의 속도차이 확인, 확장성있는 지연로드를 위하여

	PUIDataManager::GetInstance().LoadDataFromScript(L"data/UI/UI_composition_list.txt");
	PObjectDataManager::GetInstance().LoadDataFromScript(L"data/character/character_composition_list.txt");
	PScene* scene1 = new PScene();
	PUIComponent* uicomp_settingbar = PUIDataManager::GetInstance().get_ui_composition_list_from_map(L"MYSETTINGBTN");
	std::vector<PRectObject*> game_objects_ = PObjectDataManager::GetInstance().get_object_list_from_map(L"MUSHROOMLAND");

	scene1->InsertObject(uicomp_settingbar);
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
