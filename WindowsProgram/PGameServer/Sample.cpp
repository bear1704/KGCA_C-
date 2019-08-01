#include "Sample.h"
#include "PEventSelect.h"

bool g_window_terminated;

int main()
{
	Sample sample;
	sample.Init();
	while (true)
	{
		sample.PreFrame();
	}

}

Sample::Sample()
{
	g_window_terminated = false;
	
}

Sample::~Sample()
{

}

bool Sample::Init()
{


	PScene* server_scene = new PScene();
	g_current_scene_ = server_scene;

	PObjectInfoManager::GetInstance().Init();
	PObjectDataManager::GetInstance().Init();
	PObjectInfoManager::GetInstance().LoadDataFromScript(L"data/character_data.txt", ObjectLoadType::CHARACTER);
	PObjectDataManager::GetInstance().LoadDataFromScript(L"data/character_composition_list.txt");
	std::vector<PRectObject*> game_objects_ = PObjectDataManager::GetInstance().get_object_list_from_map(L"ZAKUM_TEMPLE");
	
	g_current_scene_->InsertObject(game_objects_);


	PObjectInfoManager::GetInstance().Init();
	PObjectDataManager::GetInstance().Init();
	PSpriteManager::GetInstance().Init();
	PServerInstructionProcessor::GetInstance().Init();

	std::cout << "���� ���۵�\n" << std::endl;
	// 1)�ʱ�ȭ


	if (!m_Network.Init())
	{
		return false;
	}
	// 2)����
	if (m_Network.BindListen() == false)
	{
		return false;
	}
	// 3)�� ����
	m_Network.set_current_model(make_shared<PEventSelect>(m_Network.get_listen_sock(), OperateMode::SERVER));

	PServerInstructionProcessor* p = &PServerInstructionProcessor::GetInstance();
	instruction_process_thread_ = std::thread([&p]() {p->ProcessInstruction(); });

	PNetworkTimer::GetInstance().Init();
	return true;
}
bool Sample::PreFrame()
{
	m_Network.Frame();

	if (g_custom_tick)
	{
		g_custom_tick = false;
	}

	PServerInstructionProcessor::GetInstance().Frame();
	return true;
}

