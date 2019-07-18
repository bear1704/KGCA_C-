#include "Sample.h"
#include "PEventSelect.h"


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


	return true;
}
bool Sample::PreFrame()
{
	m_Network.Frame();
	return true;
}

