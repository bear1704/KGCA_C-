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


	return true;
}

