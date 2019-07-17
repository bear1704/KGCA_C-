#include "Sample.h"
#include "PEventSelect.h"

Sample::Sample()
{
	g_current_scene_ = nullptr;
}

Sample::~Sample()
{

}

bool Sample::Init()
{
	// window api control
	DWORD style = WS_CHILD | WS_VISIBLE | ES_MULTILINE;
	m_hEdit = CreateWindow(L"edit", NULL, style,
		420, 100, 200, 100, hWnd, (HMENU)100,
		hInstance, NULL);

	style = WS_CHILD | WS_VISIBLE;
	m_hButton = CreateWindow(L"button", L"Send", style,
		630, 100, 100, 100, hWnd, (HMENU)200,
		hInstance, NULL);

	style = WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL;
	m_hList = CreateWindow(L"listbox", NULL, style,
		10, 10, 400, 500, hWnd, (HMENU)300,
		hInstance, NULL);

	SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)L"채팅시작합니다.");
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
	m_Network.set_current_model(make_shared<PEventSelect>(m_Network.get_socket()));

	//PPacketManager::GetInstance().RunPacketProcess(&(m_Network.get_socket()));

	return true;
}
bool Sample::PreFrame()
{
	m_Network.Frame();
	PacketProcess();
	return true;
}
bool Sample::Frame() { return true; }
bool Sample::Release() { m_Network.Release(); return true; }
bool Sample::PostRender() { return true; }
bool Sample::PacketProcess(){ return true; }

PCORE_RUN(L"abba", 0, 0, 800, 600);