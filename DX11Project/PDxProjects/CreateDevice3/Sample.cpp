#include "Sample.h"

Sample::Sample()
{
	
}

Sample::~Sample()
{

}


bool Sample::Init()
{
	
	//InitDevice(hWnd, g_rectangle_client.right, g_rectangle_client.bottom);
	//CreateRenderTarget(g_rectangle_client.right, g_rectangle_client.bottom);
	//DX::PDxState::SetState(device_);
	//obj.DXInit(device_, immediate_device_context_);
	obj.Init(device_, immediate_device_context_,L"character" ,L"character_move", L"VertexShader.hlsl", "VS", L"PixelShader.hlsl", "PS");


	return true;
}

bool Sample::Frame()
{
	obj.Frame();
	return true;
}

bool Sample::Render()
{
	obj.Render();
	
	return true;
}

bool Sample::Release()
{
	return true;
}