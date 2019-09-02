#include "Sample.h"

Sample::Sample()
{
	
}

Sample::~Sample()
{

}


bool Sample::Init()
{
	

	obj.Init(device_, immediate_device_context_, L"VertexShader.hlsl", "VS", L"PixelShader.hlsl", "PS", L"aaa", L"");
	mat_obj_world_.Identity();

	backview_camera_.Init();

	DX::Vector3 eye(0.0f, 0.0f, -2.0f);
	DX::Vector3 at(0.0f, 0.0f, 0.0f);
	DX::Vector3 up(0.0f, 1.0f, 0.0f);

	backview_camera_.CreateTargetViewMatrix(eye, at, up);
	backview_camera_.CreateProjectionMatrix();

	main_camera_ = &backview_camera_;

	return true;
}

bool Sample::Frame()
{

	if (g_InputActionMap.wKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->Forward();
	}
	if (g_InputActionMap.sKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->BackWard();
	}
	if (g_InputActionMap.aKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->MoveLeft();
	}
	if (g_InputActionMap.dKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->MoveRight();
	}
	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateLeft();
	if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateRight();
	if (g_InputActionMap.upArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateUp();
	if (g_InputActionMap.downArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateDown();



	main_camera_->Frame();
	obj.Frame();
	return true;
}

bool Sample::Render()
{
	obj.SetWVPMatrix(nullptr, &main_camera_->matView_, &main_camera_->matProj_);
	obj.Render();
	
	return true;
}

bool Sample::Release()
{
	return true;
}