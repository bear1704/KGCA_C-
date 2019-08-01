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

	std::cout << "서버 시작됨\n" << std::endl;
	// 1)초기화


	if (!m_Network.Init())
	{
		return false;
	}
	// 2)접속
	if (m_Network.BindListen() == false)
	{
		return false;
	}
	// 3)모델 선택
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

	if (g_skill_time)
	{
		g_skill_time = false;
		//대충 0~1사이의 랜덤값을 출력하는 코드
		
		std::random_device r;
		std::mt19937 engine(r());
		std::uniform_int_distribution<int> distribution(300, 500);
		std::uniform_int_distribution<int> distribution2(-1000, -500);
		std::uniform_int_distribution<int> r_num(0, 1);
		auto generator = std::bind(distribution, engine);
		auto generator2 = std::bind(distribution2, engine);
		auto generator3 = std::bind(r_num, engine);

		int randnum = generator3();


		if (randnum == 0)
		{

			MeteorRandNumberForPacket data;
			data.skillnum = randnum;

			for (int i = 0; i < 8; i++)
			{
				int num1 = generator2();
				int num2 = generator();
				data.initpos[i] = num1;
				data.downspeed[i] = num2;
			}

			PACKET pack;
			pack.ph.id = SERVER_ID;
			pack.ph.type = PACKET_BROADCAST_METEOR_ACTIVE;
			pack.ph.len = PACKET_HEADER_SIZE + sizeof(MeteorRandNumberForPacket);
			memcpy(pack.msg, &data, sizeof(MeteorRandNumberForPacket));


			PServerInstructionProcessor::GetInstance().Broadcast(pack);
			printf("\n 스킬 발동 : %d번", data.skillnum);
		}
		else if (randnum == 1)
		{
			std::uniform_int_distribution<int> goddess_rand(0,5);
			auto gen = std::bind(goddess_rand, engine);
			WORD num = gen();

			PACKET pack;
			pack.ph.id = SERVER_ID;
			pack.ph.type = PACKET_BROADCAST_ALLATTACK_ACTIVE;
			pack.ph.len = PACKET_HEADER_SIZE + sizeof(WORD);


			memcpy(pack.msg, &num, sizeof(WORD));
			PServerInstructionProcessor::GetInstance().Broadcast(pack);
			printf("\n 스킬 발동 : %d번", randnum);
		}

	}

	PServerInstructionProcessor::GetInstance().Frame();
	return true;
}

