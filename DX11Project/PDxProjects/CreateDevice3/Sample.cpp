#include "Sample.h"

Sample::Sample()
{
	
}

Sample::~Sample()
{

}


bool Sample::Init()
{

	obj_.Init(device_, immediate_device_context_, L"VertexShader.hlsl", "VS", L"PixelShader.hlsl", "PS", L"aaa");
	box_.Init(device_, immediate_device_context_, L"VertexShader.hlsl", "VS", L"PixelShader.hlsl", "PS", L"terrain");
	map_.Init(device_, immediate_device_context_);

	D3DXMatrixIdentity(&mat_obj_world_);
	D3DXMatrixIdentity(&mat_box_world_);

	//backview_camera_.Init();
	free_camera_.Init();

	D3DXVECTOR3 eye(0.0f, 0.0f, -2.0f);
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	//backview_camera_.CreateTargetViewMatrix(eye, at, up);
	//backview_camera_.CreateProjectionMatrix();

	free_camera_.CreateTargetViewMatrix(eye, at, up);
	free_camera_.CreateProjectionMatrix();

	D3DXMatrixRotationY(&mat_box_world_, D3DX_PI / 2.5);
	mat_obj_world_._42 = 1.0f;
	mat_box_world_._42 = 1.0f;

	main_camera_ = &free_camera_;


	PMapDesc md;
	md.vertex_cols = 257;
	md.vertex_rows = 257;
	md.cell_disatnce = 1;
	md.vs_path = L"VertexShader.hlsl";
	md.vs_func = "VS";
	md.ps_path = L"PixelShader.hlsl";
	md.ps_func = "PS";
	md.texture_name = L"bk";

	if (!map_.Load(md))
		assert(false);


	return true;
}

bool Sample::Frame()
{

	if (g_InputActionMap.qKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->UpWard();
	}
	if (g_InputActionMap.eKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->DownWard();
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
	obj_.Frame();
	box_.Frame();
	map_.Frame();
	return true;
}

bool Sample::Render()
{
	

	obj_.SetWVPMatrix(&mat_obj_world_, &main_camera_->matView_, &main_camera_->matProj_);
	obj_.Render();
	box_.SetWVPMatrix(&mat_box_world_, &main_camera_->matView_, &main_camera_->matProj_);
	box_.Render();
	map_.SetWVPMatrix(nullptr, &main_camera_->matView_, &main_camera_->matProj_);
	map_.Render();

	return true;
}

bool Sample::Release()
{
	obj_.Release();
	box_.Release();
	map_.Render();

	return true;
}

void Sample::MessageProc(MSG msg)
{
	PCore::MessageProc(msg);
	//PInput::GetInstance().MsgProc(msg);
	if (main_camera_ == nullptr) return;
	main_camera_->MessageProc(msg);
}
