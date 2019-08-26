#include "Sample.h"

Sample::Sample()
{
	
}

Sample::~Sample()
{

}


bool Sample::Init()
{
	InitDevice(hWnd, g_rectangle_client.right, g_rectangle_client.bottom);
	CreateRenderTarget(g_rectangle_client.right, g_rectangle_client.bottom);
	DX::PDxState::SetState(device_);
	obj.DXInit(device_, immediate_device_context_);
	return true;
}

bool Sample::Frame()
{
	obj.Frame();
	return true;
}

bool Sample::Render()
{
	DevicePreRender();
	DX::ApplyRasterizerState(immediate_device_context_, DX::PDxState::rs_state_solidframe_);
	obj.Render(immediate_device_context_);
	swap_chain_->Present(0, 0);
	return true;
}

bool Sample::Release()
{
	return true;
}