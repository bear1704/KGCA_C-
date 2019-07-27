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


	return true;
}

