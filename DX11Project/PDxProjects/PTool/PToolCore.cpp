#include "pch.h"
#include "PToolCore.h"


PToolCore::PToolCore()
{

}

PToolCore::~PToolCore()
{
}

bool PToolCore::Init()
{
	
	ZeroMemory(&blend_desc_, sizeof(D3D11_BLEND_DESC));
	blend_desc_.AlphaToCoverageEnable = FALSE;
	blend_desc_.IndependentBlendEnable = TRUE;
	blend_desc_.RenderTarget[0].BlendEnable = TRUE;
	blend_desc_.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blend_desc_.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blend_desc_.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;

	blend_desc_.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blend_desc_.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blend_desc_.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;

	blend_desc_.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = device()->CreateBlendState(&blend_desc_, &blend_state_);
	if (FAILED(hr))
		assert(false);

	//plane_list_.reserve(1024);


	PSpriteManager::GetInstance().LoadSpriteDataFromScript(L"data/sprite.txt", ObjectLoadType::ETC_SPRITE);
	screen_tex_object_.Init(device_, immediate_device_context_, L"VertexShader.hlsl", "VS", L"PixelShader.hlsl", "PS", L"blue");
	skybox_.Init(device_, immediate_device_context_, L"Skybox.hlsl", "VS", L"Skybox.hlsl", "PS");

	//plane_.Init(device_, immediate_device_context_, L"VertexShader.hlsl", "VS", L"PixelShader.hlsl", "PS", L"character", L"character_move");


	free_camera_.Init();

	D3DXVECTOR3 eye(0.0f, 0.0f, -30.0f);
	D3DXVECTOR3 at(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);


	free_camera_.CreateTargetViewMatrix(eye, at, up);
	free_camera_.CreateProjectionMatrix();

	main_camera_ = &free_camera_;


	dx_rt_.Create(device_, 800, 600);


	light_obj_.Init(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR4(1, 1, 1, 1), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR4(1, 1, 1, 1),
		D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR4(1, 1, 1, 1), device_, immediate_device_context_, main_camera_);

	CreateConstantBuffer();

	return true;
}

bool PToolCore::Frame()
{

	light_obj_.Frame();

#pragma region KEY
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
	if (g_InputActionMap.wKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->MoveFoward();
	}
	if (g_InputActionMap.sKey == KEYSTAT::KEY_HOLD)
	{
		main_camera_->MoveBackward();
	}
	if (g_InputActionMap.middleClick == KEYSTAT::KEY_PUSH)
	{
		ToggleIsWireframeRender();
	}
	if (g_InputActionMap.leftArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateLeft();
	if (g_InputActionMap.rightArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateRight();
	if (g_InputActionMap.upArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateUp();
	if (g_InputActionMap.downArrowKey == KEYSTAT::KEY_HOLD)
		main_camera_->RotateDown();

#pragma endregion


	main_camera_->Frame();
	for (int ii = 0; ii < effect_plane_.eff_list_.size(); ii++)
	{
		effect_plane_.eff_list_[ii]->Frame();
	}
	return true;
}

bool PToolCore::Render()
{
	//light

	light_obj_.Render();

	//sky
	D3DXMATRIX mat_sky_world;
	D3DXMatrixScaling(&mat_sky_world, 10, 10, 10);
	D3DXMATRIX mat_sky_view = main_camera_->matView_;
	mat_sky_view._41 = 0.0f;
	mat_sky_view._42 = 0.0f;
	mat_sky_view._43 = 0.0f;

#pragma region SCREEN
	dx_rt_.Begin(immediate_device_context_);
	{

		if (is_wireframe_render_) //마우스 휠 여부에 따라 와이어프레임, 솔리드를 가르는 코드
			DX::ApplyRasterizerState(immediate_device_context_, DX::PDxState::rs_state_wireframe_);
		else
			DX::ApplyRasterizerState(immediate_device_context_, DX::PDxState::rs_state_solidframe_);
		//sky

		DX::ApplySamplerState(immediate_device_context_, DX::PDxState::sampler_state_wrap_point);
		
		
		skybox_.SetWVPMatrix(&mat_sky_world, &mat_sky_view, &main_camera_->matProj_);
		skybox_.Render();

		DX::ApplyBlendState(immediate_device_context_, blend_state_);

		DX::ApplyRasterizerState(immediate_device_context_, DX::PDxState::rs_state_nocull_);
		
		
		for (int jj = 0 ; jj < effect_plane_.eff_list_.size(); jj++)
		{
			effect_plane_.eff_list_[jj]->SetWVPMatrix(&effect_plane_.eff_list_[jj]->matWorld_, &main_camera_->matView_, &main_camera_->matProj_);
			effect_plane_.eff_list_[jj]->Render();
		}

		DX::ApplyRasterizerState(immediate_device_context_, DX::PDxState::rs_state_solidframe_);
		DX::ApplyBlendState(immediate_device_context_, DX::PDxState::blend_state_alphablend_);
		DX::ApplySamplerState(immediate_device_context_, DX::PDxState::sampler_state_anisotropic);
	
		dx_rt_.End(immediate_device_context_);
	}
#pragma endregion
	
	DX::ApplyBlendState(immediate_device_context_, DX::PDxState::blend_state_alphablend_disable_);
	DX::ApplyRasterizerState(immediate_device_context_, DX::PDxState::rs_state_solidframe_);
	screen_tex_object_.vertex_list()[0].pos = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	screen_tex_object_.vertex_list()[1].pos = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	screen_tex_object_.vertex_list()[2].pos = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	screen_tex_object_.vertex_list()[3].pos = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	
	screen_tex_object_.vertex_list()[0].uv = D3DXVECTOR2(0.0f, 0.0f);
	screen_tex_object_.vertex_list()[1].uv = D3DXVECTOR2(1.0f, 0.0f);
	screen_tex_object_.vertex_list()[2].uv = D3DXVECTOR2(1.0f, 1.0f);
	screen_tex_object_.vertex_list()[3].uv = D3DXVECTOR2(0.0f, 1.0f);
	
	immediate_device_context_->UpdateSubresource(screen_tex_object_.dx_helper().vertex_buffer_.Get(),
		0, NULL, &screen_tex_object_.vertex_list().at(0), 0, 0);
	
	
	screen_tex_object_.SetWVPMatrix(NULL, NULL, NULL);
	screen_tex_object_.PreRender();
	immediate_device_context_->PSSetShaderResources(0, 1,
		dx_rt_.shader_res_view_.GetAddressOf());
	screen_tex_object_.PostRender();
	DX::ApplyBlendState(immediate_device_context_, DX::PDxState::blend_state_alphablend_);
	return true;
}

bool PToolCore::Release()
{

	dx_rt_.Release();
	for (int ii = 0; ii < effect_plane_.eff_list_.size(); ii++)
	{
		effect_plane_.eff_list_[ii]->Release();
	}
	return true;
}

void PToolCore::MessageProc(MSG msg)
{
	PCore::MessageProc(msg);
	//PInput::GetInstance().MsgProc(msg);
	if (main_camera_ == nullptr) return;
	main_camera_->MessageProc(msg);
}

HRESULT PToolCore::CreateConstantBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC cb_everyframe_desc;
	cb_everyframe_desc.ByteWidth = sizeof(CB_VS_ChangesEveryFrame);
	cb_everyframe_desc.Usage = D3D11_USAGE_DYNAMIC;
	cb_everyframe_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb_everyframe_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb_everyframe_desc.MiscFlags = 0;
	hr = device_->CreateBuffer(&cb_everyframe_desc, NULL, constant_buffer_changes_everyframe_.GetAddressOf());

	if (FAILED(hr))
		assert(false);

	cb_everyframe_desc.ByteWidth = sizeof(CB_VS_NearlyNotChange);
	cb_nearly_not_changes_.cb_AmbientLightColor = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1);
	cb_nearly_not_changes_.cb_DiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);
	cb_nearly_not_changes_.cb_SpecularLightColor = D3DXVECTOR4(1, 1, 1, 30.0f);

	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &cb_nearly_not_changes_;
	hr = device_->CreateBuffer(&cb_everyframe_desc, &InitData, constant_buffer_nearly_not_changes_.GetAddressOf());
	if (FAILED(hr))
		assert(false);

	return hr;
}
